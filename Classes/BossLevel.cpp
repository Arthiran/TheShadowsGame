#include "BossLevel.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"
#include "EndGame.h"

USING_NS_CC;
using namespace Input;

Scene* BossLevel::createScene()
{
	//Background Music
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/game_music.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/game_music.mp3", true);
	//Effects
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/jump.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/dash.mp3");
	// 'scene' is an autorelease object
	Scene* scene = Scene::createWithPhysics();
	BossLevel* layer = BossLevel::create();
	scene->addChild(layer);
	sceneHandle = scene;
	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	//Get the physics world from the scene so that we can work with it later
	physicsWorld = scene->getPhysicsWorld();
	return scene;
}

void BossLevel::onExit()
{
	Scene::onExit();
}

void BossLevel::onEnter()
{
	DISPLAY->createDebugConsole(true);
	std::cout << "THE CONSOLE IS NOW OPEN" << std::endl;//uncoment this to remove console window
	Scene::onEnter();
}

// on "init" you need to initialize your instance
bool BossLevel::init()
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
	boundry.setRect(0, 0, 3445, 1800);
	Player->getSprite()->setPosition(2175, 1240);
	//Player->getShadow(0)->health = 1;

	for (int i = 0; i < 2; i++) {
		Sprite * enemies;
		enemies = Sprite::create("UA/Enemies/placeholderV2.png");
		if (i == 0) enemies->setPosition(1225, 930);
		if (i == 1) enemies->setPosition(1750, 930);
		enemies->setRotation(0);
		enemies->setScale(0.9f);
		enemies->setAnchorPoint(Vec2(0.5f, 0.5f));
		Sprite* _shadowEnemies;
		_shadowEnemies = Sprite::create("UA/Enemies/placeholderV2_shadow.png");
		_shadowEnemies->setPosition(1215, 155);
		_shadowEnemies->setRotation(0);
		_shadowEnemies->setScale(0.9f);
		_shadowEnemies->setAnchorPoint(Vec2(0.5f, 0.5f));
		Character * shadowEnemies = new Character(_shadowEnemies);
		Character* en = new Character(enemies, shadowEnemies);
		en->getSprite()->getPhysicsBody()->setTag(enemyCollisionTag);
		en->getSprite()->getPhysicsBody()->setDynamic(true);
		Enemies.push_back(en);

		this->addChild(en->getSprite(), 1);
		this->addChild(en->getShadow(0)->getSprite(), -52);
		this->addChild(en->healthframe, 2);
		this->addChild(en->healthbar, 1);


		en->setAnimation(enemWalkP->clone(), enemWalkS->clone());
		en->runAnimation(true);
		en->runAnimation(false);

		en->getShadow(0)->getSprite()->setColor(Color3B(0, 0, 0));
	}

	//enemy tings
	for (int i = 0; i < 4; i++)
	{
		Sprite * enemies2;
		enemies2 = Sprite::create("UA/Enemies/placeholderV2.png");
		if (i == 0) enemies2->setPosition(1915, 954);
		if (i == 1) enemies2->setPosition(1620, 954);
		if (i == 2) enemies2->setPosition(1430, 954);
		if (i == 3) enemies2->setPosition(1150, 954);
		//enemies2->setPosition(558, 808);
		enemies2->setRotation(0);
		enemies2->setScale(0.9f);
		enemies2->setAnchorPoint(Vec2(0.5f, 0.5f));
		ShadowChar * en2 = new ShadowChar(enemies2);
		Enemies.push_back(en2);

		this->addChild(en2->getSprite(), -1);
		this->addChild(en2->healthframe, -2);
		this->addChild(en2->healthbar, -1);

		en2->setAnimation(enemWalkP->clone(), enemWalkS->clone());
		en2->runAnimation(false);

		en2->getShadow(0)->getSprite()->setColor(Color3B(0, 0, 0));
	}
	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();
	//this->getCameras().erase( this->getCameras().end());

	return true;
}

