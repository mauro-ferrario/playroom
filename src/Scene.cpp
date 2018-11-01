//
//  Scene.cpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#include "Scene.h"


Scene::Scene(){
  timeSpeed = 0.1;
  cam.setNearClip(.01);
  cam.setFarClip(100000);
  cam.setMovementMaxSpeed(10.0);
  setupGUI();
  lightsHandler = new LightsHandler();
  room.setLightHandler(lightsHandler);
  room.setup();
}

void Scene::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
  gui->setPosition(gui->getWidth(), 0);
  gui->addSlider("Camera near", 0.001, 10);
  gui->addSlider("Camera far", 10, 100000);
  gui->addSlider("Camera speed", 0, 100);
  gui->addSlider("Time speed", 0.001, 10);
  gui->onButtonEvent(this, &Scene::onButtonEvent);
  gui->onSliderEvent(this, &Scene::onSliderEvent);
  gui->onColorPickerEvent(this, &Scene::onColorEvent);
}

void Scene::onButtonEvent(ofxDatGuiButtonEvent e)
{
}

void Scene::onSliderEvent(ofxDatGuiSliderEvent e)
{
  string label =  e.target->getLabel();
  
  
  if(label == "Camera near"){
    cam.setNearClip(e.target->getValue());
  }
  
  if(label == "Camera far"){
    cam.setFarClip(e.target->getValue());
  }
  
  if(label == "Camera speed"){
    cam.setMovementMaxSpeed(e.target->getValue());
  }
  
  if(label == "Time speed"){
    timeSpeed = e.target->getValue();
  }
}

void Scene::onColorEvent(ofxDatGuiColorPickerEvent e)
{
}

void Scene::update(){
  time += timeSpeed;
}

void Scene::draw(){
  cam.begin();
  ofEnableDepthTest();
  room.customDraw(cam, time);
  lightsHandler->draw();
  ofDisableDepthTest();
  cam.end();
}
