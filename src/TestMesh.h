//
//  TestMesh.hpp
//  playroom
//
//  Created by xxx on 02/11/2018.
//

#ifndef TestMesh_hpp
#define TestMesh_hpp

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxAutoReloadedShader.h"
#include "LightsHandler.h"
#include "ofxFirstPersonCamera.h"

class TestMesh{
public:
                          TestMesh();
  void                    setup(string name);
  void                    draw(ofxFirstPersonCamera& cam, float time);
  void                    setupGUI();
  void                    loadShader();
  void                    setLightsHandler(LightsHandler* lightsHandler);
  void                    addMaterial(ofxAutoReloadedShader shader);
  ofxDatGui*              gui;
  LightsHandler*          lightsHandler;
  ofxAutoReloadedShader   shader;
  
  ofVec3f                 position;
  ofVec3f                 rotation;
  void                    saveSettings();
  void                    loadSettings();
  void                    toggleGUI();

private:
  
  void                    onSliderEvent(ofxDatGuiSliderEvent e);
  void                    onColorEvent(ofxDatGuiColorPickerEvent e);
  void                    onToggleEvent(ofxDatGuiToggleEvent e);
  ofBoxPrimitive          box;
  string                  name;
  void                    updateBoxSize();
};

#endif /* TestMesh_hpp */
