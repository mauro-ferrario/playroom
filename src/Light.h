//
//  Light.hpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#ifndef Light_h
#define Light_h

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxAutoReloadedShader.h"
#include "ofxFirstPersonCamera.h"

enum class LightTypes
{
  DIRECTIONAL = 0,
  SPOT = 1,
  POINT = 2
};

class Light{
public:
                                      Light(string name = "", bool addToGUI = false, bool castShadow = false);
  virtual void                        setupGUI(ofxDatGui& gui);
  bool                                addToGUI;
  void                                setType(LightTypes type);
  virtual void                        draw();
  void                                setNameWithoutSpaces(string originalString);
  virtual void                        passLightToShader(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam, string lightName);
  
  ofxDatGuiColorPicker*               ambientPicker;
  ofxDatGuiColorPicker*               diffusePicker;
  ofxDatGuiSlider*                    specularSlider;
  LightTypes                          type;
  bool                                castShadow;
  
// For shadow
  virtual void                        addShadowParametersToGui();
  void                                setupForShadow();
  virtual ofVec3f                     getShadowPosition();
  void                                setLightLookAt( ofVec3f aPos, ofVec3f upVector = ofVec3f(0, 1, 0) );
  void                                beginShadowFbo();
  void                                endShadowFbo();
  void                                allocateFbo();
  ofFbo                               shadowFbo;
  ofCamera                            lightCam;
  virtual void                        addShaderVariableForShadow(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam);
  ofxDatGuiSlider*                    lightCamNearClipSlider;
  ofxDatGuiSlider*                    lightCamFarClipSlider;
  ofxDatGuiSlider*                    shadowIntensitySlider;
  void                                enableCastShadow();
  void                                disableCastShadow();

protected:
  ofxDatGuiFolder*                    lightGUIFolder;
  string                              nameWithoutSpaces;
  

private:
  ofColor                             ambient;
  ofColor                             diffuse;
  float                               specular;
  
  string                              name;
};

#endif