void BossLevel::FlipWorld()
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
	Platform6->flipWorld(wallCollisionTag);
	Platform7->flipWorld(wallCollisionTag);
	Platform8->flipWorld(wallCollisionTag);
	Platform9->flipWorld(wallCollisionTag);
	Wall->flipWorld(wallCollisionTag);
	Wall2->flipWorld(wallCollisionTag);
	Wall3->flipWorld(wallCollisionTag);
	Wall4->flipWorld(wallCollisionTag);
	Wall5->flipWorld(wallCollisionTag);
	Wall6->flipWorld(wallCollisionTag);
	Wall7->flipWorld(wallCollisionTag);
	Wall8->flipWorld(wallCollisionTag);
	Wall9->flipWorld(wallCollisionTag);
	Wall10->flipWorld(wallCollisionTag);
	Boundary1->flipWorld(wallCollisionTag);
	Boundary2->flipWorld(wallCollisionTag);
	Ceiling->flipWorld(wallCollisionTag);
	Button1->flipWorld(flag1Tag);
	Button2->flipWorld(flag2Tag);
	for (int i = 0; i < Enemies.size(); i++)
		Enemies.at(i)->flipWorld(enemyCollisionTag);
	
	if (Player->isShadow == false) {
	}
	else {
		Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x * 0.9, Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));
		
	}
}

