#include "TestLevel.h"
#include "DashTransition.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"

USING_NS_CC;
using namespace Input;

Scene* TestLevel::createScene()
{
	//Background Music
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/tsgmusic.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/tsgmusic.mp3", true);
	//Effects
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/jump.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/dash.mp3");
	// 'scene' is an autorelease object
	Scene* scene = Scene::createWithPhysics();
	TestLevel* layer = TestLevel::create();
	scene->addChild(layer);
	sceneHandle = scene;
	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	//Get the physics world from the scene so that we can work with it later
	physicsWorld = scene->getPhysicsWorld();
	return scene;
}

void TestLevel::onExit()
{
	Scene::onExit();
}

void TestLevel::onEnter()
{
	DISPLAY->createDebugConsole(true);
	std::cout << "THE CONSOLE IS NOW OPEN" << std::endl;//uncoment this to remove console window
	Scene::onEnter();
}

// on "init" you need to initialize your instance
bool TestLevel::init()
{
	if (!BaseLevel::init())
	{
		return false;
	}
	//Get the director from cocos so we can use it when needed
	director = Director::getInstance();


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	setPosition(director->getWinSizeInPixels().width / 2, director->getWinSizeInPixels().height * 0.1);
	//Initialize Collision Callback
	initCollisionCallback();
	//Draw objects like background
	DrawWorld();
	//set screen boundry
	boundry.setRect(0, 0, 3445, 700);

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();
	//this->getCameras().erase( this->getCameras().end());
	return true;
}

