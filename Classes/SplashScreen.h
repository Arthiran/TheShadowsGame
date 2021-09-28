#pragma once
#include "cocos2d.h"
#include <iostream>
#include <fstream>
#include <ui\UITextField.h>
#include <Windows.h>
#include "controller.h"
//#pragma lib("Xinput9_1_0.lib")
#pragma comment( lib, "Xinput9_1_0.lib" )  

using namespace cocos2d;

class SplashScreen : public cocos2d::Scene
{
public:
	CREATE_FUNC(SplashScreen);
	static cocos2d::Scene* createScene();
	virtual void onExit();
	virtual void onEnter();
	virtual bool init();
	void DrawWorld();
	void update(float deltaTime);
	Input::XBoxInput XBoxController;
	unsigned int cycle = 0;


	Vector<SpriteFrame*> coverFrame;
	Vector<SpriteFrame*> blankFrame;
	Vector<SpriteFrame*> roomFrame;
	Vector<SpriteFrame*> introFrame;

	Animation* animation6;
	Animation* animation8;
	Animation* animation9;
	Animation* animation14;

	Sequence* flip;
	Sequence* fullting;
	CCSprite* splash;

private:
	//Engine
	Director* director;
	//Background
	Sprite* background;
	Sprite* white;
	Sprite* start;

	//static PhysicsWorld* physicsWorld;

	static Scene* sceneHandle;
};