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
}
