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
                                      DirectionalLight(string name = "", bool addToGUI = false);
  void                                setupGUI(ofxDatGui& gui);
  void                                draw();
  
  ofVec3f                             direction;
  ofxDatGuiSlider*                    directionXSlider;
  ofxDatGuiSlider*                    directionYSlider;
  ofxDatGuiSlider*                    directionZSlider;
};

#endif
