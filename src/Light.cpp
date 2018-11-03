//
//  Light.cpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#include "Light.h"

Light::Light(string name, bool addToGUI){
  this->name = name;
  setNameWithoutSpaces(name);
  this->addToGUI = addToGUI;
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
}

void Light::setType(LightTypes type){
  this->type = type;
}

void Light::draw(){
}
