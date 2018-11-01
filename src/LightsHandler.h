//
//  LightsHandler.hpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#ifndef LightsHandler_h
#define LightsHandler_h

#include "ofMain.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "ofxDatGui.h"
#include "ofxAutoReloadedShader.h"
#include "ofxFirstPersonCamera.h"

class LightsHandler{
public:
                      LightsHandler();
  void                setupGUI();
  void                addLight(Light* light);
  void                passLightsToShader(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam);
  void                addDirectionalLight(DirectionalLight const *dirLight, string lightPos, ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam);
  void                addPointLight(PointLight const *dirLight, string lightPos, ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam);
  void                draw();
  vector<Light*>      lights;
  
  ofxDatGui*          gui;
  
private:
  void                onButtonEvent(ofxDatGuiButtonEvent e);
  void                onSliderEvent(ofxDatGuiSliderEvent e);
  void                onColorEvent(ofxDatGuiColorPickerEvent e);
};

#endif
