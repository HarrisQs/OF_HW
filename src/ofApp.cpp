#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() 
{
	ofSetVerticalSync(true);//�O�Ӱ_�l���ƪ�!?
	ofSetFrameRate(120);//���ù���s�t�פ@�ӥؼ�!
	cam.setup(1280, 960);//��v����X���j�p
	ofEnableAlphaBlending();//�V�M�� �b�o�̤����D�Vԣ= =?
}

void ofApp::update() 
{
	cam.update();
}

void ofApp::draw() 
{
	
	ofSetColor(255, 255, 255);
	cam.draw(0, 0);//����v�����e���e�X��
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
