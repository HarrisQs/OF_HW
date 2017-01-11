#pragma once

#include "ofMain.h"
#include "ofxCv.h"


class ofApp : public ofBaseApp 
{

public:
	void setup();//程式一開始跑的
	void update();//這個函式將會被重複且固定的呼叫
	void draw();//每次Update()跑完就會跑
	
	ofVideoGrabber cam;//為了存取攝影機的

};
