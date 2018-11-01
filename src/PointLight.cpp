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
}

void PointLight::setMovement(ofVec3f maxMovement, ofVec3f minMovement){
  this->minMovement = minMovement;
  this->maxMovement = maxMovement;
}

void PointLight::setupGUI(ofxDatGui& gui){
  Light::setupGUI(gui);
  drawToggle  = lightGUIFolder->addToggle("Draw", false);
  positionXSlider = lightGUIFolder->addSlider("Position x", -1, 1, 0);
  positionYSlider = lightGUIFolder->addSlider("Position y", -1, 1, 0);
  positionZSlider = lightGUIFolder->addSlider("Position z", -1, 1, 0);
  
  constantSlider = lightGUIFolder->addSlider("Constant", 0, 1, 1);
  linearSlider = lightGUIFolder->addSlider("Linear", -1, 1, 0.17);
  quadraticSlider = lightGUIFolder->addSlider("Quadratic", -1, 1, 0.192);
  attenuationFactorSlider = lightGUIFolder->addSlider("Attenuation factor", 0, 10, 0.5);
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
