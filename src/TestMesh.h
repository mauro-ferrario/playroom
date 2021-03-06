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
  void                    setup(ofMesh _mesh, string name);
  void                    draw(ofxFirstPersonCamera& cam, float time, bool useShader = true);
  virtual void            setupGUI();
  void                    loadShader();
  void                    setLightsHandler(LightsHandler* lightsHandler);
  virtual void            addMaterial(ofxAutoReloadedShader shader);
  ofxDatGui*              gui;
  LightsHandler*          lightsHandler;
  ofxAutoReloadedShader   shader;
  ofVbo                   vbo;
  int                     vboTotIndex;
  ofMesh                  originalMesh;
  
  ofVec3f                 position;
  ofVec3f                 rotation;
  void                    saveSettings();
  void                    loadSettings();
  void                    toggleGUI();
  void                    updateOriginalMesh(ofMesh _mesh);
  
  
  
  ofxDatGuiSlider*        positionXSlider;
  ofxDatGuiSlider*        positionYSlider;
  ofxDatGuiSlider*        positionZSlider;
  
  ofxDatGuiSlider*        rotationXSlider;
  ofxDatGuiSlider*        rotationYSlider;
  ofxDatGuiSlider*        rotationZSlider;
  
  ofxDatGuiToggle*        toggleEnabled;
  ofxDatGuiToggle*        toggleDoTwist;
  ofxDatGuiSlider*        twistRotationSlider;
  
  
  ofxDatGuiSlider*        specularSlider;
  ofxDatGuiSlider*        shininessSlider;
  ofxDatGuiColorPicker*   diffuseColorPicker;

protected:
  float                   height;
  virtual void            onSliderEvent(ofxDatGuiSliderEvent e);
  virtual void            onColorEvent(ofxDatGuiColorPickerEvent e);
  virtual void            onToggleEvent(ofxDatGuiToggleEvent e);
  virtual void            updateMesh();

private:
  
  string                  name;
};

#endif /* TestMesh_hpp */
