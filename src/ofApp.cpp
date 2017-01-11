#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetWindowShape(1920, 1080);
	ofSetVerticalSync(true);//是個起始必備的!?
	ofSetFrameRate(120);//給螢幕刷新速度一個目標!
	cam.setup(1920, 1080);//攝影機投出的大小
	ofEnableAlphaBlending();//混和的 在這裡不知道混啥= =?

}

void ofApp::update() {
	cam.update();
}

void ofApp::draw() {
	
	ofSetColor(255, 255, 255);
	cam.draw(0, 0);//把攝影機的畫面畫出來
	
}
