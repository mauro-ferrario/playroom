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

enum class LightTypes
{
  DIRECTIONAL = 0,
  SPOT = 1,
  POINT = 2
};

class Light{
public:
                                      Light(string name = "", bool addToGUI = false);
  virtual void                        setupGUI(ofxDatGui& gui);
  bool                                addToGUI;
  void                                setType(LightTypes type);
  virtual void                        draw();
  
  ofxDatGuiColorPicker*               ambientPicker;
  ofxDatGuiColorPicker*               diffusePicker;
  ofxDatGuiSlider*                    specularSlider;
  LightTypes                          type;

protected:
  ofxDatGuiFolder*                    lightGUIFolder;
  

private:
  ofColor                             ambient;
  ofColor                             diffuse;
  float                               specular;
  
  string                              name;
};

#endif
