//
//  TestMesh.cpp
//  playroom
//
//  Created by xxx on 02/11/2018.
//

#include "TestMesh.h"

TestMesh::TestMesh(){
}

void TestMesh::setup(string name){
  this->name = name;
  loadShader();
  box.set(10, 30, 10, 50, 50, 50);
  setupGUI();
}

void TestMesh::draw(ofxFirstPersonCamera& cam, float time){
  ofVec3f tempPosition;
  ofVec3f tempRotation;
  tempPosition.x = gui->getSlider("Pos x")->getValue();
  tempPosition.y = gui->getSlider("Pos y")->getValue();
  tempPosition.z = gui->getSlider("Pos z")->getValue();
  tempRotation.x = gui->getSlider("Rotation x")->getValue();
  tempRotation.y = gui->getSlider("Rotation y")->getValue();
  tempRotation.z = gui->getSlider("Rotation z")->getValue();
  ofPushMatrix();
  ofTranslate(tempPosition);
  ofRotateXDeg(tempRotation.x);
  ofRotateYDeg(tempRotation.y);
  ofRotateZDeg(tempRotation.z);
  shader.begin();
  shader.setUniformMatrix4f("normalMatrix", ofGetCurrentNormalMatrix());
  shader.setUniform1i("doTwist", 1);
  shader.setUniform1f("time", time);
  shader.setUniformMatrix4f("model", box.getGlobalTransformMatrix());
  shader.setUniform3f("viewPos", cam.getGlobalPosition());
  shader.setUniform1f("angle_deg_max", gui->getSlider("Twist rotation")->getValue());
  shader.setUniform1f("height", box.getHeight());
  lightsHandler->passLightsToShader(shader, cam);
  addMaterial(shader);
  box.getMesh().drawFaces();
  shader.end();
  ofPopMatrix();
}

void TestMesh::addMaterial(ofxAutoReloadedShader shader){
  float materialSpecular = gui->getSlider("Specular")->getValue();
  ofColor materialDiffuseColor = gui->getColorPicker( "Diffuse Color")->getColor();
  // Material
  shader.setUniform3f("material.diffuse", materialDiffuseColor.r/255.0, materialDiffuseColor.g/255.0, materialDiffuseColor.b/255.0);
  shader.setUniform3f("material.specular", materialSpecular, materialSpecular, materialSpecular);
  shader.setUniform1f("material.shininess",  pow(2, (int) gui->getSlider("Material Shininess")->getValue()));
}

void TestMesh::setLightsHandler(LightsHandler* lightsHandler){
  this->lightsHandler = lightsHandler;
}

void TestMesh::loadShader(){
  shader.load("shaders/testMesh");
}

void TestMesh::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT, this->name);
  gui->setPosition(gui->getWidth()*2, 0);
  ofxDatGuiFolder* positionFolder = gui->addFolder("Position", ofColor::blue);
  ofxDatGuiFolder* rotationFolder = gui->addFolder("Rotation", ofColor::blue);
  ofxDatGuiFolder* textureFolder = gui->addFolder("Material", ofColor::blue);
  ofxDatGuiFolder* boxSizeFolder = gui->addFolder("Size", ofColor::blue);
  ofxDatGuiFolder* twistFolder = gui->addFolder("Twist", ofColor::blue);
  
  positionFolder->addSlider("Pos x", -600, 600);
  positionFolder->addSlider("Pos y", -600, 600);
  positionFolder->addSlider("Pos z", -600, 600);
  
  rotationFolder->addSlider("Rotation x", -360, 360);
  rotationFolder->addSlider("Rotation y", -360, 360);
  rotationFolder->addSlider("Rotation z", -360, 360);
  
  // Twist
  
  twistFolder->addSlider("Twist rotation", 0, 360);
  
  // Size
  
  boxSizeFolder->addSlider("Box width", 0, 100);
  boxSizeFolder->addSlider("Box height", 0, 5000);
  boxSizeFolder->addSlider("Box depth", 0, 100);
  boxSizeFolder->addSlider("Box subdivision", 2, 100);
  
  // Material props
  
  textureFolder->addSlider("Material Shininess", 1.0, 8.0, 1.0);
  textureFolder->addColorPicker("Diffuse Color", ofFloatColor(1,0.5,0.31));
  textureFolder->addSlider("Specular", 0.0, 1.0, 0.5);
  
  gui->onSliderEvent(this, &TestMesh::onSliderEvent);
  gui->onColorPickerEvent(this, &TestMesh::onColorEvent);
  gui->onToggleEvent(this, &TestMesh::onToggleEvent);
}


void TestMesh::onSliderEvent(ofxDatGuiSliderEvent e){
  string label =  e.target->getLabel();
  ofVec3f boxSize;
  boxSize.x = box.getWidth();
  boxSize.y = box.getHeight();
  boxSize.z = box.getDepth();
  int boxSubdivision = box.getResolution().x;
  
  if(label == "Pos x"){
    position.x = e.target->getValue();
  }
  if(label == "Pos y"){
    position.y = e.target->getValue();
  }
  if(label == "Pos z"){
    position.z = e.target->getValue();
  }
  
  if(label == "Rotation x"){
    rotation.x = e.target->getValue();
  }
  if(label == "Rotation y"){
    rotation.y = e.target->getValue();
  }
  if(label == "Rotation z"){
    rotation.z = e.target->getValue();
  }
  updateBoxSize();
}

void TestMesh::updateBoxSize(){
  ofVec3f boxSize;
  boxSize.x = gui->getSlider("Box width")->getValue();
  boxSize.y = gui->getSlider("Box height")->getValue();
  boxSize.z = gui->getSlider("Box depth")->getValue();
  float boxSubdivision = gui->getSlider("Box subdivision")->getValue();
  box.set(boxSize.x, boxSize.y, boxSize.z, boxSubdivision, boxSubdivision, boxSubdivision);
}

void TestMesh::onColorEvent(ofxDatGuiColorPickerEvent e){
  string label =  e.target->getLabel();
}

void TestMesh::onToggleEvent(ofxDatGuiToggleEvent e){
  
}

void TestMesh::saveSettings(){
  gui->saveSettings();
}

void TestMesh::loadSettings(){
  gui->loadSettings();
  updateBoxSize();
}

void TestMesh::toggleGUI(){
  gui->setVisible(!gui->getVisible());
}

