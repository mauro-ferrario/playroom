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
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT, "light handler" );
  gui->addLabel(":: "+gui->getName()+" ::");
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
  int totPointLight = 0;
  for (std::vector<Light*>::iterator it = lights.begin() ; it != lights.end(); ++it){
    if((*it)->type == LightTypes::DIRECTIONAL){
      DirectionalLight *dirLight = dynamic_cast<DirectionalLight *>(*it);
      dirLight->passLightToShader(shader, cam);
      dirLight = NULL;
    }
    if((*it)->type == LightTypes::POINT){
      string lightPos = ofToString(totPointLight);
      PointLight  *pointLight = dynamic_cast<PointLight *>(*it);
      pointLight->passLightToShader(shader, cam, "pointLights["+lightPos+"]");
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

void LightsHandler::loadSettings(){
  gui->loadSettings();
}

void LightsHandler::saveSettings(){
  gui->saveSettings();
}

void LightsHandler::toggleGUI(){
  gui->setVisible(!gui->getVisible());
}
