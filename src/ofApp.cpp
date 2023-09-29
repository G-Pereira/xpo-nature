#include "ofApp.h"
#include "math.h"

#define FADE_SECONDS 2.0

#define MOVIE_0 "movies/sun.mkv"
#define MOVIE_1 "movies/beach.mkv"

#define PLAYING_MOVIE_0 0
#define FADING_OUT_0 1
#define FADING_OUT_1 2
#define FADING_IN_0 3
#define FADING_IN_1 4
#define PLAYING_MOVIE_1 5

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetVerticalSync(true);
  // movie.setPixelFormat(OF_PIXELS_NATIVE);
  vids.resize(2);
  vids[0].load(MOVIE_0);
  vids[1].load(MOVIE_1);
  vids[0].setLoopState(OF_LOOP_NORMAL);
  vids[1].setLoopState(OF_LOOP_NORMAL);
  vids[0].play();
  vids[1].play();

  presence_sensor.setup("17");
  presence_sensor.export_gpio();
  presence_sensor.setdir_gpio("in");
}

//--------------------------------------------------------------
void ofApp::update() {
  if (vids.size() == 2) {
    vids[0].update();
    vids[1].update();
  }
  presence_sensor.getval_gpio(state_sensor);
  if (state_sensor == 1 && rising == 1) {
    rising = 0;
    bFading = true;
    startFadeTime = ofGetElapsedTimef();
    vid_on = 0;
  } else if (state_sensor == 0 && rising == 0) {
    rising = 1;
    bFading = true;
    startFadeTime = ofGetElapsedTimef();
    vid_on = 1;
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (vids.size() == 2) {
    ofSetColor(255);

    vids[vid_on].draw(0, 0);
    if (bFading) {
      ofSetColor(255, ofMap(ofGetElapsedTimef() - startFadeTime, 0,
                            fadeDuration, 0, 255, true));
      vids[vid_on == 1 ? 0 : 1].draw(0, 0);
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  switch (key) {
  case 'q':
    ofExit(0);
    break;
  default:
    break;
  }
}

void ofApp::exit() { presence_sensor.unexport_gpio(); }
