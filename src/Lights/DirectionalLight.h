//
//  DirectionalLight.hpp
//  playroom
//
//  Created by xxx on 01/11/2018.
//

#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include "Light.h"

class DirectionalLight: public Light{
public:
                                      DirectionalLight(string name = "", bool addToGUI = false, bool castShadow = false);
  void                                setupGUI(ofxDatGui& gui);
  void                                draw();
  
  ofxDatGuiSlider*                    directionXSlider;
  ofxDatGuiSlider*                    directionYSlider;
  ofxDatGuiSlider*                    directionZSlider;
  void                                addShaderVariableForShadow(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam);
  void                                passLightToShader(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam, string lightName = "dirLight");
  ofVec3f                             getShadowPosition();
  ofVec3f                             getDirection();
};

#endif
