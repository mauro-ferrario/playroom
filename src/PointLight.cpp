//
//  PointLight.cpp
//  playroom
//
//  Created by xxx on 01/11/2018.
//

#include "PointLight.h"

PointLight::PointLight(string name, bool addToGUI, ofVec3f maxMovement, ofVec3f minMovement):Light(name, addToGUI){
  this->setType(LightTypes::POINT);
  setMovement(minMovement, maxMovement);
  sphere.set(5, 10);
  bCastShadow = true;
  setupForShadow();
}

void PointLight::setupForShadow(){
  allocateFbo();
  setRange( 1, 1000 );
  biasMatrix = ofMatrix4x4(
                           0.5, 0.0, 0.0, 0.0,
                           0.0, 0.5, 0.0, 0.0,
                           0.0, 0.0, 0.5, 0.0,
                           0.5, 0.5, 0.5, 1.0
                           );
  setBias( 0.001 );
  setIntensity( 0.7 );
  // range of the shadow camera //
  setRange( 10, 150 );
  setBias( 0.01 );
// lightCam.enableOrtho();
}

void PointLight::enableCastShadow(){
  bCastShadow = true;
}

void PointLight::disableCastShadow(){
  bCastShadow = false;
}

void PointLight::setRange( float nearClip, float farClip ) {
  lightCam.setNearClip( nearClip );
  lightCam.setFarClip( farClip );
}

void PointLight::setLightLookAt( ofVec3f aPos, ofVec3f upVector ) {
  lightCam.lookAt( aPos, upVector );
}

//--------------------------------------------------------------
void PointLight::beginShadowFbo() {
  lightCam.setNearClip(lightCamNearClipSlider->getValue());
  lightCam.setFarClip(lightCamFarClipSlider->getValue());
//  lightCam.setPosition(-2.0f, 4.0f, -1.0f);
   lightCam.setPosition(this->getPosition());
//  setLightLookAt( ofVec3f(lookAtXSlider->getValue(), lookAtYSlider->getValue(), lookAtZSlider->getValue()), ofVec3f(0, 1,0) );
  setLightLookAt( ofVec3f(0.0), ofVec3f(0, 1,0) );
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  shadowFbo.begin();
  ofClear(255);
  lightCam.begin();
  glEnable( GL_CULL_FACE ); // cull front faces - this helps with artifacts and shadows with exponential shadow mapping
  glCullFace( GL_BACK );
}

//--------------------------------------------------------------
void PointLight::endShadowFbo() {
  lightCam.end();
  shadowFbo.end();
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  glCullFace( GL_BACK );
  glDisable( GL_CULL_FACE );
  
}

void PointLight::setMovement(ofVec3f maxMovement, ofVec3f minMovement){
  this->minMovement = minMovement;
  this->maxMovement = maxMovement;
}

void PointLight::addShaderVariableForShadow(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam){
  
  if(castShadow->getChecked()&&!shadowFbo.isAllocated()){
    lightGUIFolder->getComponent(ofxDatGuiType::TEXTURE, "Light POV")->setVisible(true);
//    ofxDatGuiTexture* guiTexture = dynamic_cast<ofxDatGuiTexture*>(lightGUIFolder->getComponent(ofxDatGuiType::TEXTURE, "Light POV"));
//    guiTexture->setTexture(&shadowFbo.getDepthTexture());
//    guiTexture = NULL;
  }
  else  if(!castShadow->getChecked()){
//    shadowFbo.clear();
    lightGUIFolder->getComponent(ofxDatGuiType::TEXTURE, "Light POV")->setVisible(false);
  }
  
  
  ofMatrix4x4 inverseCameraMatrix = ofMatrix4x4::getInverseOf( cam.getModelViewMatrix() );
  ofMatrix4x4 shadowTransMatrix = inverseCameraMatrix * lightCam.getModelViewMatrix() * lightCam.getProjectionMatrix() * biasMatrix;
  shader.setUniformTexture( "tShadowMap", shadowFbo.getDepthTexture(), 3 );
  ofVec3f camPosInViewSpace = ofVec3f(cam.getPosition()) * cam.getModelViewMatrix();
  shader.setUniformMatrix4f("u_ShadowTransMatrix", shadowTransMatrix );
  ofVec3f lpos = ofVec3f(lightCam.getPosition()) * cam.getModelViewMatrix();
  shader.setUniform3fv( "u_lightPosInWorldSpace", &lpos.getPtr()[0] );
  ofVec3f lightInViewSpace = ofVec3f(lightCam.getPosition()) * cam.getModelViewMatrix();
  shader.setUniform1f( "u_width", shadowFbo.getWidth() );
  shader.setUniform1f( "u_height", shadowFbo.getHeight() );
  shader.setUniform1f("u_bias", biasSlider->getValue() );
  shader.setUniform1f("u_shadowIntensity", shadowIntensitySlider->getValue() );
  
  
  
  glm::mat4 lightView = glm::lookAt(glm::vec3(this->getPosition()),
                                    glm::vec3( 0.0f, 0.0f,  0.0f),
                                    glm::vec3( 0.0f, 1.0f,  0.0f));
  glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, lightCam.getNearClip(), lightCam.getFarClip());
  glm::mat4 lightSpaceMatrix = lightProjection * lightView;
  lightSpaceMatrix = lightCam.getProjectionMatrix() * lightView;
  shader.setUniformMatrix4f("lightSpaceMatrix", lightSpaceMatrix );
}

