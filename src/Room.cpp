//
//  Room.cpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#include "Room.h"

ofBoxPrimitive box;

Room::Room(){
 
}

void Room::setup(int planeSubdivision, int roomWidth, int roomHeight, int roomDepth, LightsHandler* lightsHandler){
  this->planeSubdivision = planeSubdivision;
  this->roomSize = ofVec3f(roomWidth, roomHeight, roomDepth);
  if(lightsHandler != NULL){
    this->lightsHandler = lightsHandler;
  }
  lightMovementFactor = 1.5;
  setupGUI();
  loadShader();
  setupLights();
  updateRoomWalls();
  loadSettings();
}

void Room::setupLights(){
  directionalLight = new DirectionalLight("Room directional light", true);
  this->lightsHandler->addLight(directionalLight);
  
  pointLight = new PointLight("Room point light", true);
  this->lightsHandler->addLight(pointLight);
  
  pointLight2 = new PointLight("Room point light 2", true);
  this->lightsHandler->addLight(pointLight2);
}

void Room::loadShader(){
  shader.load("shaders/room");
}

void Room::setLightHandler(LightsHandler* lightsHandler){
  this->lightsHandler = lightsHandler;
}

void Room::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
  ofxDatGuiFolder* sizeFolder = gui->addFolder("Room size", ofColor::blue);
  ofxDatGuiFolder* wallsFolder = gui->addFolder("Room walls", ofColor::blue);
  ofxDatGuiFolder* textureFolder = gui->addFolder("Room material", ofColor::blue);
  
  // Room size
  
  sizeFolder->addSlider("Room width", 0, 200, roomSize.x);
  sizeFolder->addSlider("Room height", 0, 200, roomSize.y);
  sizeFolder->addSlider("Room depth", 0, 200, roomSize.z);

  wallsFolder->addToggle("Show back", true);
  wallsFolder->addToggle("Show left", true);
  wallsFolder->addToggle("Show right", true);
  wallsFolder->addToggle("Show top", true);
  wallsFolder->addToggle("Show bottom", true);

  sizeFolder->addSlider("Light movement factor", 0, 2, lightMovementFactor);
  
  // Material props
  
  textureFolder->addSlider("Material Shininess", 1.0, 8.0, 1.0);
  textureFolder->addColorPicker("Diffuse Color", ofFloatColor(1,0.5,0.31));
  textureFolder->addSlider("Specular", 0.0, 1.0, 0.5);
  
  gui->onSliderEvent(this, &Room::onSliderEvent);
  gui->onColorPickerEvent(this, &Room::onColorEvent);
  gui->onToggleEvent(this, &Room::onToggleEvent);
}

void Room::onColorEvent(ofxDatGuiColorPickerEvent e)
{
  string label =  e.target->getLabel();
  
  // Material
  
  if(label == "Diffuse Color"){
    materialDiffuseColor = e.target->getColor();
  }
}

void Room::onSliderEvent(ofxDatGuiSliderEvent e)
{
  string label =  e.target->getLabel();
  bool updateRoomSize = false;
  
  if(label == "Room width"){
    roomSize.x = e.target->getValue();
    updateRoomSize = true;
  }
  if(label == "Room height"){
    roomSize.y = e.target->getValue();
    updateRoomSize = true;
  }
  if(label == "Room depth"){
    roomSize.z = e.target->getValue();
    updateRoomSize = true;
  }
  
  if(label == "Light movement factor"){
    lightMovementFactor = e.target->getValue();
    updateRoomSize = true;
  }
  
  // Color material
  
  if(label == "Material Shininess"){
    materialShininess = e.target->getValue();
  }
  if(label == "Specular"){
    materialSpecular = e.target->getValue();
  }
  
  if(updateRoomSize)
    updateRoomWalls();
}

void Room::onToggleEvent(ofxDatGuiToggleEvent e){
  
}

void Room::updateRoomWalls(){
  back.set(roomSize.x, roomSize.y, this->planeSubdivision, this->planeSubdivision);
  left.set(roomSize.z, roomSize.y, this->planeSubdivision, this->planeSubdivision);
  right.set(roomSize.z, roomSize.y, this->planeSubdivision, this->planeSubdivision);
  bottom.set(roomSize.x, roomSize.z, this->planeSubdivision, this->planeSubdivision);
  top.set(roomSize.x, roomSize.z, this->planeSubdivision, this->planeSubdivision);
  
  top.setPosition(0, roomSize.y*0.5,  -roomSize.z*0.5);
  back.setPosition(0, 0, -roomSize.z);
  left.setPosition(-roomSize.x*0.5, 0,  -roomSize.z*0.5);
  right.setPosition(roomSize.x*0.5, 0,  -roomSize.z*0.5);
  bottom.setPosition(0, -roomSize.y*0.5, -roomSize.z*0.5);
  
  ofVec3f minMovement;
  minMovement.x = roomSize.x*0.5;
  minMovement.y = roomSize.y*0.5;
  minMovement.z = 0;
  ofVec3f maxMovement;
  maxMovement.x = -roomSize.x*0.5;
  maxMovement.y = -roomSize.y*0.5;
  maxMovement.z = -roomSize.z;
  maxMovement *= lightMovementFactor;
  minMovement *= lightMovementFactor;
  pointLight->setMovement(minMovement, maxMovement);
  pointLight2->setMovement(minMovement, maxMovement);
}

