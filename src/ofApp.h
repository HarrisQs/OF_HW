#pragma once

#include "ofMain.h"
#include "ofxCv.h"

#include "Bug.h"

class ofApp : public ofBaseApp {
public:
	void setup();//�{���@�}�l�]��
	void update();//�o�Ө禡�N�|�Q���ƥB�T�w���I�s
	void draw();//�C��Update()�]���N�|�]
	
	ofVideoGrabber cam;//���F�s����v����
	ofxCv::ObjectFinder finder;//�Ψӧ���w������
	ofImage sunglasses;//Ū�J�Ϥ���

	vector <ofVec2f> holes;//�}
	vector <Bug> bugs;//��
};