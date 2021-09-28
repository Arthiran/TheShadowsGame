#pragma once
#include "cocos2d.h"
#include "BaseLevel.h"
#pragma comment( lib, "Xinput9_1_0.lib" )  

using namespace cocos2d;


class LevelFour : public BaseLevel
{
public:
	CREATE_FUNC(LevelFour);
	static cocos2d::Scene* createScene();
	virtual void onExit();
	virtual void onEnter();
	virtual bool init();
	void update(float deltaTime);

	void FlipWorld();

	//Stuff
	void UpdatePositions(float dt);
	bool checkEnd();
	void CheckCollision();

	void initCollisionCallback();
	bool onContactBeginCallback(PhysicsContact& contact);
	//bool onSepBeginCallback(PhysicsContact& contact);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void DrawWorld();

	//Rect boundry;

private:

	//Engine
	Character * Platform;
	Character * Platform2;
	Character * Platform3;
	Character * Platform4;
	Character * Platform5;
	Character * Platform6;
	Character * Platform7;
	Character * Platform8;
	Character * Platform9;
	Character * Platform10;
	Character * Platform11;
	Character * Platform12;
	Character * Platform13;
	Character * Platform14;
	Character * Platform15;
	Character * Platform16;
	Character * Platform17;
	Character * Platform18;
	Character * Platform19;
	Character * Wall;
	Character * Wall2;
	Character * Wall3;
	Character * Wall4;
	Character * Wall5;
	Character * Wall6;
	Character * Wall7;
	Character * Wall8;
	Character * Wall9;
	Character * Wall10;
	Character * Wall11;
	Character * Wall12;
	Character * Wall13;
	Character * Wall14;
	Character * Wall15;
	Character * Wall16;
	Character * Wall17;
	Character * Boundary1;
	Character * Boundary2;
	Character * Ceiling;
	Character * Ceiling2;
	Character * ButtonTop;
	Character * ButtonTop2;
	Character * ButtonTop3;
	Character * ButtonTop4;
	Character * ButtonTop5;

	//Sprite* dashText;
	Sprite* door;
	Sprite* firstDoor;
	Sprite* buttonBottom;
	Sprite* buttonBottom2;
	Sprite* buttonBottom3;
	Sprite* buttonBottom4;
	Sprite* buttonBottom5;

	//Level Elements

	//This scene's physics world
	//Reference to the physics world used within the scene. Prevents having to call: director->getRunningScene()->getPhysicsWorld() every time we want to do something
	//HAS to be static because the create function we set its value in is a static function. The compiler will complain if we try to use a non-static member in a static function
	static PhysicsWorld* physicsWorld;

	static Scene* sceneHandle;

};


