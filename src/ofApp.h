#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp 
{

public:
	void setup();//�{���@�}�l�]��
	void update();//�o�Ө禡�N�|�Q���ƥB�T�w���I�s
	void draw();//�C��Update()�]���N�|�]
	void keyPressed(int key);
	
	ofVideoGrabber cam;//���F�s����v����
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
