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
  ofEnableAlphaBlending();
  state = PLAYING_MOVIE_0;
  movie.load(MOVIE_0);
  movie0_pos = 0;
  movie1_pos = 0;
  opacity = 255;
  movie.setLoopState(OF_LOOP_NORMAL);
  movie.play();

  presence_sensor.setup("17");
  presence_sensor.export_gpio();
  presence_sensor.setdir_gpio("in");
}

//--------------------------------------------------------------
void ofApp::update() {
  movie.update();

  float current_movie_pos;

  switch (state) {
  case PLAYING_MOVIE_0:
    presence_sensor.getval_gpio(state_sensor);
    if (state_sensor == 1) {
      movie0_pos = movie.getPosition() * movie.getDuration() + FADE_SECONDS;
      state = FADING_OUT_0;
    }
    break;
  case PLAYING_MOVIE_1:
    presence_sensor.getval_gpio(state_sensor);
    if (state_sensor == 0) {
      movie1_pos = movie.getPosition() * movie.getDuration() + FADE_SECONDS;
      state = FADING_OUT_1;
    }
    break;
  case FADING_OUT_0:
    current_movie_pos = movie.getPosition() * movie.getDuration();
    if (current_movie_pos < movie0_pos) {
      opacity =
          255 * max(fmodf(movie0_pos - current_movie_pos, movie.getDuration()) /
                        FADE_SECONDS,
                    1.0);
    } else {
      opacity = 0;
      movie.load(MOVIE_1);
      movie.setPosition(movie1_pos / movie.getDuration());
      movie.play();
      state = FADING_IN_1;
    }
    break;
  case FADING_OUT_1:
    current_movie_pos = movie.getPosition() * movie.getDuration();
    if (current_movie_pos < movie1_pos) {
      opacity =
          255 * max(fmodf(movie1_pos - current_movie_pos, movie.getDuration()) /
                        FADE_SECONDS,
                    1.0);
    } else {
      opacity = 0;
      movie.load(MOVIE_0);
      movie.setPosition(movie0_pos / movie.getDuration());
      movie.play();
      state = FADING_IN_0;
    }
    break;
  case FADING_IN_0:
    current_movie_pos = movie.getPosition() * movie.getDuration();
    if (current_movie_pos > movie0_pos + FADE_SECONDS) {
      opacity = 255 *
                fmodf(current_movie_pos - movie0_pos, movie.getDuration()) /
                FADE_SECONDS;
    } else {
      opacity = 255;
      state = PLAYING_MOVIE_0;
    }
    break;
  case FADING_IN_1:
    current_movie_pos = movie.getPosition() * movie.getDuration();
    if (current_movie_pos > movie1_pos + FADE_SECONDS) {
      opacity = 255 *
                fmodf(current_movie_pos - movie1_pos, movie.getDuration()) /
                FADE_SECONDS;
    } else {
      opacity = 255;
      state = PLAYING_MOVIE_1;
    }
    break;
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofSetColor(255, 255, 255, opacity);
  ofEnableAlphaBlending();
  movie.draw(0, 0);
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
