//
//  PointLight.hpp
//  playroom
//
//  Created by xxx on 01/11/2018.
//

#ifndef PointLight_h
#define PointLight_h

#include "Light.h"

class PointLight: public Light{
public:
                                      PointLight(string name = "", bool addToGUI = false);
  void                                setupGUI(ofxDatGui& gui);
  void                                draw();
  ofxDatGuiSlider*                    positionXSlider;
  ofxDatGuiSlider*                    positionYSlider;
  ofxDatGuiSlider*                    positionZSlider;
  ofxDatGuiSlider*                    constantSlider;
  ofxDatGuiSlider*                    linearSlider;
  ofxDatGuiSlider*                    quadraticSlider;
  ofxDatGuiSlider*                    attenuationFactorSlider;
  ofxDatGuiToggle*                    drawToggle;

private:
  ofSpherePrimitive                   sphere;
};

#endif
