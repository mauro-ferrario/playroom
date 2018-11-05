//
//  PointLight.hpp
//  playroom
//
//  Created by xxx on 01/11/2018.
//

#ifndef PointLight_h
#define PointLight_h

#include "Light.h"
#include "ofxAutoReloadedShader.h"
#include "ofxFirstPersonCamera.h"

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
  
  // Shadow
  
  void                                setupForShadow();
  ofxDatGuiToggle*                    castShadow;
  void                                setRange( float nearClip, float farClip );
  void                                setLightLookAt( ofVec3f aPos, ofVec3f upVector = ofVec3f(0, 1, 0) );
  
  void                                beginShadowFbo();
  void                                endShadowFbo();
  // bias to reduce shadow acne //
  void                                setBias( float aBias );
  // intensity of the shadows //
  void                                setIntensity( float aIntensity );
  
  ofMatrix4x4                         biasMatrix;
  
  void                                allocateFbo();
  float                               _depthBias;
  float                               _intensity;
  
  ofFbo                               shadowFbo;
  ofCamera                            lightCam;
  void                                addShaderVariableForShadow(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam);
  ofxDatGuiSlider*                    lightCamNearClipSlider;
  ofxDatGuiSlider*                    lightCamFarClipSlider;
  ofxDatGuiSlider*                    biasSlider;
  ofxDatGuiSlider*                    shadowIntensitySlider;
  ofxDatGuiSlider*                    lookAtXSlider;
  ofxDatGuiSlider*                    lookAtYSlider;
  ofxDatGuiSlider*                    lookAtZSlider;
  void                                enableCastShadow();
  void                                disableCastShadow();

private:
  ofSpherePrimitive                   sphere;
};

#endif
