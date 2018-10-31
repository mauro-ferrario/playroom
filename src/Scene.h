//
//  Scene.hpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#ifndef Scene_h
#define Scene_h

#include "ofMain.h"
#include "ofxDatGui.h"
#include "Room.h"

class Scene{
public:
            Scene();
  void      update();
  void      draw();
  
private:
  ofEasyCam cam;
  Room      room;
};

#endif /* Scene_hpp */
