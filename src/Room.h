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
#include "ofxAutoReloadedShader.h"
#include "LightsHandler.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"

class Room: public ofNode{
public:
                        Room();
  void                  setup(int planeSubdivision = 2, int roomWidth = 100, int roomHeight = 50, int roomDepth = 50, LightsHandler* lightsHandler = NULL);
  void                  setupGUI();
  void                  customDraw(ofEasyCam& cam);
  void                  setLightHandler(LightsHandler* lightsHandler);

private:
  void                  drawBack(ofEasyCam& cam);
  void                  drawRight(ofEasyCam& cam);
  void                  drawLeft(ofEasyCam& cam);
  void                  drawBottom(ofEasyCam& cam);
  void                  drawTop(ofEasyCam& cam);
  void                  loadShader();
  void                  drawFace(ofPlanePrimitive& face, ofEasyCam& cam);
  void                  addLights(ofxAutoReloadedShader shader, ofEasyCam& cam);
  void                  setupLights();
  
  LightsHandler*        lightsHandler;
  
  // Material
  void                  addMaterial(ofxAutoReloadedShader shader);
  ofColor               materialDiffuseColor;
  float                 materialShininess;
  float                 materialSpecular;
  
  ofxAutoReloadedShader shader;
  
  ofPlanePrimitive      back;
  ofPlanePrimitive      right;
  ofPlanePrimitive      left;
  ofPlanePrimitive      bottom;
  ofPlanePrimitive      top;
  ofxDatGui*            gui;
  ofVec3f               roomSize;
  void                  onSliderEvent(ofxDatGuiSliderEvent e);
  void                  onColorEvent(ofxDatGuiColorPickerEvent e);
  void                  updateRoomWalls();
  int                   planeSubdivision;
  
};

#endif /* Room_h */
