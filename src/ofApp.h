#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp 
{

public:
	void setup();//程式一開始跑的
	void update();//這個函式將會被重複且固定的呼叫
	void draw();//每次Update()跑完就會跑
	void keyPressed(int key);
	
	ofVideoGrabber cam;//為了存取攝影機的
	ofPixels videoInverted;
	ofTexture videoTexture;
	ofxCvColorImage rgb;                           //rgb object for storing color image data
	ofxCvGrayscaleImage filtered, red, green, blue;    //objects for storing grayscale image data
	ofxCvContourFinder contours;
	ofSoundPlayer  synth;
	ofSoundPlayer  Win;
	bool isBeginGame = false;
	bool LoseOrWin = false;
	bool IsFirst = true;
	ofTrueTypeFont	font;

};
