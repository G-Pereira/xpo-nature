#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
	//movie.setPixelFormat(OF_PIXELS_NATIVE);
	movie.load("movies/sun.mp4");
	movie.setLoopState(OF_LOOP_NORMAL);
	movie.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    movie.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    movie.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key){
		case 'q':
			ofExit(0);
			break;
		default:
			break;
	}
}
