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
  ofPushMatrix();
  ofTranslate(position);
  ofRotateXDeg(rotation.x);
  ofRotateYDeg(rotation.y);
  ofRotateZDeg(rotation.z);
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
  // Material
  shader.setUniform3f("material.diffuse", materialDiffuseColor.r/255.0, materialDiffuseColor.g/255.0, materialDiffuseColor.b/255.0);
  shader.setUniform3f("material.specular", materialSpecular, materialSpecular, materialSpecular);
  shader.setUniform1f("material.shininess",  pow(2, (int)materialShininess));
}

void TestMesh::setLightsHandler(LightsHandler* lightsHandler){
  this->lightsHandler = lightsHandler;
}

void TestMesh::loadShader(){
  shader.load("shaders/testMesh");
}

void TestMesh::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
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
  bool changeBoxSize = false;
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
  
  if(label == "Box width"){
    boxSize.x = e.target->getValue();
    changeBoxSize = true;
  }
  if(label == "Box height"){
    boxSize.y = e.target->getValue();
    changeBoxSize = true;
  }
  if(label == "Box depth"){
    boxSize.z = e.target->getValue();
    changeBoxSize = true;
  }
  if(label == "Box subdivision"){
    boxSubdivision = e.target->getValue();
    changeBoxSize = true;
  }
  
  // Color material
  
  if(label == "Material Shininess"){
    materialShininess = e.target->getValue();
  }
  if(label == "Specular"){
    materialSpecular = e.target->getValue();
  }
  
  if(changeBoxSize){
    box.set(boxSize.x, boxSize.y, boxSize.z, boxSubdivision, boxSubdivision, boxSubdivision);
  }
}

void TestMesh::onColorEvent(ofxDatGuiColorPickerEvent e){
  string label =  e.target->getLabel();
  
  // Material
  
  if(label == "Diffuse Color"){
    materialDiffuseColor = e.target->getColor();
  }
}

void TestMesh::onToggleEvent(ofxDatGuiToggleEvent e){
  
}

void TestMesh::saveSettings(){
  Settings::getFloat("mesh/"+this->name+"/position/x") = gui->getSlider("Pos x")->getValue();
  Settings::getFloat("mesh/"+this->name+"/position/y") = gui->getSlider("Pos y")->getValue();
  Settings::getFloat("mesh/"+this->name+"/position/z") = gui->getSlider("Pos z")->getValue();
  Settings::getFloat("mesh/"+this->name+"/rotation/x") = gui->getSlider("Rotation x")->getValue();
  Settings::getFloat("mesh/"+this->name+"/rotation/y") = gui->getSlider("Rotation y")->getValue();
  Settings::getFloat("mesh/"+this->name+"/rotation/z") = gui->getSlider("Rotation z")->getValue();
  Settings::getFloat("mesh/"+this->name+"/size/width") = gui->getSlider("Box width")->getValue();
  Settings::getFloat("mesh/"+this->name+"/size/height") = gui->getSlider("Box height")->getValue();
  Settings::getFloat("mesh/"+this->name+"/size/depth") = gui->getSlider("Box depth")->getValue();
  Settings::getFloat("mesh/"+this->name+"/size/subdivision") = gui->getSlider("Box subdivision")->getValue();
  Settings::getFloat("mesh/"+this->name+"/twist/rotation") = gui->getSlider("Twist rotation")->getValue();
  Settings::getFloat("mesh/"+this->name+"/material/shininess") = materialShininess;
  Settings::getFloat("mesh/"+this->name+"/material/specular") = materialSpecular;
  Settings::getColor("mesh/"+this->name+"/material/diffuse-color") = materialDiffuseColor;
}

void TestMesh::loadSettings(){
  gui->getSlider("Pos x")->setValue(Settings::getFloat("mesh/"+this->name+"/position/x"));
  gui->getSlider("Pos y")->setValue(Settings::getFloat("mesh/"+this->name+"/position/y"));
  gui->getSlider("Pos z")->setValue(Settings::getFloat("mesh/"+this->name+"/position/z"));
  gui->getSlider("Rotation x")->setValue(Settings::getFloat("mesh/"+this->name+"/rotation/x"));
  gui->getSlider("Rotation y")->setValue(Settings::getFloat("mesh/"+this->name+"/rotation/y"));
  gui->getSlider("Rotation z")->setValue(Settings::getFloat("mesh/"+this->name+"/rotation/z"));
  gui->getSlider("Box width")->setValue(Settings::getFloat("mesh/"+this->name+"/size/width"));
  gui->getSlider("Box height")->setValue(Settings::getFloat("mesh/"+this->name+"/size/height"));
  gui->getSlider("Box depth")->setValue(Settings::getFloat("mesh/"+this->name+"/size/depth"));
  gui->getSlider("Box subdivision")->setValue(Settings::getFloat("mesh/"+this->name+"/size/subdivision"));
  gui->getSlider("Twist rotation")->setValue(Settings::getFloat("mesh/"+this->name+"/twist/rotation"));
  materialShininess = Settings::getFloat("mesh/"+this->name+"/material/shininess");
  materialSpecular = Settings::getFloat("mesh/"+this->name+"/material/specular");
  materialDiffuseColor = Settings::getColor("mesh/"+this->name+"/material/diffuse-color");
}

void TestMesh::toggleGUI(){
  gui->setVisible(!gui->getVisible());
}