void Room::drawBack(ofxFirstPersonCamera& cam, float time){
  ofPushMatrix();
  ofTranslate(back.getPosition());
  ofSetColor(255,255,0);
  drawFace(back, cam, time);
  ofPopMatrix();
}

void Room::drawRight(ofxFirstPersonCamera& cam, float time){
  ofPushMatrix();
  ofTranslate(right.getPosition());
  ofRotateYDeg(-90);
  ofSetColor(255);
  drawFace(right, cam, time);
  ofPopMatrix();
}

void Room::drawLeft(ofxFirstPersonCamera& cam, float time){
  ofPushMatrix();
  ofTranslate(left.getPosition());
  ofRotateYDeg(90);
  ofSetColor(255,0,0);
  drawFace(left, cam, time);
  ofPopMatrix();
}

void Room::drawBottom(ofxFirstPersonCamera& cam, float time){
  ofPushMatrix();
  ofTranslate(bottom.getPosition());
  ofRotateXDeg(-90);
  ofSetColor(255);
  drawFace(bottom, cam, time);
  ofPopMatrix();
}

void Room::drawTop(ofxFirstPersonCamera& cam, float time){
  ofPushMatrix();
  ofTranslate(top.getPosition());
  ofRotateXDeg(90);
  ofSetColor(255);
  drawFace(top, cam, time);
  ofPopMatrix();
}

void Room::drawFace(ofPlanePrimitive& face, ofxFirstPersonCamera& cam, float time){
  shader.begin();
  shader.setUniform1f("time", time);
  shader.setUniformMatrix4f("model", face.getGlobalTransformMatrix());
  shader.setUniform3f("viewPos", cam.getGlobalPosition());
  addLights(shader, cam);
  addMaterial(shader);
  face.getMesh().drawFaces();
  shader.end();
}

void Room::addMaterial(ofxAutoReloadedShader shader){
  // Material
  shader.setUniform3f("material.diffuse", materialDiffuseColor.r/255.0, materialDiffuseColor.g/255.0, materialDiffuseColor.b/255.0);
  shader.setUniform3f("material.specular", materialSpecular, materialSpecular, materialSpecular);
  shader.setUniform1f("material.shininess",  pow(2, (int)materialShininess));
}

void Room::addLights(ofxAutoReloadedShader shader, ofxFirstPersonCamera& cam){
  lightsHandler->passLightsToShader(shader, cam);
}

void Room::customDraw(ofxFirstPersonCamera& cam, float time){
  if(gui->getToggle("Show back")->getChecked())
    drawBack(cam, time);
  if(gui->getToggle("Show bottom")->getChecked())
    drawBottom(cam, time);
  if(gui->getToggle("Show top")->getChecked())
    drawTop(cam, time);
  if(gui->getToggle("Show left")->getChecked())
    drawLeft(cam, time);
  if(gui->getToggle("Show right")->getChecked())
    drawRight(cam, time);
  
//  shader.begin();
//  shader.setUniform1f("time", ofGetElapsedTimef());
//  shader.setUniformMatrix4f("model", box.getGlobalTransformMatrix());
//  shader.setUniform3f("viewPos", cam.getGlobalPosition());
//  box.getMesh().drawFaces();
//  shader.end();
}

void Room::saveSettings(){
  Settings::getFloat("room/size/x") = roomSize.x;
  Settings::getFloat("room/size/y") = roomSize.y;
  Settings::getFloat("room/size/z") = roomSize.z;
  Settings::getFloat("room/light-movement-factor") = lightMovementFactor;
  
  Settings::getFloat("room/material/shininess") = materialShininess;
  Settings::getFloat("room/material/specular") = materialSpecular;
  Settings::getColor("room/material/diffuse-color") = materialDiffuseColor;
  
  Settings::getBool("room/walls/back/show") = gui->getToggle("Show back")->getChecked();
  Settings::getBool("room/walls/left/show") = gui->getToggle("Show left")->getChecked();
  Settings::getBool("room/walls/right/show") = gui->getToggle("Show right")->getChecked();
  Settings::getBool("room/walls/top/show") = gui->getToggle("Show top")->getChecked();
  Settings::getBool("room/walls/bottom/show") = gui->getToggle("Show bottom")->getChecked();
}

void Room::loadSettings(){
  roomSize.x = Settings::getFloat("room/size/x");
  roomSize.y = Settings::getFloat("room/size/y");
  roomSize.z = Settings::getFloat("room/size/z");
  lightMovementFactor = Settings::getFloat("room/light-movement-factor");
  
  materialShininess = Settings::getFloat("room/material/shininess");
  materialSpecular = Settings::getFloat("room/material/specular");
  materialDiffuseColor = Settings::getColor("room/material/diffuse-color");
  
  gui->getToggle("Show back")->setChecked(Settings::getBool("room/walls/back/show"));
  gui->getToggle("Show left")->setChecked(Settings::getBool("room/walls/left/show"));
  gui->getToggle("Show right")->setChecked(Settings::getBool("room/walls/right/show"));
  gui->getToggle("Show top")->setChecked(Settings::getBool("room/walls/top/show"));
  gui->getToggle("Show bottom")->setChecked(Settings::getBool("room/walls/bottom/show"));
  
  updateRoomWalls();
}

void Room::toggleGUI(){
  gui->setVisible(!gui->getVisible());
}
