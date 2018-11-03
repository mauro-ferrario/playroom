//
//  ModelTestMesh.cpp
//  playroom
//
//  Created by xxx on 03/11/2018.
//

#include "ModelTestMesh.h"

ModelTestMesh::ModelTestMesh(){
  
}

void ModelTestMesh::setup(string name){
  model.loadModel("penguin.obj");
  updateScale(1.0);
  TestMesh::setup(modelMesh, name);
}

void ModelTestMesh::setupGUI(){
  TestMesh::setupGUI();
  gui->addSlider("Model original scale", 0, 200.0);
  gui->setPosition(gui->getWidth()*3,0);
  
}

void ModelTestMesh::onSliderEvent(ofxDatGuiSliderEvent e){
  TestMesh::onSliderEvent(e);
  updateMesh();
}

void ModelTestMesh::updateScale(float newScale){
  modelMesh = model.getMesh(0);
  for( int i = 0; i < modelMesh.getNumVertices(); i++ ) {
    modelMesh.getVertices()[i] = modelMesh.getVertices()[i] * newScale;
  }
}

void ModelTestMesh::updateMesh(){
  updateScale(gui->getSlider("Model original scale")->getValue());
  updateOriginalMesh(modelMesh);
  height = 100;
  TestMesh::updateMesh();
}

