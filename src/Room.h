//
//  Room.hpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#ifndef Room_h
#define Room_h

#include "ofMain.h"
#include "ofxDatGui.h"

class Room: public ofNode{
public:
                        Room(int planeSubdivision = 2, int roomWidth = 100, int roomHeight = 50, int roomDepth = 50);
  void                  setupGUI();
  void                  customDraw();

private:
  void                  drawBack();
  void                  drawRight();
  void                  drawLeft();
  void                  drawBottom();
  void                  drawTop();
  
  
  ofPlanePrimitive      back;
  ofPlanePrimitive      right;
  ofPlanePrimitive      left;
  ofPlanePrimitive      bottom;
  ofPlanePrimitive      top;
  ofxDatGui*            gui;
  ofVec3f               roomSize;
  void                  onSliderEvent(ofxDatGuiSliderEvent e);
  void                  updateRoomWalls();
  int                   planeSubdivision;
  
};

#endif /* Room_h */
