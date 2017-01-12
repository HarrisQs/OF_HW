#include "ofApp.h"
#include <string>

using namespace ofxCv;
using namespace cv;
bool IsBump(int centerOfCircleX, int centerOfCircleY);
void ofApp::setup() 
{
	ofSetVerticalSync(true);//是個起始必備的!?
	ofSetFrameRate(120);//給螢幕刷新速度一個目標!
	cam.setup(1280, 960);//攝影機投出的大小
	ofEnableAlphaBlending();//混和的 在這裡不知道混啥= =?
	rgb.allocate(1280, 960);
	filtered.allocate(1280, 960);
	red.allocate(1280, 960);
	green.allocate(1280, 960);
	blue.allocate(1280, 960);
	synth.load("sounds/bomb.mp3");
	synth.setVolume(0.75f);
	Win.load("sounds/crrect_answer3.mp3");
	Win.setVolume(0.75f);
	font.load("Sudbury_Basin_3D.ttf", 26);
}

void ofApp::update() 
{
	cam.update();
	ofSoundUpdate();
	if (cam.isFrameNew()) {

		//copy webcam pixels to rgb image
		//rgb.setFromPixels(movie.getPixels(), w, h);
		rgb.setFromPixels(cam.getPixels());

		//store the three channels as grayscale images

		rgb.convertToGrayscalePlanarImages(red, green, blue);

		green += blue;   // adding green and blue channels then will subtract from red chanel to filter out only red
		red -= green;
		//filter image based on the hue value were looking for
		for (int i = 0 ; i < 1280 * 960 ; i++) {
			filtered.getPixels()[i] = ofInRange(red.getPixels()[i], 0, 40) ? 0 : 255;
		}

		filtered.flagImageChanged();
		//run the contour finder on the filtered image to find blobs with a certain hue
		contours.findContours(filtered, 50, 1280*960 / 2, 1, false);//輪廓
	}
}

void ofApp::draw() 
{
	if (isBeginGame)
	{
		IsFirst = false;
		ofSetColor(255, 255, 255);
		cam.draw(0, 0);//把攝影機的畫面畫出來
		//Map
		ofSetColor(255, 255, 0);
		ofDrawRectangle(100, 0, 50, 800);//X 100~150 Y 0~800 0
		ofDrawRectangle(250, 160, 50, 800);//X 250~300 Y 160~960 1
		ofDrawRectangle(400, 0, 50, 800);//X 400~450 Y 0~800 2
		ofDrawRectangle(550, 160, 50, 800);//X 550~600 Y 160~960 3
		ofDrawRectangle(700, 0, 50, 800);//X 700~750 Y 0~800 4
		ofDrawRectangle(800, 800, 100, 100);
		ofDrawRectangle(900, 600, 380, 50);//X 900~1280 Y 600~650 0
		ofDrawRectangle(750, 450, 380, 50);//X 750~1130 Y 450~500 1 
		ofDrawRectangle(900, 300, 380, 50);//X 900~1280 Y 300~350 2
		ofDrawRectangle(750, 150, 380, 50);//X 750~1130 Y 150~200 3
		ofDrawRectangle(900, 0, 380, 50);//X 900~1280 Y 0~50 4
		ofSetColor(255, 0, 0);
		ofDrawRectangle(750, 0, 150, 50);//goal X 750~900 Y 0~50
		//Map End
		//抓取顏色
		contours.draw(0, 0);
		ofSetColor(255, 255, 0);
		ofFill();
		//draw red circles for found blobs
		for (int i = 0; i < contours.nBlobs; i++) {
			ofCircle(contours.blobs[i].centroid.x, contours.blobs[i].centroid.y, 5);
			int centerOfCircleX = contours.blobs[i].centroid.x;
			int centerOfCircleY = contours.blobs[i].centroid.y;
			if (IsBump(centerOfCircleX, centerOfCircleY))//碰撞了輸了
			{
				LoseOrWin = false;
				isBeginGame = false;
				synth.play();

			}
			else if ((centerOfCircleX + 5 >= 750 && centerOfCircleX + 5 <= 900)
				&& (centerOfCircleY >= 0 && centerOfCircleY <= 50)) //沒碰撞而且碰到紅色的 贏了
			{
				isBeginGame = false;
				LoseOrWin = true;
				Win.play();
			}
		}
		//抓取顏色 結束
	}
	else
	{
		ofSetColor(255, 255, 255);
		cam.draw(0, 0);
		ofSetColor(0, 255, 255);
		ofDrawRectangle(420, 325, 500, 250);//X 550~600 Y 160~960 3
		ofSetColor(0, 0, 255);
		font.drawString("Let's Play Game !!", 450, 365);
		font.drawString("Press 's' play game. ", 430, 405);
		ofSetColor(255, 0, 0);
		if (!IsFirst)
			if (LoseOrWin)//WIn
				font.drawString("Congratulations!!", 480, 465);
			else//Lose
				font.drawString("You Lose!", 550, 465);	
		
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
void ofApp::keyPressed(int key) 
{
	if (key == 's')//Start Game
	{
		isBeginGame = true;
	}
}
