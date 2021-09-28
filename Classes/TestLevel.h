#pragma once
#include "cocos2d.h"
#include "BaseLevel.h"
#pragma comment( lib, "Xinput9_1_0.lib" )  

using namespace cocos2d;


class TestLevel : public BaseLevel
{
public:
	CREATE_FUNC(TestLevel);
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
	Character * Wall;
	Character * Wall2;
	Character * Wall3;
	Character * Wall4;
	Character * Wall5;
	Character * Wall6;
	Character * Boundary1;
	Character * Boundary2;
	Character * Ceiling;
	Character * Button1;
	Sprite* ButtonBot;
	Sprite* ButtonBotShad;
	
	Sprite* move;
	Sprite* space;
	Sprite* shift;
	Sprite* shift2;
	Sprite* arrow;
	Sprite* arrow2;
	Sprite* swap;

	//Level Elements
	Sprite* door;
	Sprite* firstDoor;

	//This scene's physics world
	//Reference to the physics world used within the scene. Prevents having to call: director->getRunningScene()->getPhysicsWorld() every time we want to do something
	//HAS to be static because the create function we set its value in is a static function. The compiler will complain if we try to use a non-static member in a static function
	static PhysicsWorld* physicsWorld;

	static Scene* sceneHandle;

};


