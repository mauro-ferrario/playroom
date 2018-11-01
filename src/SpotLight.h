//
//  SpotLight.hpp
//  playroom
//
//  Created by xxx on 01/11/2018.
//

#ifndef SpotLight_hpp
#define SpotLight_hpp

#include "Light.h"

class SpotLight: public Light{
public:
            SpotLight(string name = "", bool addTooGUI = false);
  void      setupGUI(ofxDatGui& gui);
  void      saveSettings();
  void      loadSettings();
};

#endif /* SpotLight_hpp */
