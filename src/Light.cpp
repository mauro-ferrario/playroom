//
//  Light.cpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#include "Light.h"

Light::Light(string name, bool addToGUI, bool castShadow){
  this->name = name;
  this->castShadow = castShadow;
  setNameWithoutSpaces(name);
  this->addToGUI = addToGUI;
  if(castShadow){
    setupForShadow();
  }
}

void Light::setupForShadow(){
  allocateFbo();
  lightCam.enableOrtho();
  lightCam.lookAt(ofVec3f(0.0));
}

void Light::enableCastShadow(){
  castShadow = true;
}

void Light::disableCastShadow(){
  castShadow = false;
}

void Light::setLightLookAt( ofVec3f aPos, ofVec3f upVector ) {
  lightCam.lookAt( aPos, upVector );
}

//--------------------------------------------------------------
void Light::beginShadowFbo() {
  lightCam.setNearClip(lightCamNearClipSlider->getValue());
  lightCam.setFarClip(lightCamFarClipSlider->getValue());
  lightCam.setPosition(this->getShadowPosition());
  setLightLookAt( ofVec3f(0.0), ofVec3f(0, 1,0) );
  glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
  shadowFbo.begin();
  ofClear(255);
  lightCam.begin();
  glEnable( GL_CULL_FACE ); // cull front faces - this helps with artifacts and shadows with exponential shadow mapping
  glCullFace( GL_BACK );
}

//--------------------------------------------------------------
void Light::endShadowFbo() {
  lightCam.end();
  shadowFbo.end();
  glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
  glCullFace( GL_BACK );
  glDisable( GL_CULL_FACE );
}

void Light::addShaderVariableForShadow(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam){
  shader.setUniformTexture( "shadowMap", shadowFbo.getDepthTexture(), 3 );
  shader.setUniform1f("shadowIntensity", shadowIntensitySlider->getValue() );
}

void Light::allocateFbo() {
  ofFbo::Settings settings;
  settings.width  = 2560;
  settings.height = 1440;
  settings.textureTarget = GL_TEXTURE_2D;
  settings.internalformat = GL_RGBA32F_ARB;
  settings.useDepth = true;
  settings.depthStencilAsTexture = true;
  settings.useStencil = true;
  //  settings.depthStencilInternalFormat = GL_DEPTH_COMPONENT32;
  shadowFbo.allocate( settings );
  shadowFbo.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
  shadowFbo.getTexture().setTextureWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
  shadowFbo.bind();
  ofFloatColor color(1.0,1.0,1.0,1.0);
  glTexParameterfv(GL_TEXTURE_RECTANGLE, GL_TEXTURE_BORDER_COLOR, &color.r);
  shadowFbo.unbind();
}

ofVec3f Light::getShadowPosition(){
  ofVec3f position;
  return position;
}

void Light::setNameWithoutSpaces(string originalString){
  nameWithoutSpaces = originalString;
  std::transform(nameWithoutSpaces.begin(), nameWithoutSpaces.end(), nameWithoutSpaces.begin(), ::tolower);
  std::replace(nameWithoutSpaces.begin(), nameWithoutSpaces.end(), ' ', '-');
}

void Light::setupGUI(ofxDatGui& gui){
  lightGUIFolder = gui.addFolder(name, ofColor::blue);
  ambientPicker = lightGUIFolder->addColorPicker("Ambient Color", ofFloatColor(0.2));
  diffusePicker = lightGUIFolder->addColorPicker("Diffuse Color", ofFloatColor(0.5));
  specularSlider = lightGUIFolder->addSlider("Specular", 0.0, 1.0, 1.0);
  if(castShadow){
    addShadowParametersToGui();
  }
}

void Light::addShadowParametersToGui(){
  lightGUIFolder->addLabel(": Shadow : ");
  lightCamNearClipSlider = lightGUIFolder->addSlider("Light cam near clip", 0.001, 100, 10);
  lightCamFarClipSlider = lightGUIFolder->addSlider("Light cam far clip", 3, 3000, 150);
  shadowIntensitySlider = lightGUIFolder->addSlider("Shadow intensity", 0, 1.0, 0.7);
  lightGUIFolder->addTexture("Light POV", &shadowFbo.getDepthTexture() );
}

void Light::setType(LightTypes type){
  this->type = type;
}

void Light::draw(){
}

void Light::passLightToShader(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam, string lightName){
  ofColor ambient = ambientPicker->getColor();
  ofColor diffuse = diffusePicker->getColor();
  float specular = specularSlider->getValue();
  shader.setUniform3f("viewPos", cam.getGlobalPosition());
  shader.setUniform3f(lightName+".ambient", ambient.r/255.0, ambient.g/255.0, ambient.b/255.0);
  shader.setUniform3f(lightName+".diffuse", diffuse.r/255.0, diffuse.g/255.0, diffuse.b/255.0);
  shader.setUniform3f(lightName+".specular", specular, specular, specular);
  if(castShadow){
    addShaderVariableForShadow(shader, cam);
  }
}