void TestLevel::FlipWorld()
{
	BaseLevel::FlipWorld();
	if (Player->isShadow == false) {
		Player->getSprite()->getPhysicsBody()->resetForces();
		Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	else {
		Player->getShadow(0)->getSprite()->getPhysicsBody()->resetForces();
		Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	//flips everything to shadows
	Player->flipWorld(playerCollisionTag);
	Platform->flipWorld(wallCollisionTag);
	Platform2->flipWorld(wallCollisionTag);
	Platform3->flipWorld(wallCollisionTag);
	Wall->flipWorld(wallCollisionTag);
	Wall2->flipWorld(wallCollisionTag);
	Wall3->flipWorld(wallCollisionTag);
	//Wall4->flipWorld(wallCollisionTag);
	//Wall5->flipWorld(wallCollisionTag);
	Wall6->flipWorld(wallCollisionTag);
	Boundary1->flipWorld(wallCollisionTag);
	Boundary2->flipWorld(wallCollisionTag);
	Ceiling->flipWorld(wallCollisionTag);
	Button1->flipWorld(flag1Tag);
	for (int i = 0; i < Enemies.size(); i++)
		Enemies.at(i)->flipWorld(enemyCollisionTag);
	if (Player->isShadow == false) {
		Player->getSprite()->getPhysicsBody()->resetForces();
		Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	else {
		Player->getShadow(0)->getSprite()->getPhysicsBody()->resetForces();
		Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
}

void TestLevel::update(float deltaTime)//UPDATE LOOP
{

	physicsWorld->setGravity(Vec2(0.0f, -1000.0f));//gravity

	if (gamePaused == false) {
		for (int i = 0; i < Enemies.size(); i++)
			Enemies.at(i)->update(deltaTime, Player->getPosition());//update enemy
	}
	//Enable Scrolling
	if (Player->isShadow == false) {
		if (mask->getOpacity() <= 1) {
			Player->update(deltaTime);//update 
			director->getRunningScene()->runAction(Follow::createWithOffset(Player->getSprite(), 0, -100, boundry));
		}
		else {
			//Shadow DashTrail
			if (blurctr >= 2) {
				auto blur = Sprite::create("UA/Player/character.png");
				blur->setPosition(Player->getShadow(0)->getSprite()->getPosition());
				blur->setRotation(0);
				blur->setScale(0.7f);
				blur->setAnchorPoint(Vec2(0.5f, 0.5f));
				blur->setOpacity(120);
				if (Player->getShadow(0)->getSprite()->isFlippedX() == true)
					blur->setFlippedX(true);
				this->addChild(blur, -60);
				blur->setColor(Color3B(0, 0, 0));
				//blur->runAction(TintTo::create(0.001f, Color3B(0, 0, 0)));
				blur->runAction(Sequence::create(FadeOut::create(0.2f), RemoveSelf::create(), NULL));
				blurlist.pushBack(blur);
				blurctr = 0;
			}
			blurctr++;
			for (int i = 0; i < blurlist.size(); i++) {
				if (blurlist.at(i)->getOpacity() == 0) {
					blurlist.erase(blurlist.begin() + i);
				}
			}
		}
	}
	else {
		if (mask->getOpacity() >= 254) {
			director->getRunningScene()->runAction(Follow::createWithOffset(Player->getShadow(0)->getSprite(), 0, -100, boundry));
			Player->update(deltaTime);//update 

		}
	}

	//fading elements
	if (Player->getSprite()->getPosition().x > move->getPosition().x + 50) {
		if (move->getOpacity() > 5) move->setOpacity(move->getOpacity() - 2);
	}
	if (Player->getSprite()->getPosition().x > space->getPosition().x + 100) {
		if (space->getOpacity() > 5) space->setOpacity(space->getOpacity() - 2);
	}
	//if (Player->getSprite()->getPosition().x > shift->getPosition().x) {
	//	if (shift->getOpacity() > 5) shift->setOpacity(shift->getOpacity() - 2);
	//}
	//if (Player->getShadow(0)->getSprite()->getPosition().x > shift2->getPosition().x) {
	//	if (shift2->getOpacity() > 5) shift2->setOpacity(shift2->getOpacity() - 2);
	//}
	if (Player->getSprite()->getPosition().x > arrow->getPosition().x + 200) {
		if (arrow->getOpacity() > 5) arrow->setOpacity(arrow->getOpacity() - 1);
		if (arrow2->getOpacity() > 5) arrow2->setOpacity(arrow2->getOpacity() - 1);
	}
	if (Player->getSprite()->getPosition().x > swap->getPosition().x + 200) {
		if (swap->getOpacity() > 5) swap->setOpacity(swap->getOpacity() - 2);
	}

	//Load the next level after the tutorial
	if (black->isFlippedY() == true) {
		std::cout << "level1" << std::endl;
		this->stopAllActions();
		this->removeAllComponents();
		cocos2d::CCDirector::sharedDirector()->purgeCachedData();
		SpriteFrameCache::getInstance()->removeSpriteFrames();
		SpriteFrameCache::destroyInstance();
		this->cleanup();
		DISPLAY->init(1000.0f, 500.0f, "Shadow Game (Stalactites)", false);
		Scene* level1 = DashTransition::createScene();
		director->getInstance()->replaceScene(level1);
	}
	else if (Player->getSprite()->getPosition().x >= 3315 && Player->getSprite()->getPosition().y <= 210)
	{
		if (black->isFlippedX() == false) {
			black->setPosition(Player->getPosition());
			black->setFlippedX(true);
			black->runAction(Sequence::createWithTwoActions(FadeIn::create(0.5f), FlipY::create(true)));
		}
	}

	//Health bar
	if ((Player->health <= 0 && Player->isShadow == false) || Player->getSprite()->getPosition().y < -20)
	{
		Player->getSprite()->stopAllActions();
		Player->getSprite()->runAction(TintTo::create(0.01, Color3B(255, 255, 255)));
		Player->getShadow(0)->getSprite()->stopAllActions();
		Player->getSprite()->setPosition(140, 150);
		Player->getShadow(0)->getSprite()->setPosition(115, 175);
		std::cout << "u dead" << std::endl;
		Player->health = 3;Player->health = 3;
		Player->healthbar->setScale(0.01f);
		Player->healthbar->setTexture("UA/Player/healthbar0.png");
		//Player->healthframe->stopAllActions();
		Player->healthbar->stopAllActions();
		Player->healthbar->runAction(
			Sequence::createWithTwoActions(
				Sequence::createWithTwoActions(
					FadeIn::create(0.2f), ScaleTo::create(0.5f, 0.1f, 0.1f)),
				Sequence::createWithTwoActions(
					Blink::create(0.3f, 3), FadeOut::create(0.5f))
			));
		//Player->healthframe->runAction(
		//	Sequence::createWithTwoActions(
		//		Sequence::createWithTwoActions(
		//			FadeIn::create(0.2f), MoveBy::create(0.5f, Vec3(0, 0, 0))),
		//		Sequence::createWithTwoActions(
		//			MoveBy::create(0.3f, Vec3(0, 0, 0)), FadeOut::create(0.5f))
		//	));
		//if (Player->isShadow == false)
			Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
		//else
			//Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
	}
	//For when the player is a shadow, they should only die after one hit
	if (mask->getOpacity() > 254 && Player->isShadow == true && ((Player->getShadow(0)->health <= 0) || Player->getShadow(0)->getSprite()->getPosition().y < -20))
	{
		//Player->getSprite()->stopAllActions();
		//Player->getShadow(0)->getSprite()->stopAllActions();

		//Player->getShadow(0)->getSprite()->setPosition(Player->getSprite()->getPosition().x - 25, Player->getSprite()->getPosition().y + 25);
		//Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));

		//flips everything to shadows
		FlipWorld();

		Player->getShadow(0)->health = 1;
	}
	

	//Update everything
	//UpdatePositions(deltaTime);
	updateInputs();
	//CheckCollision();
	if (grounded == true)
		falling = false;
	if (onWall == true) {
		if (right == true) {
			Player->getSprite()->setFlippedX(false);
			Player->getShadow(0)->getSprite()->setFlippedX(false);
		}
		else {
			Player->getSprite()->setFlippedX(true);
			Player->getShadow(0)->getSprite()->setFlippedX(true);
		}
	}


	//THIS NEEDS TO BE CALLED DO NOT REMOVE
	INPUTS->clearForNextFrame();
}


void TestLevel::UpdatePositions(float dt)
{
	//not in use
}

bool TestLevel::checkEnd()
{
	//not in use
	return false;
}

void TestLevel::CheckCollision()
{
	
	//not in use
}

void TestLevel::initCollisionCallback()
{
	//Create the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	//Assign the callback function
	contactListener->onContactBegin = CC_CALLBACK_1(TestLevel::onContactBeginCallback, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(TestLevel::onSepBeginCallback, this);
	//Add the contact listener to the event dispatcher
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}



bool TestLevel::onContactBeginCallback(PhysicsContact& contact)
{
	//Get the two nodes that took part in the collision
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	//Get the collision tags from the nodes
	int tagA = nodeA->getPhysicsBody()->getTag();
	int tagB = nodeB->getPhysicsBody()->getTag();

	//Check to ensure both nodes actually exist, just in case. If they didn't just return false
	if (nodeA && nodeB)
	{
		if (BaseLevel::onContactBeginCallback(contact)) {
			return true;
		}
		//PLAYER COLLISONS
		else if (tagA == playerCollisionTag)
		{
			if (tagB == flag1Tag)
			{
				//reset jump and dash
				candash = true;
				dash = 0;
				falling = false;
				grounded = true;
				//shift->setVisible(false);
				//remove bounce
				if (Player->isShadow == false) {
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					shift->runAction(FadeOut::create(1.0f));
					Button1->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Wall6->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					Wall6->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					//Button1->getShadow(0)->getSprite()->setPosition(3630, 120);
				}
				else if (Player->isShadow == true) {
					shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button1->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Wall3->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					//Wall6->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -50)));
					//Button1->getSprite()->setPosition(1800, 95);
				}
				return true;
			}
		}
		else if (tagB == playerCollisionTag)
		{
			if (tagA == flag1Tag)
			{
				//reset jump and dash
				candash = true;
				dash = 0;
				falling = false;
				grounded = true;
				//shift->setVisible(false);
				//remove bounce
				if (Player->isShadow == false) {
					shift->runAction(FadeOut::create(1.0f));
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button1->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Wall6->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					Wall6->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					//Button1->getShadow(0)->getSprite()->setPosition(3630, 120);
				}
				else if (Player->isShadow == true) {
					shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button1->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Wall3->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					//Wall6->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -50)));
					//Button1->getSprite()->setPosition(1800, 95);
				}
				return true;
			}
		}
		else
		{
			//If it was another form of collision, just return false
			return false;
		}
	}
	else {
		return false; //If the nodes don't exist, just return false
	}
	return false;
}


void TestLevel::DrawWorld()
{
	//Creating the background
	background = Sprite::create("UA/Background/Warehouse2.png");
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(965, 675);
	background->setPositionZ(-250);
	background->setScale(0.9f, 0.9f);
	this->addChild(background, -100);

	move = Sprite::create("UA/Background/move.png");
	move->setAnchorPoint(Vec2(0.5f, 0.5f));
	move->setPosition(400, 170);
	move->setScale(0.4f, 0.4f);
	this->addChild(move, -50);

	space = Sprite::create("UA/Background/jump.png");
	space->setAnchorPoint(Vec2(0.5f, 0.5f));
	space->setPosition(910, 175);
	space->setScale(0.4f, 0.4f);
	this->addChild(space, -50);

	shift = Sprite::create("UA/Background/shift.png");
	shift->setAnchorPoint(Vec2(0.5f, 0.5f));
	shift->setPosition(1515, 135);
	shift->setScale(0.4f, 0.4f);
	this->addChild(shift, -50);

	shift->runAction(Repeat::create(Sequence::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 20)), MoveBy::create(1.0f, Vec2(0, -20))), 9999));

	shift2 = Sprite::create("UA/Background/shift.png");
	shift2->setAnchorPoint(Vec2(0.5f, 0.5f));
	shift2->setPosition(3095, 160);
	shift2->setScale(0.5f, 0.5f);
	this->addChild(shift2, -50);

	shift2->runAction(Repeat::create(Sequence::createWithTwoActions(MoveBy::create(1.0f, Vec2(0, 20)), MoveBy::create(1.0f, Vec2(0, -20))), 9999));

	arrow = Sprite::create("UA/Background/arrow1.png");
	arrow->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrow->setPosition(2055, 170);
	arrow->setScale(0.2f, 0.2f);
	this->addChild(arrow, -50);

	arrow2 = Sprite::create("UA/Background/arrow1.png");
	arrow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrow2->setPosition(2055, 285);
	arrow2->setScale(0.2f, 0.2f);
	arrow2->setFlippedX(true);
	this->addChild(arrow2, -50);

	swap = Sprite::create("UA/Background/switch.png");
	swap->setAnchorPoint(Vec2(0.5f, 0.5f));
	swap->setPosition(2590, 170);
	swap->setScale(0.4f, 0.4f);
	this->addChild(swap, -50);

	//Create Platform 1
	Sprite * platform;
	platform = Sprite::create("UA/Background/platform1.png");
	platform->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform->setPosition(415, 20);
	platform->setScale(0.5f, 0.5f);
	Sprite * platformshadow;
	platformshadow = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow->setPosition(390, 45);
	platformshadow->setScale(0.5f, 0.5f);
	///Add to character object
	Character * _platshad = new Character(platformshadow);
	Platform = new Character(platform, _platshad);
	this->addChild(Platform->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform->getShadow(0)->getSprite(), -51);//z = -50
	Platform->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform
	Sprite * platform2;
	platform2 = Sprite::create("UA/Background/platform2.png");
	platform2->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform2->setPosition(2465, 20);
	platform2->setScale(0.5f, 0.5f);
	Sprite * platformshadow2;
	platformshadow2 = Sprite::create("UA/Background/platform2_shadow.png");
	platformshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow2->setPosition(2440, 45);
	platformshadow2->setScale(0.5f, 0.5f);
	///Add to character object
	Character * _platshad2 = new Character(platformshadow2);
	Platform2 = new Character(platform2, _platshad2);
	this->addChild(Platform2->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform2->getShadow(0)->getSprite(), -51);//z = -50
	Platform2->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform for jump
	Sprite * platform3;
	platform3 = Sprite::create("UA/Background/platform3.png");
	platform3->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform3->setPosition(915, 0);
	platform3->setScale(0.5f, 0.5f);
	Sprite * platformshadow3;
	platformshadow3 = Sprite::create("UA/Background/platform3_shadow.png");
	platformshadow3->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow3->setPosition(890, 25);
	platformshadow3->setScale(0.5f, 0.5f);
	///Add to character object
	Character * _platshad3 = new Character(platformshadow3);
	Platform3 = new Character(platform3, _platshad3);
	this->addChild(Platform3->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform3->getShadow(0)->getSprite(), -53);//z = -50
	Platform3->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform3->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall
	Sprite * wall;
	wall = Sprite::create("UA/Background/wall.png");
	wall->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall->setPosition(1965, 950);
	Sprite * wallshadow;
	wallshadow = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow->setPosition(1940, 975);
	///add to character object
	Character * _wallshad = new Character(wallshadow);
	Wall = new Character(wall, _wallshad);
	this->addChild(Wall->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Wall->getShadow(0)->getSprite(), -50);// z = -50
	Wall->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall
	Sprite* wall2;
	wall2 = Sprite::create("UA/Background/wall.png");
	wall2->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall2->setPosition(2165, 215);
	wall2->setScaleY(0.2);
	Sprite* wallshadow2;
	wallshadow2 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow2->setPosition(2140, 240);
	wallshadow2->setScaleY(0.2);
	///add to character object
	Character * _wallshad2 = new Character(wallshadow2);
	Wall2 = new Character(wall2, _wallshad2);
	this->addChild(Wall2->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Wall2->getShadow(0)->getSprite(), -50);// z = -50 (way behind player)
	Wall2->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall with no shadow
	Sprite* wall3;
	wall3 = Sprite::create("UA/Background/wall.png");
	wall3->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall3->setPosition(2865, 370);
	wall3->setScaleY(0.4);
	Sprite* wallshadow3;
	wallshadow3 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow3->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow3->setPosition(100000, 100000);
	wallshadow3->setScale(0.1, 0.1);
	///add to character object
	Character * _wallshad3 = new Character(wallshadow3);
	Wall3 = new Character(wall3, _wallshad3);
	this->addChild(Wall3->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Wall3->getShadow(0)->getSprite(), -50);// z = -50 (way behind player)
	Wall3->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall3->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall
	/*Sprite* wall4;
	wall4 = Sprite::create("UA/Background/wall.png");
	wall4->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall4->setPosition(1290, 43);
	wall4->setScaleY(0.1);
	Sprite* wallshadow4;
	wallshadow4 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow4->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow4->setPosition(1265, 68);
	wallshadow4->setScaleY(0.1);
	///add to character object
	Character * _wallshad4 = new Character(wallshadow4);
	Wall4 = new Character(wall4, _wallshad4);
	this->addChild(Wall4->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Wall4->getShadow(0)->getSprite(), -50);// z = -50 (way behind player)
	Wall4->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall4->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall
	Sprite* wall5;
	wall5 = Sprite::create("UA/Background/wall.png");
	wall5->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall5->setPosition(1555, 43);
	wall5->setScaleY(0.1);
	Sprite* wallshadow5;
	wallshadow5 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow5->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow5->setPosition(1530, 68);
	wallshadow5->setScaleY(0.1);
	///add to character object
	Character * _wallshad5 = new Character(wallshadow5);
	Wall5 = new Character(wall5, _wallshad5);
	this->addChild(Wall5->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Wall5->getShadow(0)->getSprite(), -50);// z = -50 (way behind player)
	Wall5->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall5->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);*/

	//Create Wall
	Sprite* wall6;
	wall6 = Sprite::create("UA/Background/wall.png");
	wall6->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall6->setPosition(1720, 325);
	wall6->setScaleY(0.35);
	Sprite* wallshadow6;
	wallshadow6 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow6->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow6->setPosition(1695, 350);
	wallshadow6->setScaleY(0.35);
	///add to character object
	Character * _wallshad6 = new Character(wallshadow6);
	Wall6 = new Character(wall6, _wallshad6);
	this->addChild(Wall6->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Wall6->getShadow(0)->getSprite(), -50);// z = -50 (way behind player)
	Wall6->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall6->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Left Boundary Wall
	Sprite* boundary1;
	boundary1 = Sprite::create("UA/Background/wall.png");
	boundary1->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundary1->setPosition(75, 270);
	boundary1->setScaleY(0.4);
	Sprite* boundaryshadow1;
	boundaryshadow1 = Sprite::create("UA/Background/wall_shadow.png");
	boundaryshadow1->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundaryshadow1->setPosition(50, 295);
	boundaryshadow1->setScaleY(0.4);
	///add to character object
	Character * _boundshad1 = new Character(boundaryshadow1);
	Boundary1 = new Character(boundary1, _boundshad1);
	this->addChild(Boundary1->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Boundary1->getShadow(0)->getSprite(), -50);// z = -50 (way behind player)
	Boundary1->getSprite()->getPhysicsBody()->setDynamic(false);
	Boundary1->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	Boundary1->getSprite()->setFlippedX(true);

	//Create Right Boundary Wall
	Sprite* boundary2;
	boundary2 = Sprite::create("UA/Background/wall.png");
	boundary2->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundary2->setPosition(3365, 270);
	boundary2->setScaleY(0.4);
	Sprite* boundaryshadow2;
	boundaryshadow2 = Sprite::create("UA/Background/wall_shadow.png");
	boundaryshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundaryshadow2->setPosition(3340, 295);
	boundaryshadow2->setScaleY(0.4);
	///add to character object
	Character * _boundshad2 = new Character(boundaryshadow2);
	Boundary2 = new Character(boundary2, _boundshad2);
	this->addChild(Boundary2->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Boundary2->getShadow(0)->getSprite(), -50);// z = -50 (way behind player)
	Boundary2->getSprite()->getPhysicsBody()->setDynamic(false);
	Boundary2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Ceiling
	Sprite * ceiling;
	ceiling = Sprite::create("UA/Background/ceiling.png");
	ceiling->setAnchorPoint(Vec2(0.5f, 0.5f));
	ceiling->setPosition(1415, 625);
	ceiling->setScale(3.0f, 0.5f);
	Sprite * ceilingshadow;
	ceilingshadow = Sprite::create("UA/Background/ceiling_shadow.png");
	ceilingshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	ceilingshadow->setPosition(1390, 650);
	ceilingshadow->setScale(3.0f, 0.5f);
	///Add to character object
	Character * _ceilingshad = new Character(ceilingshadow);
	Ceiling = new Character(ceiling, _ceilingshad);
	this->addChild(Ceiling->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Ceiling->getShadow(0)->getSprite(), -50);//z = -50
	Ceiling->getSprite()->getPhysicsBody()->setDynamic(false);
	Ceiling->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Button
	Sprite* button;
	button = Sprite::create("UA/Level/ButtonTop.png");
	button->setAnchorPoint(Vec2(0.5f, 0.5f));
	button->setPosition(1515, 108);
	Sprite* buttonShadow;
	buttonShadow = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadow->setPosition(3095, 133);

	//Create button aesthetics
	ButtonBot = Sprite::create("UA/Level/ButtonBottom.png");
	ButtonBot->setAnchorPoint(Vec2(0.5f, 0.5f));
	ButtonBot->setPosition(1515, 108);
	this->addChild(ButtonBot, 1);

	ButtonBotShad = Sprite::create("UA/Level/ButtonBottomShadow.png");
	ButtonBotShad->setAnchorPoint(Vec2(0.5f, 0.5f));
	ButtonBotShad->setPosition(3095, 133);
	this->addChild(ButtonBotShad, -50);

	///add to character object
	Character * _buttonShad = new Character(buttonShadow);
	Button1 = new Character(button, _buttonShad);
	this->addChild(Button1->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Button1->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	Button1->getSprite()->getPhysicsBody()->setDynamic(false);
	Button1->getSprite()->getPhysicsBody()->setTag(flag1Tag);

	door = Sprite::create("UA/Level/door2.png");
	door->setAnchorPoint(Vec2(0.5f, 0.5f));
	door->setPosition(3323, 176);
	door->setScale(0.5f, 0.5f);
	this->addChild(door, -48);

	firstDoor = Sprite::create("UA/Level/closedDoor.png");
	firstDoor->setAnchorPoint(Vec2(0.5f, 0.5f));
	firstDoor->setPosition(114, 176);
	firstDoor->setScale(0.5f, 0.5f);
	this->addChild(firstDoor, -48);
}
//Init the static physics world pointer. Set it to be a nullptr which means it points to nothing
PhysicsWorld* TestLevel::physicsWorld = nullptr;
Scene* TestLevel::sceneHandle = nullptr;