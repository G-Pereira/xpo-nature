#pragma once

#include "ofMain.h"
#include "ofxGPIO.h"

class ofApp : public ofBaseApp{

	public:

		ofVideoPlayer movie;

		GPIO presence_sensor;
		int state_sensor;

		int opacity;

		int state;
		float movie0_pos;
		float movie1_pos;

		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
};

