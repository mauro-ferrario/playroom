//
//  PointLight.cpp
//  playroom
//
//  Created by xxx on 01/11/2018.
//

#include "PointLight.h"

PointLight::PointLight(string name, bool addToGUI):Light(name, addToGUI){
  this->setType(LightTypes::POINT);
  sphere.set(5, 10);
}

void PointLight::setupGUI(ofxDatGui& gui){
  Light::setupGUI(gui);
  drawToggle  = lightGUIFolder->addToggle("Draw", false);
  positionXSlider = lightGUIFolder->addSlider("Position x", -600, 600, 0);
  positionYSlider = lightGUIFolder->addSlider("Position y", -600, 600, 0);
  positionZSlider = lightGUIFolder->addSlider("Position z", -600, 600, 0);
  
  constantSlider = lightGUIFolder->addSlider("Constant", 0, 1, 1);
  linearSlider = lightGUIFolder->addSlider("Linear", -1, 1, 0.17);
  quadraticSlider = lightGUIFolder->addSlider("Quadratic", -1, 1, 0.192);
  attenuationFactorSlider = lightGUIFolder->addSlider("Attenuation factor", 0, 10, 0.5);
}

void PointLight::draw(){
  if(drawToggle->getChecked()){
    ofVec3f position;
    position.x = positionXSlider->getValue();
    position.y = positionYSlider->getValue();
    position.z = positionZSlider->getValue();
    ofPushMatrix();
    ofTranslate(position);
    ofPushStyle();
    ofSetColor(255);
    sphere.getMesh().drawFaces();
    ofPopStyle();
    ofPopMatrix();
  }
}
