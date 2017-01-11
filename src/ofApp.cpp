#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetWindowShape(1920, 1080);
	ofSetVerticalSync(true);//�O�Ӱ_�l���ƪ�!?
	ofSetFrameRate(120);//���ù���s�t�פ@�ӥؼ�!
	cam.setup(1920, 1080);//��v����X���j�p
	ofEnableAlphaBlending();//�V�M�� �b�o�̤����D�Vԣ= =?

}

void ofApp::update() {
	cam.update();
}

void ofApp::draw() {
	
	ofSetColor(255, 255, 255);
	cam.draw(0, 0);//����v�����e���e�X��
	
}
