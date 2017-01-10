#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	ofSetWindowShape(1920, 1080);
	ofSetVerticalSync(true);//�O�Ӱ_�l���ƪ�!?
	ofSetFrameRate(120);//���ù���s�t�פ@�ӥؼ�!
	finder.setup("haarcascade_frontalface_default.xml");//��ݬݳo���ɮצ��S��
	finder.setPreset(ObjectFinder::Fast);//�i�H�M�θ̭��w�]�n���@�ǰѼ�
	finder.getTracker().setSmoothingRate(.3);
	cam.setup(1920, 1080);//��v����X���j�p
	sunglasses.load("sunglasses.png");//���J�Ϥ�
	ofEnableAlphaBlending();//�V�M�� �b�o�̤����D�Vԣ= =?

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
	if(cam.isFrameNew()) {//�p�G��v�����Ү����쪺�e����s����
		finder.update(cam);//��䦳�S���ŦX���n�䪺����
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
	cam.draw(0, 0);//����v�����e���e�X��
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

	//���Ӷ�����
	ofSetColor(255, 255, 255);
	for(int i = 0; i < finder.size(); i++) {
		ofRectangle object = finder.getObjectSmoothed(i);//���o�Ӫ��󪺤j�p
		sunglasses.setAnchorPercent(0.5, 0.5);//�NANCHOR POINT �]�m�b�Ϥ��������I
		//Anchor POINT ���I���O�T�w�I�A���������Y���ೣ�|�H�o�Ӭ����ߦA��
		float scaleAmount = .85 * object.width / sunglasses.getWidth();//���Y�q
		ofPushMatrix();//�x�s��U�����Ҫ��A
		ofTranslate(object.x + object.width / 2., object.y + object.height * .42);
		ofScale(scaleAmount, scaleAmount);
		sunglasses.draw(0, 0);//���W�Ӷ�����
		ofPopMatrix();//�٭�ofPushMatrix �x�s�����Ҫ��A
		ofTranslate(object.getPosition()); //move the coordinate system to position
		ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
		ofDrawLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
	}
	
}
