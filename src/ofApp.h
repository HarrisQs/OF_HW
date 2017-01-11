#pragma once

#include "ofMain.h"
#include "ofxCv.h"


class ofApp : public ofBaseApp {
public:
	void setup();//程式一開始跑的
	void update();//這個函式將會被重複且固定的呼叫
	void draw();//每次Update()跑完就會跑
	
	ofVideoGrabber cam;//為了存取攝影機的
	ofxCv::ObjectFinder finder;//用來找指定的物件的
	ofImage sunglasses;//讀入圖片的

	vector <ofVec2f> holes;//洞
	vector <Bug> bugs;//蟲
};
