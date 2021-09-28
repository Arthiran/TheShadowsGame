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
private:
	//Engine
	Director* director;
	//Background
	Sprite* background;
	
	static PhysicsWorld* physicsWorld;

	static Scene* sceneHandle;
};