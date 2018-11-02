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
#include "ofxJsonSettings.h"
#include "TestMesh.h"

class Room: public ofNode{
public:
                        Room();
  void                  setup(int planeSubdivision = 200, int roomWidth = 100, int roomHeight = 50, int roomDepth = 50, LightsHandler* lightsHandler = NULL);
  void                  setupGUI();
  void                  customDraw(ofxFirstPersonCamera& cam, float time);
  void                  setLightHandler(LightsHandler* lightsHandler);
  void                  saveSettings();
  void                  loadSettings();
  void                  toggleGUI();

private:
  void                  drawBack(ofxFirstPersonCamera& cam, float time);
  void                  drawRight(ofxFirstPersonCamera& cam, float time);
  void                  drawLeft(ofxFirstPersonCamera& cam, float time);
  void                  drawBottom(ofxFirstPersonCamera& cam, float time);
  void                  drawTop(ofxFirstPersonCamera& cam, float time);
  void                  loadShader();
  void                  drawFace(ofPlanePrimitive& face, ofxFirstPersonCamera& cam, float time);
  void                  addLights(ofxAutoReloadedShader shader, ofxFirstPersonCamera& cam);
  void                  setupLights();
  
  LightsHandler*        lightsHandler;
  float                 lightMovementFactor;
  
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
  void                  onToggleEvent(ofxDatGuiToggleEvent e);
  void                  updateRoomWalls();
  int                   planeSubdivision;
  
  DirectionalLight*     directionalLight;
  PointLight*           pointLight;
  PointLight*           pointLight2;
  
  TestMesh              testMesh;
  
  
};

#endif /* Room_h */
