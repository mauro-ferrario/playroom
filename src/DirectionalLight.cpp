//
//  DirectionalLight.cpp
//  playroom
//
//  Created by xxx on 01/11/2018.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(string name, bool addToGUI):Light(name, addToGUI){
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
