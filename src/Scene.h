//
//  Scene.hpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#ifndef Scene_h
#define Scene_h

#include "ofMain.h"
#include "ofxDatGui.h"
#include "Room.h"
#include "LightsHandler.h"
#include "ofxFirstPersonCamera.h"
#include "ofxJsonSettings.h"

class Scene{
public:
            Scene();
  void      update();
  void      draw();
  void      saveSettings();
  void      loadSettings();
  
private:
  void                  setupGUI();
  ofxFirstPersonCamera  cam;
  Room                  room;
  LightsHandler*        lightsHandler;
  ofxDatGui*            gui;
  void                  onButtonEvent(ofxDatGuiButtonEvent e);
  void                  onSliderEvent(ofxDatGuiSliderEvent e);
  void                  onColorEvent(ofxDatGuiColorPickerEvent e);
  float                 time;
  float                 timeSpeed;
};

#endif /* Scene_hpp */
