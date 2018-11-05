#include "ofMain.h"
#include "ofApp.h"
//========================================================================
int main( ){
  ofGLFWWindowSettings settings;
  settings.setGLVersion(4,1);
  settings.stencilBits = 8;
  settings.setSize(1920, 1080);
  shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);     // this kicks off the running of my app
  ofRunApp(new ofApp());
}