void BossLevel::update(float deltaTime)//UPDATE LOOP
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
	//Raises the shadow wall a bit once all enemies are defeated
	if (Enemies.size() == 0)
	{
		Wall4->getShadow(0)->getSprite()->setPosition(1036, 1600);
	}

	//Load the end game screen
	if (black->isFlippedY() == true) {
		std::cout << "End Game" << std::endl;
		DISPLAY->init(1000.0f, 500.0f, "Shadow Game (Stalactites)", false);
		Scene* endGame = EndGame::createScene();
		director->getInstance()->replaceScene(endGame);
	}
	else if (Player->getSprite()->getPosition().x <= 1123 && Player->getSprite()->getPosition().y >= 1450)
	{

		if (black->isFlippedX() == false) {
			black->setPosition(Player->getPosition());
			black->setFlippedX(true);
			black->runAction(Sequence::createWithTwoActions(FadeIn::create(0.5f), FlipY::create(true)));
		}

	}

	//Health bar
	if (Player->health <= 0 || Player->getSprite()->getPosition().y < -1000)
	{
		//Reload the scene so they have to fight enemies again
		Scene* restart = BossLevel::createScene();
		director->replaceScene(restart);
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

void BossLevel::UpdatePositions(float dt)
{
	//not in use
}

bool BossLevel::checkEnd()
{
	//not in use
	return false;
}

void BossLevel::CheckCollision()
{
	
	//not in use
}

void BossLevel::initCollisionCallback()
{
	//Create the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	//Assign the callback function
	contactListener->onContactBegin = CC_CALLBACK_1(BossLevel::onContactBeginCallback, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(BossLevel::onSepBeginCallback, this);
	//Add the contact listener to the event dispatcher
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}


bool BossLevel::onContactBeginCallback(PhysicsContact& contact)
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
					Wall3->getShadow(0)->getSprite()->setPosition(Vec2(-1000, -1000));
					//shift->runAction(FadeOut::create(1.0f));
					Button1->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall6->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					//Wall6->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					//Button1->getShadow(0)->getSprite()->setPosition(3630, 120);
				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button1->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Platform8->getSprite()->setPosition(-100, -100);
					Platform8->getShadow(0)->getSprite()->setPosition(-100, -100);
				}
				return true;
			}

			if (tagB == flag2Tag)
			{
				//reset jump and dash
				candash = true;
				dash = 0;
				falling = false;
				grounded = true;
				//shift->setVisible(false);
				//remove bounce
				if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button2->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Wall3->getSprite()->runAction(MoveBy::create(1.0, Vec2(0, +250)));
					//Wall3->getSprite()->setPosition(Vec2(-1000, -1000));
					//Wall3->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					//Platform6->getSprite()->setPosition(Vec2(2360, 425));
					//Platform6->getShadow(0)->getSprite()->setPosition(Vec2(2335, 450));
					//Platform7->getSprite()->setPosition(Vec2(3020, 425));
					//Platform7->getShadow(0)->getSprite()->setPosition(Vec2(2995, 450));
					//Platform8->getSprite()->setPosition(Vec2(1700, 425));
					//Platform8->getShadow(0)->getSprite()->setPosition(Vec2(1675, 450));
					//dashText->setPosition(1800, 650);
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
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Wall3->getShadow(0)->getSprite()->setPosition(Vec2(-1000, -1000));
					//shift->runAction(FadeOut::create(1.0f));
					Button1->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall6->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					//Wall6->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					//Button1->getShadow(0)->getSprite()->setPosition(3630, 120);
				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button1->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Platform8->getSprite()->setPosition(-100, -100);
					Platform8->getShadow(0)->getSprite()->setPosition(-100, -100);
				}
				return true;
			} 
			if (tagA == flag2Tag)
			{
				//reset jump and dash
				candash = true;
				dash = 0;
				falling = false;
				grounded = true;
				//shift->setVisible(false);
				//remove bounce
				if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button2->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Wall3->getSprite()->runAction(MoveBy::create(1.0, Vec2(0, +250)));
					//Wall3->getSprite()->setPosition(Vec2(-1000, -1000));
					//Wall3->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					//Platform6->getSprite()->setPosition(Vec2(2360, 425));
					//Platform6->getShadow(0)->getSprite()->setPosition(Vec2(2335, 450));
					//Platform7->getSprite()->setPosition(Vec2(3020, 425));
					//Platform7->getShadow(0)->getSprite()->setPosition(Vec2(2995, 450));
					//Platform8->getSprite()->setPosition(Vec2(1700, 425));
					//Platform8->getShadow(0)->getSprite()->setPosition(Vec2(1675, 450));
					//dashText->setPosition(1800, 650);
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

void BossLevel::DrawWorld()
{
	///ALL SHADOWS ARE OFFSET BY Vec2(-25,25)

	//Creating the background
	background = Sprite::create("UA/Background/Warehouse2.png");
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(965, 675);
	background->setPositionZ(-250);
	background->setScale(0.9f, 0.9f);
	this->addChild(background, -100);

	//Create Platform 1
	Sprite * platform;
	platform = Sprite::create("UA/Background/platform1.png");
	platform->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform->setPosition(1415, 820);
	platform->setScale(0.9f, 0.5f);

	Sprite * platformshadow;
	platformshadow = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow->setPosition(1390, 845);
	platformshadow->setScale(0.9f, 0.5f);
	///Add to character object
	Character * _platshad = new Character(platformshadow);
	Platform = new Character(platform, _platshad);
	this->addChild(Platform->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform->getShadow(0)->getSprite(), -53);//z = -50
	Platform->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform
	Sprite * platform2;
	platform2 = Sprite::create("UA/Background/platform1.png");
	platform2->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform2->setPosition(2177, 1175);
	platform2->setScale(0.25f, 0.20f);
	Sprite * platformshadow2;
	platformshadow2 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow2->setPosition(2154, 1200);
	platformshadow2->setScale(0.25f, 0.20f);
	///Add to character object
	Character * _platshad2 = new Character(platformshadow2);
	Platform2 = new Character(platform2, _platshad2);
	this->addChild(Platform2->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform2->getShadow(0)->getSprite(), -53);//z = -50
	Platform2->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform 
	Sprite * platform3;
	platform3 = Sprite::create("UA/Background/platform1.png");
	platform3->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform3->setPosition(1600, 1422);
	platform3->setScale(0.8f, 0.25f);
	Sprite * platformshadow3;
	platformshadow3 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow3->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow3->setPosition(1575, 1447);
	platformshadow3->setScale(0.8f, 0.25f);
	///Add to character object
	Character * _platshad3 = new Character(platformshadow3);
	Platform3 = new Character(platform3, _platshad3);
	this->addChild(Platform3->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform3->getShadow(0)->getSprite(), -53);//z = -50
	Platform3->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform3->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//first shadow only platform
	Sprite * platform4;
	platform4 = Sprite::create("UA/Background/platform1.png");
	platform4->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform4->setPosition(-3025, 9375);
	platform4->setScaleY(0.00001f);
	Sprite * platformshadow4;
	platformshadow4 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow4->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow4->setPosition(500, 1100);
	platformshadow4->setScale(0.4f, 0.25f);
	///Add to character object
	Character * _platshad4 = new Character(platformshadow4);
	Platform4 = new Character(platform4, _platshad4);
	this->addChild(Platform4->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform4->getShadow(0)->getSprite(), -53);//z = -50
	Platform4->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform4->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);
	
	//Pllayer walks onto this shadow plat first
	Sprite * platform5;
	platform5 = Sprite::create("UA/Background/platform1.png");
	platform5->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform5->setPosition(3025, -2220);
	platform5->setScaleY(0.000001f);
	Sprite * platformshadow5;
	platformshadow5 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow5->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow5->setPosition(600, 825);
	platformshadow5->setScale(0.25f, 0.25f);
	///Add to character object
	Character * _platshad5 = new Character(platformshadow5);
	Platform5 = new Character(platform5, _platshad5);
	this->addChild(Platform5->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform5->getShadow(0)->getSprite(), -53);//z = -50
	Platform5->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform5->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	
	Sprite * platform6;
	platform6 = Sprite::create("UA/Background/platform1.png");
	platform6->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform6->setPosition(-2300, 425);
	platform6->setScale(0.1f, 0.1f);
	//First bottom platform shadow
	Sprite * platformshadow6;
	platformshadow6 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow6->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow6->setPosition(525, 416);
	platformshadow6->setScale(0.5f, 0.25f);
	///Add to character object
	Character * _platshad6 = new Character(platformshadow6);
	Platform6 = new Character(platform6, _platshad6);
	this->addChild(Platform6->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform6->getShadow(0)->getSprite(), -53);//z = -50
	Platform6->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform6->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Last shadow platform with button on top of it!
	Sprite * platform7;
	platform7 = Sprite::create("UA/Background/platform1.png");
	platform7->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform7->setPosition(-3020, 425);
	platform7->setScale(0.1f, 0.1f);

	Sprite * platformshadow7;
	platformshadow7 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow7->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow7->setPosition(1840, 405);
	platformshadow7->setScale(0.25f, 0.2f);
	///Add to character object
	Character * _platshad7 = new Character(platformshadow7);
	Platform7 = new Character(platform7, _platshad7);
	this->addChild(Platform7->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform7->getShadow(0)->getSprite(), -53);//z = -50
	Platform7->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform7->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//PLATFORM THAT BLOCKS PLAYER BUT DISAPEARS WITH BUTTON PRESS
	Sprite * platform8;
	platform8 = Sprite::create("UA/Background/platform1.png");
	platform8->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform8->setPosition(2234, 1423);
	platform8->setScale(0.11f, 0.2f);
	Sprite * platformshadow8;
	platformshadow8 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow8->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow8->setPosition(2209, 1448);
	platformshadow8->setScale(0.11f, 0.1f);
	///Add to character object
	Character * _platshad8 = new Character(platformshadow8);
	Platform8 = new Character(platform8, _platshad8);
	this->addChild(Platform8->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform8->getShadow(0)->getSprite(), -53);//z = -50
	Platform8->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform8->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform for jump before exit
	Sprite * platform9;
	platform9 = Sprite::create("UA/Background/platform1.png");
	platform9->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform9->setPosition(-2170, 60);
	platform9->setScale(0.1f, 0.1f);
	Sprite * platformshadow9;
	platformshadow9 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow9->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow9->setPosition(-2145, 85);
	platformshadow9->setScale(0.1f, 0.1f);
	///Add to character object
	Character * _platshad9 = new Character(platformshadow9);
	Platform9 = new Character(platform9, _platshad9);
	this->addChild(Platform9->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform9->getShadow(0)->getSprite(), -53);//z = -50
	Platform9->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform9->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall
	//First vertical wall
	Sprite * wall;
	wall = Sprite::create("UA/Background/wall.png");
	wall->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall->setPosition(2025, 1015);
	wall->setScale(1.0f, 0.2f);
	Sprite * wallshadow;
	wallshadow = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow->setPosition(2000, 1040);
	wallshadow->setScale(1.0f, 0.2f);
	///add to character object
	Character * _wallshad = new Character(wallshadow);
	Wall = new Character(wall, _wallshad);
	this->addChild(Wall->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall->getShadow(0)->getSprite(), -53);// z = -50
	Wall->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall
	//First floating wall for wall jump
	Sprite* wall2;
	wall2 = Sprite::create("UA/Background/wall.png");
	wall2->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall2->setPosition(1797, 1215);
	wall2->setScale(1.0f, 0.25f);
	Sprite* wallshadow2;
	wallshadow2 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow2->setPosition(1772, 1240);
	wallshadow2->setScale(1.0f, 0.25f);
	///add to character object
	Character * _wallshad2 = new Character(wallshadow2);
	Wall2 = new Character(wall2, _wallshad2);
	this->addChild(Wall2->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall2->getShadow(0)->getSprite(), -53);// z = -50 (way behind player)
	Wall2->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall with no shadow
	Sprite* wall3;
	wall3 = Sprite::create("UA/Background/wall.png");
	wall3->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall3->setPosition(2330, 1450);
	wall3->setScale(1.0f, 0.4f);
	Sprite* wallshadow3;
	wallshadow3 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow3->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow3->setPosition(2305, 1475);
	wallshadow3->setScale(1.0f, 0.4f);
	///add to character object
	Character * _wallshad3 = new Character(wallshadow3);
	Wall3 = new Character(wall3, _wallshad3);
	this->addChild(Wall3->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall3->getShadow(0)->getSprite(), -53);// z = -50 (way behind player)
	Wall3->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall3->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Wall that moves after enemies are dead (only shdaow part moves)
	Sprite * wall4;
	wall4 = Sprite::create("UA/Background/wall.png");
	wall4->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall4->setPosition(1061, 1425);
	wall4->setScaleY(0.8f);
	Sprite * wallshadow4;
	wallshadow4 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow4->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow4->setPosition(1036, 1450);
	wallshadow4->setScaleY(0.8f);
	
	Character * _wallshad4 = new Character(wallshadow4);
	Wall4 = new Character(wall4, _wallshad4);
	this->addChild(Wall4->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall4->getShadow(0)->getSprite(), -53);// z = -50
	Wall4->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall4->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);
	//First vertical shadow wall
	Sprite * wall5;
	wall5 = Sprite::create("UA/Background/wall.png");
	wall5->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall5->setPosition(9061, -1560);
	wall5->setScaleY(0.00001f);
	Sprite * wallshadow5;
	wallshadow5 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow5->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow5->setPosition(200, 780);
	wallshadow5->setScale(1.0f, 0.5f);

	Character * _wallshad5 = new Character(wallshadow5);
	Wall5 = new Character(wall5, _wallshad5);
	this->addChild(Wall5->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall5->getShadow(0)->getSprite(), -53);// z = -50
	Wall5->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall5->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	Sprite * wall6;
	wall6 = Sprite::create("UA/Background/wall.png");
	wall6->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall6->setPosition(9069, -1560);
	wall6->setScaleY(0.00001f);
	Sprite * wallshadow6;
	wallshadow6 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow6->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow6->setPosition(450, 700);
	wallshadow6->setScale(1.0f, 0.2f);

	Character * _wallshad6 = new Character(wallshadow6);
	Wall6 = new Character(wall6, _wallshad6);
	this->addChild(Wall6->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall6->getShadow(0)->getSprite(), -53);// z = -50
	Wall6->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall6->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Far right shadow wall.
	Sprite * wall7;
	wall7 = Sprite::create("UA/Background/wall.png");
	wall7->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall7->setPosition(9069, -1560);
	wall7->setScaleY(0.00001f);
	Sprite * wallshadow7;
	wallshadow7 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow7->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow7->setPosition(1994, 591);
	wallshadow7->setScale(1.0f, 0.3f);

	Character * _wallshad7 = new Character(wallshadow7);
	Wall7 = new Character(wall7, _wallshad7);
	this->addChild(Wall7->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall7->getShadow(0)->getSprite(), -53);// z = -50
	Wall7->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall7->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	Sprite * wall8;
	wall8 = Sprite::create("UA/Background/wall.png");
	wall8->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall8->setPosition(9069, -1560);
	wall8->setScaleY(0.00001f);
	Sprite * wallshadow8;
	wallshadow8 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow8->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow8->setPosition(1291, 400);
	wallshadow8->setScale(1.0f, 0.2f);

	Character * _wallshad8 = new Character(wallshadow8);
	Wall8 = new Character(wall8, _wallshad8);
	this->addChild(Wall8->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall8->getShadow(0)->getSprite(), -53);// z = -50
	Wall8->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall8->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	Sprite * wall9;
	wall9 = Sprite::create("UA/Background/wall.png");
	wall9->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall9->setPosition(9069, -1560);
	wall9->setScaleY(0.00001f);
	Sprite * wallshadow9;
	wallshadow9 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow9->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow9->setPosition(756, 1475);
	wallshadow9->setScaleY(0.5f);

	Character * _wallshad9 = new Character(wallshadow9);
	Wall9 = new Character(wall9, _wallshad9);
	this->addChild(Wall9->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall9->getShadow(0)->getSprite(), -53);// z = -50
	Wall9->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall9->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create wall to make door more legit looking at end of level
	Sprite * wall10;
	wall10 = Sprite::create("UA/Background/ceiling.png");
	wall10->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall10->setPosition(437, 1600);
	wall10->setScale(0.1f, 1.0f);
	Sprite * wallshadow10;
	wallshadow10 = Sprite::create("UA/Background/ceiling_shadow.png");
	wallshadow10->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow10->setPosition(412, 1625);
	wallshadow10->setScale(0.1f, 1.0f);

	Character * _wallshad10 = new Character(wallshadow10);
	Wall10 = new Character(wall10, _wallshad10);
	this->addChild(Wall10->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall10->getShadow(0)->getSprite(), -53);// z = -50
	Wall10->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall10->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

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
	ceiling->setPosition(1415, 1800);
	ceiling->setScale(3.0f, 0.5f);
	Sprite * ceilingshadow;
	ceilingshadow = Sprite::create("UA/Background/ceiling_shadow.png");
	ceilingshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	ceilingshadow->setPosition(1390, 1825);
	ceilingshadow->setScale(3.0f, 0.5f);
	///Add to character object
	Character * _ceilingshad = new Character(ceilingshadow);
	Ceiling = new Character(ceiling, _ceilingshad);
	this->addChild(Ceiling->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Ceiling->getShadow(0)->getSprite(), -53);//z = -50
	Ceiling->getSprite()->getPhysicsBody()->setDynamic(false);
	Ceiling->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Button
	Sprite* button;
	button = Sprite::create("UA/Level/ButtonTop.png");
	button->setAnchorPoint(Vec2(0.5f, 0.5f));
	button->setPosition(-800, -675);

	Sprite* buttonShadow;
	buttonShadow = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadow->setPosition(1840, 448);
	///add to character object
	Character * _buttonShad = new Character(buttonShadow);
	Button1 = new Character(button, _buttonShad);
	this->addChild(Button1->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Button1->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	Button1->getSprite()->getPhysicsBody()->setDynamic(false);
	Button1->getSprite()->getPhysicsBody()->setTag(flag1Tag);

	//Create button aesthetics
	buttonBotShad1 = Sprite::create("UA/Level/ButtonBottomShadow.png");
	buttonBotShad1->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBotShad1->setPosition(1840, 448);
	this->addChild(buttonBotShad1, -53);

	//Create Button
	Sprite* button2;
	button2 = Sprite::create("UA/Level/ButtonTop.png");
	button2->setAnchorPoint(Vec2(0.5f, 0.5f));
	button2->setPosition(-800, -675);
	Sprite* buttonShadow2;
	buttonShadow2 = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadow2->setPosition(3095, 5480);
	///add to character object
	Character * _buttonShad2 = new Character(buttonShadow2);
	Button2 = new Character(button2, _buttonShad2);
	this->addChild(Button2->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Button2->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	Button2->getSprite()->getPhysicsBody()->setDynamic(false);
	Button2->getSprite()->getPhysicsBody()->setTag(flag2Tag);

	door = Sprite::create("UA/Level/door2.png");
	door->setAnchorPoint(Vec2(0.5f, 0.5f));
	door->setPosition(1103, 1542);
	door->setScale(0.5f, 0.5f);
	this->addChild(door, -50);
	door->setFlippedX(true);
}
//Init the static physics world pointer. Set it to be a nullptr which means it points to nothing
PhysicsWorld* BossLevel::physicsWorld = nullptr;
Scene* BossLevel::sceneHandle = nullptr;