#include "DashLevel.h"
#include "Transition.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"

USING_NS_CC;
using namespace Input;

Scene* DashLevel::createScene()
{
	//Background Music
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/game_music.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/game_music.mp3", true);
	//Effects
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/jump.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/dash.mp3");
	// 'scene' is an autorelease object
	Scene* scene = Scene::createWithPhysics();
	DashLevel* layer = DashLevel::create();
	scene->addChild(layer);
	sceneHandle = scene;
	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	//Get the physics world from the scene so that we can work with it later
	physicsWorld = scene->getPhysicsWorld();
	return scene;
}

void DashLevel::onExit()
{
	Scene::onExit();
}

void DashLevel::onEnter()
{
	DISPLAY->createDebugConsole(true);
	std::cout << "THE CONSOLE IS NOW OPEN" << std::endl;//uncoment this to remove console window
	Scene::onEnter();
}

// on "init" you need to initialize your instance
bool DashLevel::init()
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

void DashLevel::FlipWorld()
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
	Platform4->flipWorld(wallCollisionTag);
	Platform5->flipWorld(wallCollisionTag);
	//Wall->flipWorld(wallCollisionTag);
	//Wall2->flipWorld(wallCollisionTag);
	//Wall3->flipWorld(wallCollisionTag);
	Wall4->flipWorld(wallCollisionTag);
	//Wall5->flipWorld(wallCollisionTag);
	//Wall6->flipWorld(wallCollisionTag);
	Boundary1->flipWorld(wallCollisionTag);
	Boundary2->flipWorld(wallCollisionTag);
	Ceiling->flipWorld(wallCollisionTag);
	//Button1->flipWorld(flag1Tag);
	//Enemies->flipWorld(enemyCollisionTag);
	if (Player->isShadow == false) {
		Player->getSprite()->getPhysicsBody()->resetForces();
		Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
		
	}
	else {
		Player->getShadow(0)->getSprite()->getPhysicsBody()->resetForces();
		Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(0, 0));
		
	}
}

