#pragma once

#include "ofMain.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp {

public:
  vector<ofVideoPlayer> vids;
  bool bFading = false;
  int vid_on = 0;
  float startFadeTime;
  float fadeDuration = 5;

  GPIO presence_sensor;
  int state_sensor;
  int rising = 1;

  void setup();
  void update();
  void draw();
  void exit();

  void keyPressed(int key);
};
