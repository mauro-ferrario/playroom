//
//  LightsHandler.hpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#ifndef LightsHandler_h
#define LightsHandler_h

#include "ofMain.h"
#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "ofxDatGui.h"
#include "ofxAutoReloadedShader.h"
#include "ofxFirstPersonCamera.h"

class LightsHandler{
public:
                      LightsHandler();
  void                setupGUI();
  void                addLight(Light* light);
  void                passLightsToShader(ofxAutoReloadedShader& shader, ofxFirstPersonCamera& cam);

  template<typename Draw>
  void updateShadow(ofxFirstPersonCamera& cam, float time, bool useShader, Draw & element){
    for (std::vector<Light*>::iterator it = lights.begin() ; it != lights.end(); ++it){
      if((*it)->castShadow){
        if((*it)->type == LightTypes::DIRECTIONAL){
          DirectionalLight* directionalLight = dynamic_cast<DirectionalLight*>(*it);
          directionalLight->beginShadowFbo();
          ofEnableDepthTest();
          glCullFace(GL_FRONT);
          element.drawScene(cam, time, useShader);
          glCullFace(GL_BACK);
          ofDisableDepthTest();
          directionalLight->endShadowFbo();
          directionalLight = NULL;
        }
      }
    }
  }
  
  void                draw();
  vector<Light*>      lights;
  
  ofxDatGui*          gui;
  void                saveSettings();
  void                loadSettings();
  void                toggleGUI();
  
private:
  void                onButtonEvent(ofxDatGuiButtonEvent e);
  void                onSliderEvent(ofxDatGuiSliderEvent e);
  void                onColorEvent(ofxDatGuiColorPickerEvent e);
};

#endif
