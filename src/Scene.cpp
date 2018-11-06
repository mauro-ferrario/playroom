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
  loadSettings();
}

void Scene::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT, "scene");
  gui->setPosition(gui->getWidth(), 0);
  gui->addLabel(":: "+gui->getName()+" ::");
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
  
  ofVec3f camPos;
  camPos.x = Settings::getFloat("scene/camera-pos-x");
  camPos.y = Settings::getFloat("scene/camera-pos-y");
  camPos.z = Settings::getFloat("scene/camera-pos-z");
  cam.setPosition(camPos);
  cam.setNearClip(gui->getSlider("Camera near")->getValue());
  cam.setFarClip(gui->getSlider("Camera far")->getValue());
  cam.setMovementMaxSpeed(gui->getSlider("Camera speed")->getValue());
  timeSpeed = gui->getSlider("Time speed")->getValue();
}

void Scene::saveSettings(){
  Settings::getFloat("scene/camera-pos-x") = cam.getPosition().x;
  Settings::getFloat("scene/camera-pos-y") = cam.getPosition().y;
  Settings::getFloat("scene/camera-pos-z") = cam.getPosition().z;
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
  lightsHandler->updateShadow(cam, time, false, *this);
}

void Scene::draw(){
  cam.begin();
  drawScene(cam, time, true);
  cam.end();
}

void Scene::drawScene(ofxFirstPersonCamera& _cam, float _time, bool _useShader){
  ofEnableDepthTest();
  room.customDraw(_cam, _time, _useShader);
  if(_useShader){
    lightsHandler->draw();
  }
  ofDisableDepthTest();
}

void Scene::toggleGUI(){
  gui->setVisible(!gui->getVisible());
  room.toggleGUI();
  lightsHandler->toggleGUI();
}
