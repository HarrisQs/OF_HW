#include "ofApp.h"

using namespace ofxCv;
using namespace cv;
bool IsBump(int centerOfCircleX, int centerOfCircleY);
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
	ofDrawRectangle(100, 0, 50, 800);//X 100~150 Y 0~800 0
	ofDrawRectangle(250, 160, 50, 800);//X 250~300 Y 160~960 1
	ofDrawRectangle(400, 0, 50, 800);//X 400~450 Y 0~800 2
	ofDrawRectangle(550, 160, 50, 800);//X 550~600 Y 160~960 3
	ofDrawRectangle(700, 0, 50, 800);//X 700~750 Y 0~800 4
	ofDrawRectangle(800,800,100,100);
	ofDrawRectangle(900, 600, 380, 50);//X 900~1280 Y 600~650 0
	ofDrawRectangle(750, 450, 380, 50);//X 750~1130 Y 450~500 1 
	ofDrawRectangle(900, 300, 380, 50);//X 900~1280 Y 300~350 2
	ofDrawRectangle(750, 150, 380, 50);//X 750~1130 Y 150~200 3
	ofDrawRectangle(900, 0, 380, 50);//X 900~1280 Y 0~50 4
	ofSetColor(255, 0, 0);
	ofDrawRectangle(750, 0, 150, 50);//goal X 750~900 Y 0~50
	//Map End
	//抓取顏色
	//抓取顏色 結束
	//判斷有沒有碰到 邊邊 或到紅色了
	//ofCircle(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 5);
	int centerOfCircleX = 0; 
	int centerOfCircleY = 0;
	if (IsBump(centerOfCircleX, centerOfCircleY))//碰撞了輸了
	{
		
	
	}
	else if ((centerOfCircleX + 5 >= 750 && centerOfCircleX + 5 <= 900)
		&& (centerOfCircleY >= 0 && centerOfCircleY <= 50)) //沒碰撞而且碰到紅色的 贏了
	{
	
	}

}
bool IsBump(int centerOfCircleX, int centerOfCircleY)
{
	bool IsLoser = false;
	for (int i = 0; i < 5; i++) // 前面直的長方形
	{
		int rangeOfY = (i % 2 == 0) ? 0 : 160;
		if ((centerOfCircleX + 5 >= 100 + i * 150 && centerOfCircleX + 5 <= 150 + i * 150) && (centerOfCircleY >= rangeOfY && centerOfCircleY <= rangeOfY + 800)) IsLoser = true;
		if ((centerOfCircleX - 5 >= 100 + i * 150 && centerOfCircleX - 5 <= 150 + i * 150) && (centerOfCircleY >= rangeOfY && centerOfCircleY <= rangeOfY + 800)) IsLoser = true;
		if ((centerOfCircleX >= 100 + i * 150 && centerOfCircleX <= 150 + i * 150) && (centerOfCircleY + 5 >= rangeOfY && centerOfCircleY + 5 <= rangeOfY + 800)) IsLoser = true;
		if ((centerOfCircleX >= 100 + i * 150 && centerOfCircleX <= 150 + i * 150) && (centerOfCircleY - 5 >= rangeOfY && centerOfCircleY - 5 <= rangeOfY + 800)) IsLoser = true;
		int rangeOfX = (i % 2 == 0) ? 900 : 750;
		if ((centerOfCircleX + 5 >= rangeOfX && centerOfCircleX + 5 <= rangeOfX + 380) && (centerOfCircleY >= 600 - i * 150 && centerOfCircleY <= 650 - i * 150)) IsLoser = true;
		if ((centerOfCircleX - 5 >= rangeOfX && centerOfCircleX - 5 <= rangeOfX + 380) && (centerOfCircleY >= 600 - i * 150 && centerOfCircleY <= 650 - i * 150)) IsLoser = true;
		if ((centerOfCircleX >= rangeOfX && centerOfCircleX <= rangeOfX + 380) && (centerOfCircleY + 5 >= 600 - i * 150 && centerOfCircleY + 5 <= 650 - i * 150)) IsLoser = true;
		if ((centerOfCircleX >= rangeOfX && centerOfCircleX <= rangeOfX + 380) && (centerOfCircleY - 5 >= 600 - i * 150 && centerOfCircleY - 5 <= 650 - i * 150)) IsLoser = true;
	}
	return IsLoser;
}
