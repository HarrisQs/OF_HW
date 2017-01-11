#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() 
{
	ofSetVerticalSync(true);//是個起始必備的!?
	ofSetFrameRate(120);//給螢幕刷新速度一個目標!
	cam.setup(1280, 960);//攝影機投出的大小
	ofEnableAlphaBlending();//混和的 在這裡不知道混啥= =?
}

void ofApp::update() 
{
	cam.update();
}

void ofApp::draw() 
{
	
	ofSetColor(255, 255, 255);
	cam.draw(0, 0);//把攝影機的畫面畫出來
	//Map
	ofSetColor(255, 255, 0);
	ofDrawRectangle(100, 0, 50, 800);
	ofDrawRectangle(250, 160, 50, 800);
	ofDrawRectangle(400, 0, 50, 800);
	ofDrawRectangle(550, 160, 50, 800);
	ofDrawRectangle(700, 0, 50, 800);
	ofDrawCircle(800,800,100);
	ofDrawRectangle(900, 600, 380, 50);
	ofDrawRectangle(750, 450, 380, 50);
	ofDrawRectangle(900, 300, 380, 50);
	ofDrawRectangle(750, 150, 380, 50);
	ofDrawRectangle(900, 0, 380, 50);
	ofSetColor(255, 0, 0);
	ofDrawRectangle(750, 0, 150, 50);

}
