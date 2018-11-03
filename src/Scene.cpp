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
  
  ofVec3f camPosition;
//  camPosition.x = Settings::getFloat("camera/position/x");
//  camPosition.y = Settings::getFloat("camera/position/y");
//  camPosition.z = Settings::getFloat("camera/position/z");
  cam.setPosition(camPosition);
  
  setupGUI();
  lightsHandler = new LightsHandler();
  room.setLightHandler(lightsHandler);
  room.setup();
  loadSettings();
}

void Scene::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT, "scene");
  gui->setPosition(gui->getWidth(), 0);
  gui->addSlider("Camera near", 0.001, 10);
  gui->addSlider("Camera far", 10, 100000);
  gui->addSlider("Camera speed", 0, 100);
  gui->addSlider("Time speed", 0.001, 10);
  gui->onButtonEvent(this, &Scene::onButtonEvent);
  gui->onSliderEvent(this, &Scene::onSliderEvent);
  gui->onColorPickerEvent(this, &Scene::onColorEvent);
}

void Scene::loadSettings(){
  gui->loadSettings("data.json");
  lightsHandler->loadSettings();
  room.loadSettings();
}

void Scene::saveSettings(){
  gui->saveSettings();
  room.saveSettings();
  lightsHandler->saveSettings();
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

void Scene::toggleGUI(){
  gui->setVisible(!gui->getVisible());
  room.toggleGUI();
  lightsHandler->toggleGUI();
}
