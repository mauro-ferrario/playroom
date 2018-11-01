//
//  Scene.cpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#include "Scene.h"


Scene::Scene(){
  cam.setNearClip(.01);
  cam.setFarClip(100000);
  lightsHandler = new LightsHandler();
  room.setLightHandler(lightsHandler);
  room.setup();
}

void Scene::update(){
  
}

void Scene::draw(){
  cam.begin();
  ofEnableDepthTest();
  room.customDraw(cam);
  lightsHandler->draw();
  ofDisableDepthTest();
  cam.end();
}
