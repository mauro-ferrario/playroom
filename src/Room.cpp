//
//  Room.cpp
//  playroom
//
//  Created by xxx on 31/10/2018.
//

#include "Room.h"


Room::Room(int planeSubdivision, int roomWidth, int roomHeight, int roomDepth){
  this->planeSubdivision = planeSubdivision;
  this->roomSize = ofVec3f(roomWidth, roomHeight, roomDepth);
  updateRoomWalls();
  setupGUI();
}

void Room::setupGUI(){
  gui = new ofxDatGui( ofxDatGuiAnchor::TOP_LEFT );
  gui->addSlider("Room width", 0, 200, roomSize.x);
  gui->addSlider("Room height", 0, 200, roomSize.y);
  gui->addSlider("Room depth", 0, 200, roomSize.z);
  gui->onSliderEvent(this, &Room::onSliderEvent);
}

void Room::onSliderEvent(ofxDatGuiSliderEvent e)
{
  string label =  e.target->getLabel();
  
  if(label == "Room width"){
    roomSize.x = e.target->getValue();
  }
  if(label == "Room height"){
    roomSize.y = e.target->getValue();
  }
  if(label == "Room depth"){
    roomSize.z = e.target->getValue();
  }
  updateRoomWalls();
}

void Room::updateRoomWalls(){
  back.set(roomSize.x, roomSize.y, this->planeSubdivision, this->planeSubdivision);
  left.set(roomSize.z, roomSize.y, this->planeSubdivision, this->planeSubdivision);
  right.set(roomSize.z, roomSize.y, this->planeSubdivision, this->planeSubdivision);
  bottom.set(roomSize.x, roomSize.z, this->planeSubdivision, this->planeSubdivision);
  top.set(roomSize.x, roomSize.z, this->planeSubdivision, this->planeSubdivision);
  
  top.setPosition(0, roomSize.y, 0);
  back.setPosition(0, roomSize.y*0.5, -roomSize.z*0.5);
  left.setPosition(-roomSize.x*0.5, roomSize.y*0.5, 0);
  right.setPosition(roomSize.x*0.5, roomSize.y*0.5, 0);
  bottom.setPosition(0, 0, 0);
}

void Room::drawBack(){
  ofPushMatrix();
  ofTranslate(back.getPosition());
  ofSetColor(255,255,0);
  back.getMesh().drawFaces();
  ofPopMatrix();
}

void Room::drawRight(){
  ofPushMatrix();
  ofTranslate(right.getPosition());
  ofRotateYDeg(-90);
  ofSetColor(255);
  right.getMesh().drawFaces();
  ofPopMatrix();
}

void Room::drawLeft(){
  ofPushMatrix();
  ofTranslate(left.getPosition());
  ofRotateYDeg(-90);
  ofSetColor(255,0,0);
  left.getMesh().drawFaces();
  ofPopMatrix();
}

void Room::drawBottom(){
  ofPushMatrix();
  ofTranslate(bottom.getPosition());
  ofRotateXDeg(-90);
  ofSetColor(255);
  bottom.getMesh().drawFaces();
  ofPopMatrix();
}

void Room::drawTop(){
  ofPushMatrix();
  ofTranslate(top.getPosition());
  ofRotateXDeg(90);
  ofSetColor(255);
  top.getMesh().drawFaces();
  ofPopMatrix();
}

void Room::customDraw(){
  drawBack();
  drawBottom();
  drawTop();
  drawLeft();
  drawRight();
}