//--------------------------------------------------------------
void PointLight::allocateFbo() {
  ofFbo::Settings settings;
  settings.width  = 2560;
  settings.height = 1440;
  settings.textureTarget = GL_TEXTURE_2D;
  settings.internalformat = GL_RGBA32F_ARB;
  settings.useDepth = true;
  settings.depthStencilAsTexture = true;
  settings.useStencil = true;
  //    settings.depthStencilInternalFormat = GL_DEPTH_COMPONENT32;
  shadowFbo.allocate( settings );
  shadowFbo.getTexture().setTextureWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  shadowFbo.bind();
  ofFloatColor color(1.0,1.0,1.0,1.0);
  glTexParameterfv(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BORDER_COLOR, &color.r);
  shadowFbo.unbind();
}

//--------------------------------------------------------------
void PointLight::setBias( float aBias ) {
  _depthBias = aBias;
}

//--------------------------------------------------------------
void PointLight::setIntensity( float aIntensity ) {
  _intensity = aIntensity;
}


void PointLight::setupGUI(ofxDatGui& gui){
  Light::setupGUI(gui);
  drawToggle  = lightGUIFolder->addToggle("Draw", false);
  positionXSlider = lightGUIFolder->addSlider("Position x", -1, 1, 0);
  positionYSlider = lightGUIFolder->addSlider("Position y", -1, 1, 0);
  positionZSlider = lightGUIFolder->addSlider("Position z", -3, 3, 0);
  constantSlider = lightGUIFolder->addSlider("Constant", 0, 1, 1);
  linearSlider = lightGUIFolder->addSlider("Linear", -1, 1, 0.17);
  quadraticSlider = lightGUIFolder->addSlider("Quadratic", -1, 1, 0.192);
  attenuationFactorSlider = lightGUIFolder->addSlider("Attenuation factor", 0, 10, 0.5);
  
  castShadow = lightGUIFolder->addToggle("Cast shadow", false);
  
  lookAtXSlider = lightGUIFolder->addSlider("Look at x", -200, 200, 0);
  lookAtYSlider = lightGUIFolder->addSlider("Look at y", -200, 200, 0);
  lookAtZSlider = lightGUIFolder->addSlider("Look at z", -200, 200, 0);
  
  lightCamNearClipSlider = lightGUIFolder->addSlider("Light cam near clip", 0.001, 10, 10);
  lightCamFarClipSlider = lightGUIFolder->addSlider("Light cam far clip", 10, 100000, 150);
  biasSlider = lightGUIFolder->addSlider("Bias", 0.001, 0.010, 0.01);
  biasSlider->setPrecision(3);
  shadowIntensitySlider = lightGUIFolder->addSlider("Shadow intensity", 0, 1.0, 0.7);
  
  lightGUIFolder->addTexture("Light POV", &shadowFbo.getDepthTexture() );
  
}


ofVec3f PointLight::getPosition(){
  ofVec3f position;
  position.x = ofMap(positionXSlider->getValue(),-1,1,minMovement.x,maxMovement.x);
  position.y = ofMap(positionYSlider->getValue(),-1,1,minMovement.y,maxMovement.y);
  position.z = ofMap(positionZSlider->getValue(),-1,1,minMovement.z,maxMovement.z);
  return position;
}

void PointLight::draw(){
  if(drawToggle->getChecked()){
    ofVec3f position = getPosition();
    ofPushMatrix();
    ofTranslate(position);
    ofPushStyle();
    ofSetColor(255);
    sphere.getMesh().drawFaces();
    ofPopStyle();
    ofPopMatrix();
  }
}
