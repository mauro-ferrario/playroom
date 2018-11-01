//
//  LightsHandler.cpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#include "LightsHandler.h"


LightsHandler::LightsHandler(){
  setupGUI();
}

void LightsHandler::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
  gui->onButtonEvent(this, &LightsHandler::onButtonEvent);
  gui->onSliderEvent(this, &LightsHandler::onSliderEvent);
  gui->onColorPickerEvent(this, &LightsHandler::onColorEvent);
}

void LightsHandler::addLight(Light* light){
  lights.push_back(light);
  if(light->addToGUI){
    light->setupGUI(*gui);
  }
}

void LightsHandler::onButtonEvent(ofxDatGuiButtonEvent e)
{
}

void LightsHandler::onSliderEvent(ofxDatGuiSliderEvent e)
{
}

void LightsHandler::onColorEvent(ofxDatGuiColorPickerEvent e)
{
}

void LightsHandler::passLightsToShader(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam){
  int totDirectionalLight = 0;
  int totPointLight = 0;
  for (std::vector<Light*>::iterator it = lights.begin() ; it != lights.end(); ++it){
    if((*it)->type == LightTypes::DIRECTIONAL){
      string lightPos = ofToString(totDirectionalLight);
      DirectionalLight *dirLight = dynamic_cast<DirectionalLight *>(*it);
      addDirectionalLight(dirLight, lightPos, shader, cam);
      dirLight = NULL;
      totDirectionalLight++;
    }
    if((*it)->type == LightTypes::POINT){
      string lightPos = ofToString(totPointLight);
      PointLight  *pointLight = dynamic_cast<PointLight *>(*it);
      addPointLight(pointLight, lightPos, shader, cam);
      pointLight = NULL;
      totPointLight++;
    }
  }
}

void LightsHandler::draw(){
  for (std::vector<Light*>::iterator it = lights.begin() ; it != lights.end(); ++it){
    (*it)->draw();
  }
}

void LightsHandler::addDirectionalLight(DirectionalLight *dirLight, string lightPos, ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam){
  ofColor ambient = dirLight->ambientPicker->getColor();
  ofColor diffuse = dirLight->diffusePicker->getColor();
  float specular = dirLight->specularSlider->getValue();
  ofVec3f direction;
  direction.x = dirLight->directionXSlider->getValue();
  direction.y = dirLight->directionYSlider->getValue();
  direction.z = dirLight->directionZSlider->getValue();
  shader.setUniform3f("viewPos", cam.getGlobalPosition());
  shader.setUniform3f("dirLights["+lightPos+"].direction", direction);
  shader.setUniform3f("dirLights["+lightPos+"].ambient", ambient.r/255.0, ambient.g/255.0, ambient.b/255.0);
  shader.setUniform3f("dirLights["+lightPos+"].diffuse", diffuse.r/255.0, diffuse.g/255.0, diffuse.b/255.0);
  shader.setUniform3f("dirLights["+lightPos+"].specular", specular, specular, specular);
  dirLight = NULL;
}

void LightsHandler::addPointLight(PointLight *pointLight, string lightPos, ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam){
  ofColor ambient = pointLight->ambientPicker->getColor();
  ofColor diffuse = pointLight->diffusePicker->getColor();
  float specular = pointLight->specularSlider->getValue();
  float constant = pointLight->constantSlider->getValue();
  float linear = pointLight->constantSlider->getValue();
  float quadratic = pointLight->constantSlider->getValue();
  float attenuationFactor = pointLight->attenuationFactorSlider->getValue();
  ofVec3f position = pointLight->getPosition();
  shader.setUniform3f("viewPos", cam.getGlobalPosition());
  shader.setUniform3f("pointLights["+lightPos+"].position", position);
  shader.setUniform3f("pointLights["+lightPos+"].ambient", ambient.r/255.0, ambient.g/255.0, ambient.b/255.0);
  shader.setUniform3f("pointLights["+lightPos+"].diffuse", diffuse.r/255.0, diffuse.g/255.0, diffuse.b/255.0);
  shader.setUniform3f("pointLights["+lightPos+"].specular", specular, specular, specular);
  shader.setUniform1f("pointLights["+lightPos+"].constant", constant);
  shader.setUniform1f("pointLights["+lightPos+"].linear", linear);
  shader.setUniform1f("pointLights["+lightPos+"].quadratic", quadratic);
  shader.setUniform1f("pointLights["+lightPos+"].attenuationFactor", attenuationFactor);
  pointLight = NULL;
}

void LightsHandler::loadSettings(){
  for (std::vector<Light*>::iterator it = lights.begin() ; it != lights.end(); ++it){
    (*it)->loadSettings();
  }
}

void LightsHandler::saveSettings(){
  for (std::vector<Light*>::iterator it = lights.begin() ; it != lights.end(); ++it){
    (*it)->saveSettings();
  }
}
