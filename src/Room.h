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
#include "ofxFirstPersonCamera.h"
#include "TestMesh.h"
#include "BoxTestMesh.h"
#include "ModelTestMesh.h"

class Room: public ofNode{
public:
                        Room();
  void                  setup(int planeSubdivision = 200, int roomWidth = 100, int roomHeight = 50, int roomDepth = 50, LightsHandler* lightsHandler = NULL);
  void                  setupGUI(int roomWidth = 100, int roomHeight = 50, int roomDepth = 50);
  void                  customDraw(ofxFirstPersonCamera& cam, float time, bool useShader = true);
  void                  setLightHandler(LightsHandler* lightsHandler);
  void                  saveSettings();
  void                  loadSettings();
  void                  toggleGUI();

private:
  void                  drawBack(ofxFirstPersonCamera& cam, float time, bool useShader = true);
  void                  drawRight(ofxFirstPersonCamera& cam, float time, bool useShader = true);
  void                  drawLeft(ofxFirstPersonCamera& cam, float time, bool useShader = true);
  void                  drawBottom(ofxFirstPersonCamera& cam, float time, bool useShader = true);
  void                  drawTop(ofxFirstPersonCamera& cam, float time, bool useShader = true);
  void                  loadShader();
  void                  drawFace(ofPlanePrimitive& face, ofxFirstPersonCamera& cam, float time, bool useShader = true);
  void                  addLights(ofxAutoReloadedShader shader, ofxFirstPersonCamera& cam);
  void                  setupLights();
  
  LightsHandler*        lightsHandler;
  
  // Material
  void                  addMaterial(ofxAutoReloadedShader shader);
  
  ofxAutoReloadedShader shader;
  
  ofPlanePrimitive      back;
  ofPlanePrimitive      right;
  ofPlanePrimitive      left;
  ofPlanePrimitive      bottom;
  ofPlanePrimitive      top;
  ofxDatGui*            gui;
  void                  onSliderEvent(ofxDatGuiSliderEvent e);
  void                  onColorEvent(ofxDatGuiColorPickerEvent e);
  void                  onToggleEvent(ofxDatGuiToggleEvent e);
  void                  updateRoomWalls();
  int                   planeSubdivision;
  
  DirectionalLight*     directionalLight;
  PointLight*           pointLight;
  PointLight*           pointLight2;
  
  TestMesh              testMesh;
  BoxTestMesh           boxTestMesh;
  ModelTestMesh         model;
};

#endif /* Room_h */
