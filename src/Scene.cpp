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
  loadSettings();
  
  ofVec3f camPosition;
  camPosition.x = Settings::getFloat("camera/position/x");
  camPosition.y = Settings::getFloat("camera/position/y");
  camPosition.z = Settings::getFloat("camera/position/z");
  cam.setPosition(camPosition);
  
  setupGUI();
  lightsHandler = new LightsHandler();
  room.setLightHandler(lightsHandler);
  room.setup();
  lightsHandler->loadSettings();
}

void Scene::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
  gui->setPosition(gui->getWidth(), 0);
  gui->addSlider("Camera near", 0.001, 10,  Settings::getFloat("camera/near"));
  gui->addSlider("Camera far", 10, 100000, Settings::getFloat("camera/far"));
  gui->addSlider("Camera speed", 0, 100, Settings::getFloat("camera/speed"));
  gui->addSlider("Time speed", 0.001, 10, Settings::getFloat("time/speed"));
  gui->onButtonEvent(this, &Scene::onButtonEvent);
  gui->onSliderEvent(this, &Scene::onSliderEvent);
  gui->onColorPickerEvent(this, &Scene::onColorEvent);
}

void Scene::loadSettings(){
  Settings::get().load("data.json");
  cam.setNearClip(Settings::getFloat("camera/near"));
  cam.setFarClip(Settings::getFloat("camera/far"));
  cam.setMovementMaxSpeed(Settings::getFloat("camera/speed"));
  timeSpeed = Settings::getFloat("time/speed");
//  room.loadSettings();
}

void Scene::saveSettings(){
  room.saveSettings();
  lightsHandler->saveSettings();
  Settings::getFloat("camera/near") = gui->getSlider("Camera near")->getValue();
  Settings::getFloat("camera/far") = gui->getSlider("Camera far")->getValue();
  Settings::getFloat("camera/speed") = gui->getSlider("Camera speed")->getValue();
  Settings::getFloat("camera/position/x") = cam.getPosition().x;
  Settings::getFloat("camera/position/y") = cam.getPosition().y;
  Settings::getFloat("camera/position/z") = cam.getPosition().z;
  Settings::getFloat("time/speed") = gui->getSlider("Time speed")->getValue();
  Settings::get().save("data.json");
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
