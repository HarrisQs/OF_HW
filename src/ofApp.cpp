#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetWindowShape(1920, 1080);
	ofSetVerticalSync(true);//是個起始必備的!?
	ofSetFrameRate(120);//給螢幕刷新速度一個目標!
	finder.setup("haarcascade_frontalface_default.xml");//找看看這個檔案有沒有
	finder.setPreset(ObjectFinder::Fast);//可以套用裡面預設好的一些參數
	finder.getTracker().setSmoothingRate(.3);
	cam.setup(1920, 1080);//攝影機投出的大小
	sunglasses.load("sunglasses.png");//載入圖片
	ofEnableAlphaBlending();//混和的 在這裡不知道混啥= =?

	/*****************************/
	// add some random holes for the bugs to come out
	int nHoldes = 10;
	for (int i = 0; i<nHoldes; i++) {
		ofVec2f p(ofRandomWidth(), ofRandomHeight());
		holes.push_back(p);
	}
}

void ofApp::update() {
	cam.update();
	if(cam.isFrameNew()) {//如果攝影機的所捕捉到的畫面更新的話
		finder.update(cam);//找找有沒有符合剛剛要找的物件
	}
	if ((int)ofRandom(0, 20) == 10) {

		int randomHole = ofRandom(holes.size());

		Bug newBug;
		newBug.pos = holes[randomHole];
		newBug.vel.set(ofRandom(-1, 1), ofRandom(-1, 1));
		bugs.push_back(newBug);
	}

	for (unsigned int i = 0; i<bugs.size(); i++) {

		bugs[i].update();

		// bug pos and size
		float   size = bugs[i].size;
		ofVec2f pos = bugs[i].pos;

		// wrap the bugs around the screen
		if (pos.x > ofGetWidth() - size)  bugs[i].pos.x = -size;
		if (pos.x < -size)              bugs[i].pos.x = ofGetWidth() - size;
		if (pos.y > ofGetHeight() + size) bugs[i].pos.y = -size;
		if (pos.y < -size)              bugs[i].pos.y = ofGetHeight() - size;

	}
}

void ofApp::draw() {
	
	ofSetColor(255, 255, 255);
	cam.draw(0, 0);//把攝影機的畫面畫出來
	// draw the bug holes
	for (unsigned int i = 0; i<holes.size(); i++) {
		ofSetColor(100);
		ofDrawCircle(holes[i], 20);
		ofSetColor(40);
		ofDrawCircle(holes[i], 17);
	}
	for (unsigned int i = 0; i<bugs.size(); i++) {
		bugs[i].draw();
	}

	//戴太陽眼鏡
	ofSetColor(255, 255, 255);
	for(int i = 0; i < finder.size(); i++) {
		ofRectangle object = finder.getObjectSmoothed(i);//取得該物件的大小
		sunglasses.setAnchorPercent(0.5, 0.5);//將ANCHOR POINT 設置在圖片的中心點
		//Anchor POINT 有點像是固定點，全部的伸縮旋轉都會以這個為中心再轉
		float scaleAmount = .85 * object.width / sunglasses.getWidth();//伸縮量
		ofPushMatrix();//儲存當下的環境狀態
		ofTranslate(object.x + object.width / 2., object.y + object.height * .42);
		ofScale(scaleAmount, scaleAmount);
		sunglasses.draw(0, 0);//戴上太陽眼鏡
		ofPopMatrix();//還原ofPushMatrix 儲存的環境狀態
		ofTranslate(object.getPosition()); //move the coordinate system to position
		ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
		ofDrawLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
	}
	
}
