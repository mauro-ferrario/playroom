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
                                      PointLight(string name = "", bool addToGUI = false, ofVec3f maxMovement = ofVec3f(600), ofVec3f minMovement = ofVec3f(-600));
  void                                setupGUI(ofxDatGui& gui);
  void                                draw();
  void                                setMovement(ofVec3f maxMovement, ofVec3f minMovement);
  ofxDatGuiSlider*                    positionXSlider;
  ofxDatGuiSlider*                    positionYSlider;
  ofxDatGuiSlider*                    positionZSlider;
  ofxDatGuiSlider*                    constantSlider;
  ofxDatGuiSlider*                    linearSlider;
  ofxDatGuiSlider*                    quadraticSlider;
  ofxDatGuiSlider*                    attenuationFactorSlider;
  ofxDatGuiToggle*                    drawToggle;
  ofVec3f                             maxMovement;
  ofVec3f                             minMovement;
  ofVec3f                             getPosition();

private:
  ofSpherePrimitive                   sphere;
};

#endif
