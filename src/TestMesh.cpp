//
//  TestMesh.cpp
//  playroom
//
//  Created by xxx on 02/11/2018.
//

#include "TestMesh.h"

TestMesh::TestMesh(){
}

void TestMesh::setup(ofMesh _mesh, string name){
  updateOriginalMesh(_mesh);
  this->name = name;
  loadShader();
  setupGUI();
}

void TestMesh::updateOriginalMesh(ofMesh _mesh){
  this->originalMesh.clear();
  this->originalMesh = _mesh;
}

void TestMesh::draw(ofxFirstPersonCamera& cam, float time, bool useShader){
  if(toggleEnabled->getChecked()){
    ofVec3f tempPosition;
    ofVec3f tempRotation;
    tempPosition.x = positionXSlider->getValue();
    tempPosition.y = positionYSlider->getValue();
    tempPosition.z = positionZSlider->getValue();
    tempRotation.x = rotationXSlider->getValue();
    tempRotation.y = rotationYSlider->getValue();
    tempRotation.z = rotationZSlider->getValue();
    ofPushMatrix();
    ofTranslate(tempPosition);
    ofRotateXDeg(tempRotation.x);
    ofRotateYDeg(tempRotation.y);
    ofRotateZDeg(tempRotation.z);
    if(useShader){
      shader.begin();
      shader.setUniformMatrix4f("normalMatrix", ofGetCurrentNormalMatrix());
      shader.setUniform1i("doTwist", toggleDoTwist->getChecked());
      shader.setUniform1f("time", time);
      shader.setUniform3f("viewPos", cam.getGlobalPosition());
      shader.setUniform1f("angle_deg_max", twistRotationSlider->getValue());
      shader.setUniform1f("height", height);
      lightsHandler->passLightsToShader(shader, cam);
      addMaterial(shader);
    }
    vbo.drawElements(GL_TRIANGLES, vboTotIndex);
    if(useShader){
       shader.end();
    }
    ofPopMatrix();
  }
}

void TestMesh::addMaterial(ofxAutoReloadedShader shader){
  float materialSpecular = specularSlider->getValue();
  ofColor materialDiffuseColor = diffuseColorPicker->getColor();
  // Material
  shader.setUniform3f("material.diffuse", materialDiffuseColor.r/255.0, materialDiffuseColor.g/255.0, materialDiffuseColor.b/255.0);
  shader.setUniform3f("material.specular", materialSpecular, materialSpecular, materialSpecular);
  shader.setUniform1f("material.shininess",  pow(2, (int) shininessSlider->getValue()));
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
  gui->addLabel(":: "+gui->getName()+" ::");
  toggleEnabled = gui->addToggle("Enabled", true);
  ofxDatGuiFolder* positionFolder = gui->addFolder("Position", ofColor::blue);
  ofxDatGuiFolder* rotationFolder = gui->addFolder("Rotation", ofColor::blue);
  ofxDatGuiFolder* textureFolder = gui->addFolder("Material", ofColor::blue);
  ofxDatGuiFolder* twistFolder = gui->addFolder("Twist", ofColor::blue);
  
  positionXSlider = positionFolder->addSlider("Pos x", -600, 600);
  positionYSlider = positionFolder->addSlider("Pos y", -600, 600);
  positionZSlider = positionFolder->addSlider("Pos z", -600, 600);
  
  rotationXSlider = rotationFolder->addSlider("Rotation x", -360, 360);
  rotationYSlider = rotationFolder->addSlider("Rotation y", -360, 360);
  rotationZSlider = rotationFolder->addSlider("Rotation z", -360, 360);
  
  // Twist
  
  toggleDoTwist = twistFolder->addToggle("Do twist", false);
  twistRotationSlider = twistFolder->addSlider("Twist rotation", 0, 360);
  
  // Material props
  
  shininessSlider = textureFolder->addSlider("Material Shininess", 1.0, 8.0, 1.0);
  diffuseColorPicker = textureFolder->addColorPicker("Diffuse Color", ofFloatColor(1,0.5,0.31));
  specularSlider = textureFolder->addSlider("Specular", 0.0, 1.0, 0.5);
  
  gui->onSliderEvent(this, &TestMesh::onSliderEvent);
  gui->onColorPickerEvent(this, &TestMesh::onColorEvent);
  gui->onToggleEvent(this, &TestMesh::onToggleEvent);
}


void TestMesh::onSliderEvent(ofxDatGuiSliderEvent e){
  string label =  e.target->getLabel();
  int boxSubdivision; // = box.getResolution().x;
  
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
}

void TestMesh::updateMesh(){
  vbo.setMesh(originalMesh, GL_STATIC_DRAW);
  vboTotIndex = originalMesh.getNumIndices();
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
  updateMesh();
}

void TestMesh::toggleGUI(){
  gui->setVisible(!gui->getVisible());
}

