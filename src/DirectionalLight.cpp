//
//  DirectionalLight.cpp
//  playroom
//
//  Created by xxx on 01/11/2018.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(string name, bool addToGUI, bool castShadow):Light(name, addToGUI, castShadow){
  this->setType(LightTypes::DIRECTIONAL);
}

void DirectionalLight::setupGUI(ofxDatGui& gui){
  Light::setupGUI(gui);
  directionXSlider = lightGUIFolder->addSlider("Direction x", -1, 1, 0);
  directionYSlider = lightGUIFolder->addSlider("Direction y", -1, 1, 0);
  directionZSlider = lightGUIFolder->addSlider("Direction z", -1, 1, 0);
}

void DirectionalLight::draw(){
  // No need to draw
}

void DirectionalLight::addShaderVariableForShadow(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam){
  Light::addShaderVariableForShadow(shader, cam);
  glm::mat4 lightView = glm::lookAt(glm::vec3(this->getShadowPosition()),
                                    glm::vec3(0.0f, 0.0f, 0.0f),
                                    glm::vec3( 0.0f, 1.0f,  0.0f));
  glm::mat4 lightSpaceMatrix = lightCam.getProjectionMatrix() * lightView;
  shader.setUniform3f("positionForShadow", getShadowPosition());
  shader.setUniformMatrix4f("lightSpaceMatrix", lightSpaceMatrix );
}

ofVec3f DirectionalLight::getDirection(){
  ofVec3f direction;
  direction.x = directionXSlider->getValue();
  direction.y = directionYSlider->getValue();
  direction.z = directionZSlider->getValue();
  return direction;
}

ofVec3f DirectionalLight::getShadowPosition(){
  ofVec3f direction = this->getDirection();
  ofVec3f position = ofVec3f(300);
  position.x *= -direction.x;
  position.y *= -direction.y;
  position.z *= -direction.z;
  return position;
}

void DirectionalLight::passLightToShader(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam, string lightName){
  Light::passLightToShader(shader, cam, lightName);
  shader.setUniform3f("dirLight.direction", getDirection());
}
