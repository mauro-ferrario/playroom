/*
 Copyright (C) 2015 Stephen Braitsch [http://braitsch.io]
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#pragma once
#include "ofxDatGuiComponent.h"

class ofxDatGuiTexture : public ofxDatGuiComponent {
  
public:
  
  ofxDatGuiTexture(string label, ofTexture* texture = NULL) : ofxDatGuiComponent(label)
  {
    this->texture = texture;
    mPercentX = 0.5f;
    mPercentY = 0.5f;
    mType = ofxDatGuiType::TEXTURE;
    proportion = texture->getWidth() / texture->getHeight();
    setBounds(ofRectangle(0, 0, texture->getWidth(), texture->getHeight()), true);
    setTheme(ofxDatGuiComponent::getTheme());
    ofAddListener(ofEvents().windowResized, this, &ofxDatGuiTexture::onWindowResized);
  }
  
  void setTexture(ofTexture* texture){
    this->texture = texture;
    proportion = texture->getWidth() / texture->getHeight();
    setBounds(ofRectangle(0, 0, texture->getWidth(), texture->getHeight()), true);
  }
  
  void setTheme(const ofxDatGuiTheme* theme)
  {
    setComponentStyle(theme);
    mStyle.height = ((mStyle.width - mStyle.padding - mLabel.width) / proportion) + mStyle.padding;
    mStyle.stripe.color = theme->stripe.pad2d;
    mColors.fill = theme->color.inputAreaBackground;
    mPad = ofRectangle(0, 0, mStyle.width - mStyle.padding - mLabel.width, mStyle.height - (mStyle.padding * 2));
  }
  
  void setBounds(ofRectangle bounds, bool scaleOnResize = false)
  {
    mBounds = bounds;
    mScaleOnResize = scaleOnResize;
    setWorldCoordinates();
  }
  
  ofRectangle getBounds()
  {
    return mBounds;
  }
  
  void reset()
  {
    mPercentX = 0.5f;
    mPercentY = 0.5f;
    setWorldCoordinates();
  }
  
  void draw()
  {
    if (!mVisible) return;
    ofPushStyle();
    mPad.x = x + mLabel.width;
    mPad.y = y + mStyle.padding;
    mPad.width = mStyle.width - mStyle.padding - mLabel.width;
    mPad.height = mPad.width / proportion;
    ofxDatGuiComponent::draw();
    ofSetColor(mColors.fill);
    ofDrawRectangle(mPad);
    if(texture != NULL && texture->isAllocated() ){
      ofSetColor(255,255);
      texture->draw(mPad.x, mPad.y, mPad.width, mPad.height);
    }
    ofPopStyle();
  }
  
  static ofxDatGuiTexture* getInstance() { return new ofxDatGuiTexture("X"); }
  
protected:
  
  void setWorldCoordinates()
  {
    mWorld.x = mBounds.x + (mBounds.width * mPercentX);
    mWorld.y = mBounds.y + (mBounds.height * mPercentY);
  }
  
  void onWindowResized(ofResizeEventArgs &e)
  {
    // scale the bounds to the resized window //
    if (mScaleOnResize){
      mBounds.width *= (ofGetWidth() / mBounds.width);
      mBounds.height *= (ofGetHeight() / mBounds.height);
      setWorldCoordinates();
    }
  }
  
private:
  ofPoint mWorld;
  ofRectangle mPad;
  ofRectangle mBounds;
  float mPercentX;
  float mPercentY;
  float proportion;
  bool mScaleOnResize;
  struct{
    ofColor fill;
  } mColors;
  ofTexture* texture;
  
};

