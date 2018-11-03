//
//  BoxTestMesh.hpp
//  playroom
//
//  Created by xxx on 03/11/2018.
//

#ifndef BoxTestMesh_h
#define BoxTestMesh_h

#include "TestMesh.h"

class BoxTestMesh: public TestMesh{
public:
                    BoxTestMesh();
  void              setup(string name);
  void              setupGUI();
  void              onSliderEvent(ofxDatGuiSliderEvent e);
  void              updateMesh();

private:
  void              updateBoxSize();
  ofBoxPrimitive    box;
};

#endif
