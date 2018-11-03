//
//  SpotLight.cpp
//  playroom
//
//  Created by xxx on 01/11/2018.
//

#include "SpotLight.h"

SpotLight::SpotLight(string name, bool addToGUI):Light(name, addToGUI){
  this->setType(LightTypes::SPOT);
}

void SpotLight::setupGUI(ofxDatGui& gui){
  SpotLight::setupGUI(gui);
//  directionXSlider = lightGUIFolder->addSlider("Direction x", -1, 1, 0);
//  directionYSlider = lightGUIFolder->addSlider("Direction y", -1, 1, 0);
//  directionZSlider = lightGUIFolder->addSlider("Direction z", -1, 1, 0);
}
