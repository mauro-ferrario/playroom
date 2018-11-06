//
//  Room.cpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#include "Room.h"

Room::Room(){
 
}

void Room::setup(int planeSubdivision, int roomWidth, int roomHeight, int roomDepth, LightsHandler* lightsHandler){
  if(lightsHandler != NULL){
    this->lightsHandler = lightsHandler;
    boxTestMesh.setLightsHandler(lightsHandler);
    model.setLightsHandler(lightsHandler);
  }
  this->planeSubdivision = planeSubdivision;
//  ofBoxPrimitive box;
//  box.set(20, 100, 20, 20, 20, 20);
//  testMesh.setup(box.getMesh(), "Teste mesh 1");
  boxTestMesh.setup("Test mesh 1");
  model.setup("Test model");
  setupGUI(roomWidth, roomHeight, roomDepth);
  loadShader();
  setupLights();
  updateRoomWalls();
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
  shader.load("shaders/testMesh");
}

void Room::setLightHandler(LightsHandler* lightsHandler){
  this->lightsHandler = lightsHandler;
  boxTestMesh.setLightsHandler(lightsHandler);
  model.setLightsHandler(lightsHandler);
}

void Room::setupGUI(int roomWidth, int roomHeight, int roomDepth){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT, "room");
  gui->addLabel(":: "+gui->getName()+" ::");
  ofxDatGuiFolder* sizeFolder = gui->addFolder("Room size", ofColor::blue);
  ofxDatGuiFolder* wallsFolder = gui->addFolder("Room walls", ofColor::blue);
  ofxDatGuiFolder* textureFolder = gui->addFolder("Room material", ofColor::blue);
  
  // Room size
  
  sizeFolder->addSlider("Room width", 0, 200, roomWidth);
  sizeFolder->addSlider("Room height", 0, 200, roomHeight);
  sizeFolder->addSlider("Room depth", 0, 200, roomDepth);

  wallsFolder->addToggle("Show back", true);
  wallsFolder->addToggle("Show left", true);
  wallsFolder->addToggle("Show right", true);
  wallsFolder->addToggle("Show top", true);
  wallsFolder->addToggle("Show bottom", true);

  sizeFolder->addSlider("Light movement factor", 0, 5, 1.6);
  
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
}

void Room::onSliderEvent(ofxDatGuiSliderEvent e)
{
  string label =  e.target->getLabel();
  updateRoomWalls();
}

void Room::onToggleEvent(ofxDatGuiToggleEvent e){
}

void Room::updateRoomWalls(){
  ofVec3f roomSize;
  roomSize.x = gui->getSlider("Room width")->getValue();
  roomSize.y = gui->getSlider("Room height")->getValue();
  roomSize.z = gui->getSlider("Room depth")->getValue();
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
  maxMovement *= gui->getSlider("Light movement factor")->getValue();
  minMovement *= gui->getSlider("Light movement factor")->getValue();
  pointLight->setMovement(minMovement, maxMovement);
  pointLight2->setMovement(minMovement, maxMovement);
}

void Room::drawBack(ofxFirstPersonCamera& cam, float time, bool useShader){
  ofPushMatrix();
  ofTranslate(back.getPosition());
  ofSetColor(255,255,0);
  drawFace(back, cam, time, useShader);
  ofPopMatrix();
}

void Room::drawRight(ofxFirstPersonCamera& cam, float time, bool useShader){
  ofPushMatrix();
  ofTranslate(right.getPosition());
  ofRotateYDeg(-90);
  ofSetColor(255);
  drawFace(right, cam, time, useShader);
  ofPopMatrix();
}

void Room::drawLeft(ofxFirstPersonCamera& cam, float time, bool useShader){
  ofPushMatrix();
  ofTranslate(left.getPosition());
  ofRotateYDeg(90);
  ofSetColor(255,0,0);
  drawFace(left, cam, time, useShader);
  ofPopMatrix();
}

void Room::drawBottom(ofxFirstPersonCamera& cam, float time, bool useShader){
  ofPushMatrix();
  ofTranslate(bottom.getPosition());
  ofRotateXDeg(-90);
  ofSetColor(255);
  drawFace(bottom, cam, time, useShader);
  ofPopMatrix();
}

void Room::drawTop(ofxFirstPersonCamera& cam, float time, bool useShader){
  ofPushMatrix();
  ofTranslate(top.getPosition());
  ofRotateXDeg(90);
  ofSetColor(255);
  drawFace(top, cam, time, useShader);
  ofPopMatrix();
}

void Room::drawFace(ofPlanePrimitive& face, ofxFirstPersonCamera& cam, float time, bool useShader){
  if(useShader){
    shader.begin();
    shader.setUniform1i("doTwist", 0);
    shader.setUniform1f("time", time);
    shader.setUniformMatrix4f("model", face.getGlobalTransformMatrix());
    shader.setUniform3f("viewPos", cam.getGlobalPosition());
    addLights(shader, cam);
    addMaterial(shader);
  }
  face.getMesh().drawFaces();
  if(useShader){
    shader.end();
  }
}

void Room::addMaterial(ofxAutoReloadedShader shader){
  float materialSpecular = gui->getSlider( "Specular")->getValue();
  ofColor materialDiffuseColor = gui->getColorPicker("Diffuse Color")->getColor();
  // Material
  shader.setUniform3f("material.diffuse", materialDiffuseColor.r/255.0, materialDiffuseColor.g/255.0, materialDiffuseColor.b/255.0);
  shader.setUniform3f("material.specular", materialSpecular, materialSpecular, materialSpecular);
  shader.setUniform1f("material.shininess",  pow(2, (int) gui->getSlider( "Material Shininess")->getValue()));
}

void Room::addLights(ofxAutoReloadedShader shader, ofxFirstPersonCamera& cam){
  lightsHandler->passLightsToShader(shader, cam);
}

void Room::customDraw(ofxFirstPersonCamera& cam, float time, bool useShader){
  if(gui->getToggle("Show back")->getChecked())
    drawBack(cam, time, useShader);
  if(gui->getToggle("Show bottom")->getChecked())
    drawBottom(cam, time, useShader);
  if(gui->getToggle("Show top")->getChecked())
    drawTop(cam, time, useShader);
  if(gui->getToggle("Show left")->getChecked())
    drawLeft(cam, time, useShader);
  if(gui->getToggle("Show right")->getChecked())
    drawRight(cam, time, useShader);
  
   // Devo fare un ciclo  fra tutti gli oggetti aggiunti
  boxTestMesh.draw(cam, time);
  model.draw(cam, time);
  
//  shader.begin();
//  shader.setUniform1f("time", ofGetElapsedTimef());
//  shader.setUniformMatrix4f("model", box.getGlobalTransformMatrix());
//  shader.setUniform3f("viewPos", cam.getGlobalPosition());
//  box.getMesh().drawFaces();
//  shader.end();
}

void Room::saveSettings(){
  gui->saveSettings();
  // Devo fare un ciclo  fra tutti gli oggetti aggiunti
  boxTestMesh.saveSettings();
  model.saveSettings();
}

void Room::loadSettings(){
  gui->loadSettings();
  boxTestMesh.loadSettings();
  model.loadSettings();
  updateRoomWalls();
}

void Room::toggleGUI(){
  gui->setVisible(!gui->getVisible());
  // Devo fare un ciclo  fra tutti gli oggetti aggiunti
  boxTestMesh.toggleGUI();
  model.toggleGUI();
}
