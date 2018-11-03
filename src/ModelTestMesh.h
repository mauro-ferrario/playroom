//
//  ModelTestMesh.hpp
//  playroom
//
//  Created by xxx on 03/11/2018.
//

#ifndef ModelTestMesh_hpp
#define ModelTestMesh_hpp

#include "TestMesh.h"
#include "ofxAssimpModelLoader.h"

class ModelTestMesh: public TestMesh{
public:
                        ModelTestMesh();
  void                  setup(string name);
  void                  setupGUI();
  void                  onSliderEvent(ofxDatGuiSliderEvent e);
  void                  updateMesh();
  
private:
  void                  updateBoxSize();
  void                  updateScale(float newScale);
  ofMesh                modelMesh;
  ofxAssimpModelLoader  model;
};

#endif /* ModelTestMesh_hpp */
