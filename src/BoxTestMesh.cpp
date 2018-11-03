//
//  BoxTestMesh.cpp
//  playroom
//
//  Created by xxx on 03/11/2018.
//

#include "BoxTestMesh.h"


BoxTestMesh::BoxTestMesh(){
  
}

void BoxTestMesh::setup(string name){
  box.set(20, 10, 20, 20, 20, 20);
  TestMesh::setup(box.getMesh(), name);
}

void BoxTestMesh::setupGUI(){
  TestMesh::setupGUI();
  ofxDatGuiFolder* boxSizeFolder = gui->addFolder("Size", ofColor::blue);
  
  // Size
  
  boxSizeFolder->addSlider("Box width", 0, 100);
  boxSizeFolder->addSlider("Box height", 0, 5000);
  boxSizeFolder->addSlider("Box depth", 0, 100);
  boxSizeFolder->addSlider("Box subdivision", 2, 100);
  
}

void BoxTestMesh::onSliderEvent(ofxDatGuiSliderEvent e){
  TestMesh::onSliderEvent(e);
  ofVec3f boxSize;
  boxSize.x = box.getWidth();
  boxSize.y = box.getHeight();
  boxSize.z = box.getDepth();
  updateMesh();
}

void BoxTestMesh::updateBoxSize(){
  ofVec3f boxSize;
  boxSize.x = gui->getSlider("Box width")->getValue();
  boxSize.y = gui->getSlider("Box height")->getValue();
  boxSize.z = gui->getSlider("Box depth")->getValue();
  float boxSubdivision = gui->getSlider("Box subdivision")->getValue();
  box.set(boxSize.x, boxSize.y, boxSize.z, boxSubdivision, boxSubdivision, boxSubdivision);
  height = box.getHeight();
}

void BoxTestMesh::updateMesh(){
  updateBoxSize();
  updateOriginalMesh(box.getMesh());
  TestMesh::updateMesh();
}