void DashLevel::update(float deltaTime)//UPDATE LOOP
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
	//Load the next level after the tutorial
	if (black->isFlippedY() == true) {
		std::cout << "level2" << std::endl;
		this->stopAllActions();
		this->removeAllComponents();
		cocos2d::CCDirector::sharedDirector()->purgeCachedData();
		SpriteFrameCache::getInstance()->removeSpriteFrames();
		SpriteFrameCache::destroyInstance();
		this->cleanup();
		DISPLAY->init(1000.0f, 500.0f, "Shadow Game (Stalactites)", false);
		Scene* level2 = Transition::createScene();
		director->getInstance()->replaceScene(level2);
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
		Player->health = 3;
		Player->healthbar->setScale(0.01f);
		Player->healthbar->setTexture("UA/Player/healthbar0.png");
		Player->healthframe->stopAllActions();
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


void DashLevel::UpdatePositions(float dt)
{
	//not in use
}

bool DashLevel::checkEnd()
{
	//not in use
	return false;
}

void DashLevel::CheckCollision()
{

	//not in use
}

void DashLevel::initCollisionCallback()
{
	//Create the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	//Assign the callback function
	contactListener->onContactBegin = CC_CALLBACK_1(DashLevel::onContactBeginCallback, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(DashLevel::onSepBeginCallback, this);
	//Add the contact listener to the event dispatcher
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}



bool DashLevel::onContactBeginCallback(PhysicsContact& contact)
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
				}
				else if (Player->isShadow == true) {
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
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
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 0));
				}
				else if (Player->isShadow == true) {
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
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


void DashLevel::DrawWorld()
{
	///ALL SHADOWS ARE OFFSET BY Vec2(-25,25)


	//Creating the background
	background = Sprite::create("UA/Background/Warehouse2.png");
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(965, 675);
	background->setPositionZ(-250);
	background->setScale(0.9f, 0.9f);
	this->addChild(background, -100);

	dashText = Sprite::create("UA/Background/dash.png");
	dashText->setAnchorPoint(Vec2(0.5f, 0.5f));
	dashText->setPosition(465, 160);
	dashText->setScale(0.4f, 0.4f);
	this->addChild(dashText, -50);

	//Create Platform 1
	Sprite * platform;
	platform = Sprite::create("UA/Background/platform1.png");
	platform->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform->setPosition(415, 20);
	platform->setScale(0.5f, 0.5f);
	Sprite * platformshadow;
	platformshadow = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow->setPosition(-925, -45);
	platformshadow->setScale(0.005f, 0.005f);
	///Add to character object
	Character * _platshad = new Character(platformshadow);
	Platform = new Character(platform, _platshad);
	this->addChild(Platform->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform->getShadow(0)->getSprite(), -53);//z = -50
	Platform->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform for shadow
	Sprite * platform2;
	platform2 = Sprite::create("UA/Background/platform2.png");
	platform2->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform2->setPosition(-3000, -20);
	platform2->setScale(0.000005f, 0.000005f);
	Sprite * platformshadow2;
	platformshadow2 = Sprite::create("UA/Background/platform2_shadow.png");
	platformshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow2->setPosition(2450, 45);
	platformshadow2->setScale(2.0f, 0.5f);
	///Add to character object
	Character * _platshad2 = new Character(platformshadow2);
	Platform2 = new Character(platform2, _platshad2);
	this->addChild(Platform2->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform2->getShadow(0)->getSprite(), -53);//z = -50
	Platform2->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create platfrom2 for player to jump
	Sprite * platform3;
	platform3 = Sprite::create("UA/Background/platform4.png");
	platform3->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform3->setPosition(1265, 20);
	platform3->setScale(0.5f, 0.5f);
	Sprite * platformshadow3;
	platformshadow3 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow3->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow3->setPosition(-1775, -45);
	platformshadow3->setScale(0.005f, 0.005f);
	///Add to character object
	Character * _platshad3 = new Character(platformshadow3);
	Platform3 = new Character(platform3, _platshad3);
	this->addChild(Platform3->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform3->getShadow(0)->getSprite(), -53);//z = -50
	Platform3->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform3->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform 3 for player to jump 
	Sprite * platform4;
	platform4 = Sprite::create("UA/Background/platform4.png");
	platform4->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform4->setPosition(2165, 20);
	platform4->setScale(0.5f, 0.5f);
	Sprite * platformshadow4;
	platformshadow4 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow4->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow4->setPosition(-2475, -45);
	platformshadow4->setScale(0.005f, 0.005f);
	///Add to character object
	Character * _platshad4 = new Character(platformshadow4);
	Platform4 = new Character(platform4, _platshad4);
	this->addChild(Platform4->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform4->getShadow(0)->getSprite(), -53);//z = -50
	Platform4->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform4->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform three for player to jump - last one
	Sprite * platform5;
	platform5 = Sprite::create("UA/Background/platform5.png");
	platform5->setAnchorPoint(Vec2(0.f, 0.5f));
	platform5->setPosition(2975, 20);
	platform5->setScale(0.5f, 0.5f);
	Sprite * platformshadow5;
	platformshadow5 = Sprite::create("UA/Background/platform3_shadow.png");
	platformshadow5->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow5->setPosition(-3175, -45);
	platformshadow5->setScale(0.005f, 0.005f);
	///Add to character object
	Character * _platshad5 = new Character(platformshadow5);
	Platform5 = new Character(platform5, _platshad5);
	this->addChild(Platform5->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform5->getShadow(0)->getSprite(), -53);//z = -50
	Platform5->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform5->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall for scaling
	Sprite * wall4;
	wall4 = Sprite::create("UA/Background/wall.png");
	wall4->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall4->setPosition(3165, 200);
	wall4->setScaleY(0.2);
	Sprite * wallshadow4;
	wallshadow4 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow4->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow4->setPosition(3140, 225);
	wallshadow4->setScaleY(0.2);
	///add to character object
	Character * _wallshad4 = new Character(wallshadow4);
	Wall4 = new Character(wall4, _wallshad4);
	this->addChild(Wall4->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall4->getShadow(0)->getSprite(), -53);// z = -50
	Wall4->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall4->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Left Boundary Wall
	Sprite* boundary1;
	boundary1 = Sprite::create("UA/Background/wall.png");
	boundary1->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundary1->setPosition(75, 290);
	boundary1->setScaleY(0.8);
	Sprite* boundaryshadow1;
	boundaryshadow1 = Sprite::create("UA/Background/wall_shadow.png");
	boundaryshadow1->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundaryshadow1->setPosition(50, 315);
	boundaryshadow1->setScaleY(0.8);
	///add to character object
	Character * _boundshad1 = new Character(boundaryshadow1);
	Boundary1 = new Character(boundary1, _boundshad1);
	this->addChild(Boundary1->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Boundary1->getShadow(0)->getSprite(), -53);// z = -50 (way behind player)
	Boundary1->getSprite()->getPhysicsBody()->setDynamic(false);
	Boundary1->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	Boundary1->getSprite()->setFlippedX(true);

	//Create Right Boundary Wall
	Sprite* boundary2;
	boundary2 = Sprite::create("UA/Background/wall.png");
	boundary2->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundary2->setPosition(3365, 290);
	boundary2->setScaleY(0.8);
	Sprite* boundaryshadow2;
	boundaryshadow2 = Sprite::create("UA/Background/wall_shadow.png");
	boundaryshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundaryshadow2->setPosition(3340, 315);
	boundaryshadow2->setScaleY(0.8);
	///add to character object
	Character * _boundshad2 = new Character(boundaryshadow2);
	Boundary2 = new Character(boundary2, _boundshad2);
	this->addChild(Boundary2->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Boundary2->getShadow(0)->getSprite(), -53);// z = -50 (way behind player)
	Boundary2->getSprite()->getPhysicsBody()->setDynamic(false);
	Boundary2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Ceiling
	Sprite * ceiling;
	ceiling = Sprite::create("UA/Background/ceiling.png");
	ceiling->setAnchorPoint(Vec2(0.5f, 0.5f));
	ceiling->setPosition(1415, 925);
	ceiling->setScale(3.0f, 0.5f);
	Sprite * ceilingshadow;
	ceilingshadow = Sprite::create("UA/Background/ceiling_shadow.png");
	ceilingshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	ceilingshadow->setPosition(1390, 950);
	ceilingshadow->setScale(3.0f, 0.5f);
	///Add to character object
	Character * _ceilingshad = new Character(ceilingshadow);
	Ceiling = new Character(ceiling, _ceilingshad);
	this->addChild(Ceiling->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Ceiling->getShadow(0)->getSprite(), -53);//z = -50
	Ceiling->getSprite()->getPhysicsBody()->setDynamic(false);
	Ceiling->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

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

	arrow = Sprite::create("UA/Background/arrow2.png");
	arrow->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrow->setPosition(3090, 150);
	arrow->setScale(0.2f, 0.2f);
	this->addChild(arrow, -50);
	arrow2 = Sprite::create("UA/Background/arrow2.png");
	arrow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	arrow2->setPosition(3090, 275);
	arrow2->setScale(0.2f, 0.2f);
	this->addChild(arrow2, -50);
}
//Init the static physics world pointer. Set it to be a nullptr which means it points to nothing
PhysicsWorld* DashLevel::physicsWorld = nullptr;
Scene* DashLevel::sceneHandle = nullptr;