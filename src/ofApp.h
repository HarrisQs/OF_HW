#pragma once

#include "ofMain.h"
#include "ofxCv.h"


class ofApp : public ofBaseApp 
{

public:
	void setup();//�{���@�}�l�]��
	void update();//�o�Ө禡�N�|�Q���ƥB�T�w���I�s
	void draw();//�C��Update()�]���N�|�]
	
	ofVideoGrabber cam;//���F�s����v����

};
