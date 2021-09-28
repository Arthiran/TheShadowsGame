#pragma once
#include "cocos2d.h"
#include <iostream>
#include <fstream>
#include <ui\UITextField.h>
#include <Windows.h>
//#include "Character.h"
#include "ShadowChar.h"
#include "controller.h"
#include "SplashScreen.h"
#pragma comment( lib, "Xinput9_1_0.lib" ) 
using namespace cocos2d;


class BaseLevel : public cocos2d::Scene
{
public:
	CREATE_FUNC(BaseLevel);
	static cocos2d::Scene* createScene();
	virtual void onExit();
	virtual void onEnter();
	virtual bool init();
	virtual void update(float deltaTime) {}
	void updateInputs();
	void updateControllerInputs();
	void updateKeyboardInputs();

	void initCollisionCallback();
	virtual bool onContactBeginCallback(PhysicsContact& contact);
	bool onSepBeginCallback(PhysicsContact& contact);
	// a selector callback
	void DrawWorld();

	//pause

	virtual void FlipWorld();
	unsigned int fadectr;

	//controller
	Input::XBoxInput XBoxController;
	bool Aold, Anew, Bold, Bnew, Yold, Ynew, Xold, Xnew, Snew, Sold;
	bool RBold, RBnew, LBold, LBnew, RTold, RTnew, LTold, LTnew;
	bool pad;

	float lTrig, rTrig;

	Rect boundry;

	Sprite* healthbar_;
	Sprite* mask;

	float zoom = 1.0f;
	bool done = true;
	//states
	Vec2* PlayerPosition;
	bool right = true;
	bool onWall = false;
	bool falling = false;
	float jump = 0;
	bool grounded = false;
	float dash = 0;
	bool candash = true;
	bool dead = false;

	unsigned int playerCollisionTag = 0;
	unsigned int enemyCollisionTag = 1;
	unsigned int wallCollisionTag = 2;
	unsigned int flag1Tag = 3;
	unsigned int attackTag = 4;
	unsigned int flag2Tag = 5;
	unsigned int flag3Tag = 6;
	unsigned int flag4Tag = 7;
	unsigned int flag5Tag = 8;

	//
protected:
	//Engine
	Director* director;
	bool gamePaused;
	int gameSpeed;

	Repeat* walking;
	Repeat* idle;
	Animate* jumpP;
	Repeat* walkingS;
	Repeat* idleS;
	Animate* jumpS;
	Animate* attack;
	Animate* attackS;

	//Enemies
	Animate* enemWalkP;
	Animate* enemWalkS;
	
	Sprite* pauseicon;
	Sprite* pauseoverlay;

	Character * Player;
	std::vector<Character*> Enemies;
	//FX
	Vector<Sprite*> dustlist;
	int dustctr = 0;
	Vector<Sprite*> blurlist;
	int blurctr = 0;

	//Background
	Sprite* background;
	Sprite* black;

	//This scene's physics world
	//Reference to the physics world used within the scene. Prevents having to call: director->getRunningScene()->getPhysicsWorld() every time we want to do something
	//HAS to be static because the create function we set its value in is a static function. The compiler will complain if we try to use a non-static member in a static function
	static PhysicsWorld* physicsWorld;

	static Scene* sceneHandle;

};



