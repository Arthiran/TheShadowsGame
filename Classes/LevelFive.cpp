#include "LevelFive.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"
#include "BossTransition.h"

USING_NS_CC;
using namespace Input;

Scene* LevelFive::createScene()
{
	//Background Music
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/game_music.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/game_music.mp3", true);
	//Effects
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/jump.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/dash.mp3");
	// 'scene' is an autorelease object
	Scene* scene = Scene::createWithPhysics();
	LevelFive* layer = LevelFive::create();
	scene->addChild(layer);
	sceneHandle = scene;
	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	//Get the physics world from the scene so that we can work with it later
	physicsWorld = scene->getPhysicsWorld();
	return scene;
}

void LevelFive::onExit()
{
	Scene::onExit();
}

void LevelFive::onEnter()
{
	DISPLAY->createDebugConsole(true);
	std::cout << "THE CONSOLE IS NOW OPEN" << std::endl;//uncoment this to remove console window
	Scene::onEnter();
}

// on "init" you need to initialize your instance
bool LevelFive::init()
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
	boundry.setRect(0, 0, 5155, 1800);

	//enemy tings
	for (int i = 0; i < 5; i++) {//increase 3 to 5
		Sprite * enemies;
		enemies = Sprite::create("UA/Enemies/placeholderV2.png");
		if (i == 0) enemies->setPosition(1240, 130);
		if (i == 1) enemies->setPosition(260, 790);
		if (i == 2) enemies->setPosition(1530, 530);
		if (i == 3) enemies->setPosition(3840, 128);//todo
		if (i == 4) enemies->setPosition(4565, 128);//todo
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

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();
	//this->getCameras().erase( this->getCameras().end());

	return true;
}

void LevelFive::FlipWorld()
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
	Platform10->flipWorld(wallCollisionTag);
	Platform11->flipWorld(wallCollisionTag);
	Platform12->flipWorld(wallCollisionTag);
	Platform13->flipWorld(wallCollisionTag);
	Platform14->flipWorld(wallCollisionTag);
	Platform15->flipWorld(wallCollisionTag);
	Platform16->flipWorld(wallCollisionTag);
	Platform17->flipWorld(wallCollisionTag);
	Platform18->flipWorld(wallCollisionTag);
	Platform19->flipWorld(wallCollisionTag);

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
	Wall11->flipWorld(wallCollisionTag);
	Wall12->flipWorld(wallCollisionTag);
	Wall13->flipWorld(wallCollisionTag);

	Boundary1->flipWorld(wallCollisionTag);
	Boundary2->flipWorld(wallCollisionTag);
	Ceiling->flipWorld(wallCollisionTag);

	Button1->flipWorld(flag1Tag);
	Button2->flipWorld(flag2Tag);
	Button3->flipWorld(flag3Tag);

	for (int i = 0; i < Enemies.size(); i++)
		Enemies.at(i)->flipWorld(enemyCollisionTag);

	if (Player->isShadow == false) {
	}
	else {
		Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x * 0.9, Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));
		
	}
}

void LevelFive::update(float deltaTime)//UPDATE LOOP
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

	//Load the next level
	if (black->isFlippedY() == true) {
		std::cout << "level4t" << std::endl;
		this->stopAllActions();
		this->removeAllComponents();
		cocos2d::CCDirector::sharedDirector()->purgeCachedData();
		SpriteFrameCache::getInstance()->removeSpriteFrames();
		SpriteFrameCache::destroyInstance();
		this->cleanup();
		DISPLAY->init(1000.0f, 500.0f, "Shadow Game (Stalactites)", false);
		Scene* bossLevel = BossTransition::createScene();
		director->getInstance()->replaceScene(bossLevel);
	}
	else if (Player->getSprite()->getPosition().x >= 5020 && Player->getSprite()->getPosition().y >= 1300)
	{

		if (black->isFlippedX() == false) {
			black->setPosition(Player->getPosition());
			black->setFlippedX(true);
			black->runAction(Sequence::createWithTwoActions(FadeIn::create(0.5f), FlipY::create(true)));
		}

	}

	//Health bar
	if (Player->health <= 0 || Player->getSprite()->getPosition().y < -20)
	{
		Player->getSprite()->stopAllActions();
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

void LevelFive::UpdatePositions(float dt)
{
	//not in use
}

bool LevelFive::checkEnd()
{
	//not in use
	return false;
}

void LevelFive::CheckCollision()
{

	//not in use
}

void LevelFive::initCollisionCallback()
{
	//Create the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	//Assign the callback function
	contactListener->onContactBegin = CC_CALLBACK_1(LevelFive::onContactBeginCallback, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(LevelFive::onSepBeginCallback, this);
	//Add the contact listener to the event dispatcher
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}


bool LevelFive::onContactBeginCallback(PhysicsContact& contact)
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
				if (Player->isShadow == false)
				{
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button1->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Position platforms to get to falling platform
					Platform5->getShadow(0)->getSprite()->setPosition(980, 1405);
					Platform6->getShadow(0)->getSprite()->setPosition(1630, 1405);
				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					//Button1->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Button1->getShadow(0)->getSprite()->runAction(MoveTo::create(0.4, Vec2(2606, 390)));
					//Cause the platform to fall
					Platform7->getSprite()->runAction(MoveTo::create(0.4, Vec2(2606, 300)));
					Platform7->getShadow(0)->getSprite()->runAction(MoveTo::create(0.4, Vec2(2581, 325)));
					Wall7->getSprite()->runAction(MoveTo::create(0.4, Vec2(3070, -350)));
					Wall7->getShadow(0)->getSprite()->runAction(MoveTo::create(0.4, Vec2(3045, -375)));
					buttonBotShad1->runAction(MoveTo::create(0.4, Vec2(2606, 415)));
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
				if (Player->isShadow == false)
				{
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button2->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Wall11->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -50)));
				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button2->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Remove blocking platform
					Platform10->getSprite()->setPosition(-1000, -100);
					Platform10->getShadow(0)->getSprite()->setPosition(-1000, -100);

				}
				return true;
			}

			if (tagB == flag3Tag)
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
					Button3->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Remove blocking platform
					Wall13->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					Wall13->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));

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
				if (Player->isShadow == false)
				{
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button1->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Position platforms to get to falling platform
					Platform5->getShadow(0)->getSprite()->setPosition(980, 1405);
					Platform6->getShadow(0)->getSprite()->setPosition(1630, 1405);
				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					//Button1->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Button1->getShadow(0)->getSprite()->runAction(MoveTo::create(0.4, Vec2(2606, 390)));
					//Cause the platform to fall
					Platform7->getSprite()->runAction(MoveTo::create(0.4, Vec2(2606, 300)));
					Platform7->getShadow(0)->getSprite()->runAction(MoveTo::create(0.4, Vec2(2581, 325)));
					Wall7->getSprite()->runAction(MoveTo::create(0.4, Vec2(3070, -350)));
					Wall7->getShadow(0)->getSprite()->runAction(MoveTo::create(0.4, Vec2(3045, -375)));
					buttonBotShad1->runAction(MoveTo::create(0.4, Vec2(2606, 415)));
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
				if (Player->isShadow == false)
				{
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button2->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Wall11->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -50)));
				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					Button2->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Remove blocking platform
					Platform10->getSprite()->setPosition(-1000, -100);
					Platform10->getShadow(0)->getSprite()->setPosition(-1000, -100);

				}
				return true;
			}

			if (tagA == flag3Tag)
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
					Button3->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Remove blocking platform
					Wall13->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));
					Wall13->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +50)));

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

void LevelFive::DrawWorld()
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
	platform->setPosition(900, 20);
	platform->setScale(1.2f, 0.5f);
	Sprite * platformshadow;
	platformshadow = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow->setPosition(875, 45);
	platformshadow->setScale(1.2f, 0.5f);
	///Add to character object
	Character * _platshad = new Character(platformshadow);
	Platform = new Character(platform, _platshad);
	this->addChild(Platform->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform->getShadow(0)->getSprite(), -53);//z = -50
	Platform->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create platform for T
	Sprite * platform2;
	platform2 = Sprite::create("UA/Background/platform1.png");
	platform2->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform2->setPosition(1715, 475);
	platform2->setScale(0.3f, 0.4f);
	Sprite * platformshadow2;
	platformshadow2 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow2->setPosition(1690, 500);
	platformshadow2->setScale(0.3f, 0.4f);
	///Add to character object
	Character * _platshad2 = new Character(platformshadow2);
	Platform2 = new Character(platform2, _platshad2);
	this->addChild(Platform2->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform2->getShadow(0)->getSprite(), -53);//z = -50
	Platform2->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform for first upper area
	Sprite * platform3;
	platform3 = Sprite::create("UA/Background/platform1.png");
	platform3->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform3->setPosition(650, 685);
	platform3->setScale(0.8f, 0.5f);
	Sprite * platformshadow3;
	platformshadow3 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow3->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow3->setPosition(625, 710);
	platformshadow3->setScale(0.8f, 0.5f);
	///Add to character object
	Character * _platshad3 = new Character(platformshadow3);
	Platform3 = new Character(platform3, _platshad3);
	this->addChild(Platform3->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform3->getShadow(0)->getSprite(), -53);//z = -50
	Platform3->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform3->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create platform above barrier
	Sprite * platform4;
	platform4 = Sprite::create("UA/Background/platform1.png");
	platform4->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform4->setPosition(550, 1300);
	platform4->setScale(0.2, 0.3);
	Sprite * platformshadow4;
	platformshadow4 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow4->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow4->setPosition(525, 1325);
	platformshadow4->setScale(0.2, 0.3);
	///Add to character object
	Character * _platshad4 = new Character(platformshadow4);
	Platform4 = new Character(platform4, _platshad4);
	this->addChild(Platform4->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform4->getShadow(0)->getSprite(), -53);//z = -50
	Platform4->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform4->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create small platforms to falling platform
	Sprite * platform5;
	platform5 = Sprite::create("UA/Background/platform1.png");
	platform5->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform5->setPosition(-980, -1405);
	platform5->setScale(0.00001f, 0.00001f);
	Sprite * platformshadow5;
	platformshadow5 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow5->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow5->setPosition(980, -1405);
	platformshadow5->setScale(0.1f, 0.1f);
	///Add to character object
	Character * _platshad5 = new Character(platformshadow5);
	Platform5 = new Character(platform5, _platshad5);
	this->addChild(Platform5->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform5->getShadow(0)->getSprite(), -53);//z = -50
	Platform5->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform5->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create small platforms to falling platform
	Sprite * platform6;
	platform6 = Sprite::create("UA/Background/platform1.png");
	platform6->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform6->setPosition(-1630, -1405);
	platform6->setScale(0.00001f, 0.00001f);
	Sprite * platformshadow6;
	platformshadow6 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow6->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow6->setPosition(1630, -1405);
	platformshadow6->setScale(0.1f, 0.1f);
	///Add to character object
	Character * _platshad6 = new Character(platformshadow6);
	Platform6 = new Character(platform6, _platshad6);
	this->addChild(Platform6->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform6->getShadow(0)->getSprite(), -53);//z = -50
	Platform6->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform6->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Platform6->getSprite()->runAction(Repeat::create(Sequence::createWithTwoActions(MoveBy::create(2.5f, Vec2(50, 0)), MoveBy::create(2.5f, Vec2(-50, 0))), 9999));
	//Platform6->getShadow(0)->getSprite()->runAction(Repeat::create(Sequence::createWithTwoActions(MoveBy::create(2.5f, Vec2(-50, 0)), MoveBy::create(2.5f, Vec2(50, 0))), 9999));

	//Create large platform that falls
	Sprite * platform7;
	platform7 = Sprite::create("UA/Background/platform1.png");
	platform7->setAnchorPoint(Vec2(0.5f, 0.5f));
	//platform7->setPosition(2606, 300);
	platform7->setPosition(2606, 1375);
	platform7->setScale(0.7f, 0.5f);
	Sprite * platformshadow7;
	platformshadow7 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow7->setAnchorPoint(Vec2(0.5f, 0.5f));
	//platformshadow7->setPosition(2581, 325);
	platformshadow7->setPosition(2681, 1400);
	platformshadow7->setScale(0.7f, 0.5f);
	///Add to character object
	Character * _platshad7 = new Character(platformshadow7);
	Platform7 = new Character(platform7, _platshad7);
	this->addChild(Platform7->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform7->getShadow(0)->getSprite(), -53);//z = -50
	Platform7->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform7->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform after falling platform gap
	Sprite * platform8;
	platform8 = Sprite::create("UA/Background/platform1.png");
	platform8->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform8->setPosition(3495, 425);
	platform8->setScale(0.3f, 0.3f);
	Sprite * platformshadow8;
	platformshadow8 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow8->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow8->setPosition(3470, 450);
	platformshadow8->setScale(0.3f, 0.3f);
	///Add to character object
	Character * _platshad8 = new Character(platformshadow8);
	Platform8 = new Character(platform8, _platshad8);
	this->addChild(Platform8->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform8->getShadow(0)->getSprite(), -53);//z = -50
	Platform8->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform8->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create plaform for small shadow area by falling platform
	Sprite * platform9;
	platform9 = Sprite::create("UA/Background/platform1.png");
	platform9->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform9->setPosition(-1350, 625);
	platform9->setScale(0.001f, 0.001f);
	Sprite * platformshadow9;
	platformshadow9 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow9->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow9->setPosition(3650, 1300);
	platformshadow9->setScale(0.4f, 0.5f);
	///Add to character object
	Character * _platshad9 = new Character(platformshadow9);
	Platform9 = new Character(platform9, _platshad9);
	this->addChild(Platform9->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform9->getShadow(0)->getSprite(), -53);//z = -50
	Platform9->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform9->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform that blocks the shadow button on the falling platform
	Sprite * platform10;
	platform10 = Sprite::create("UA/Background/glass.png");
	platform10->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform10->setPosition(2631, 1479);
	platform10->setScale(0.2f, 0.2f);
	Sprite * platformshadow10;
	platformshadow10 = Sprite::create("UA/Background/glass_shadow.png");
	platformshadow10->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow10->setPosition(2606, 1504);
	platformshadow10->setScale(0.2f, 0.2f);
	///Add to character object
	Character * _platshad10 = new Character(platformshadow10);
	Platform10 = new Character(platform10, _platshad10);
	this->addChild(Platform10->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform10->getShadow(0)->getSprite(), -53);//z = -50
	Platform10->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform10->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Platform that is the start of the next area after falling paltform
	Sprite * platform11;
	platform11 = Sprite::create("UA/Background/platform1.png");
	platform11->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform11->setPosition(3870, 739);
	platform11->setScale(0.3f, 0.5f);
	Sprite * platformshadow11;
	platformshadow11 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow11->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow11->setPosition(3845, 764);
	platformshadow11->setScale(0.3f, 0.5f);
	///Add to character object
	Character * _platshad11 = new Character(platformshadow11);
	Platform11 = new Character(platform11, _platshad11);
	this->addChild(Platform11->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform11->getShadow(0)->getSprite(), -53);//z = -50
	Platform11->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform11->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform in the second area for the bottom where the enemies are
	Sprite * platform12;
	platform12 = Sprite::create("UA/Background/platform1.png");
	platform12->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform12->setPosition(4395, 20);
	platform12->setScale(1.0f, 0.5f);
	Sprite * platformshadow12;
	platformshadow12 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow12->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow12->setPosition(4370, 45);
	platformshadow12->setScale(1.0f, 0.5f);
	///Add to character object
	Character * _platshad12 = new Character(platformshadow12);
	Platform12 = new Character(platform12, _platshad12);
	this->addChild(Platform12->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform12->getShadow(0)->getSprite(), -53);//z = -50
	Platform12->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform12->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create shadow platform for button to open exit
	Sprite * platform13;
	platform13 = Sprite::create("UA/Background/platform1.png");
	platform13->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform13->setPosition(-4395, -450);
	platform13->setScale(0.0001f, 0.0001f);
	Sprite * platformshadow13;
	platformshadow13 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow13->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow13->setPosition(3900, 375);
	platformshadow13->setScale(0.3f, 0.3f);
	///Add to character object
	Character * _platshad13 = new Character(platformshadow13);
	Platform13 = new Character(platform13, _platshad13);
	this->addChild(Platform13->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform13->getShadow(0)->getSprite(), -53);//z = -50
	Platform13->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform13->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create platform for where the exit is
	Sprite * platform14;
	platform14 = Sprite::create("UA/Background/platform1.png");
	platform14->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform14->setPosition(4865, 1265);
	platform14->setScale(0.3f, 0.2f);
	Sprite * platformshadow14;
	platformshadow14 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow14->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow14->setPosition(4840, 1293);
	platformshadow14->setScale(0.3f, 0.2f);
	///Add to character object
	Character * _platshad14 = new Character(platformshadow14);
	Platform14 = new Character(platform14, _platshad14);
	this->addChild(Platform14->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform14->getShadow(0)->getSprite(), -53);//z = -50
	Platform14->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform14->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create small platforms to exit
	Sprite * platform15;
	platform15 = Sprite::create("UA/Background/platform1.png");
	platform15->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform15->setPosition(4500, 800);
	platform15->setScale(0.1f, 0.1f);
	Sprite * platformshadow15;
	platformshadow15 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow15->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow15->setPosition(4475, 825);
	platformshadow15->setScale(0.1f, 0.1f);
	///Add to character object
	Character * _platshad15 = new Character(platformshadow15);
	Platform15 = new Character(platform15, _platshad15);
	this->addChild(Platform15->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform15->getShadow(0)->getSprite(), -53);//z = -50
	Platform15->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform15->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create small platforms to exit
	Sprite * platform16;
	platform16 = Sprite::create("UA/Background/platform1.png");
	platform16->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform16->setPosition(4500, 450);
	platform16->setScale(0.1f, 0.1f);
	Sprite * platformshadow16;
	platformshadow16 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow16->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow16->setPosition(4475, 475);
	platformshadow16->setScale(0.1f, 0.1f);
	///Add to character object
	Character * _platshad16 = new Character(platformshadow16);
	Platform16 = new Character(platform16, _platshad16);
	this->addChild(Platform16->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform16->getShadow(0)->getSprite(), -53);//z = -50
	Platform16->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform16->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create small platforms to exit
	Sprite * platform17;
	platform17 = Sprite::create("UA/Background/platform1.png");
	platform17->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform17->setPosition(4700, 950);
	platform17->setScale(0.1f, 0.1f);
	Sprite * platformshadow17;
	platformshadow17 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow17->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow17->setPosition(4675, 975);
	platformshadow17->setScale(0.1f, 0.1f);
	///Add to character object
	Character * _platshad17 = new Character(platformshadow17);
	Platform17 = new Character(platform17, _platshad17);
	this->addChild(Platform17->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform17->getShadow(0)->getSprite(), -53);//z = -50
	Platform17->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform17->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create small platforms to exit
	Sprite * platform18;
	platform18 = Sprite::create("UA/Background/platform1.png");
	platform18->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform18->setPosition(4500, 1100);
	platform18->setScale(0.1f, 0.1f);
	Sprite * platformshadow18;
	platformshadow18 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow18->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow18->setPosition(4475, 1125);
	platformshadow18->setScale(0.1f, 0.1f);
	///Add to character object
	Character * _platshad18 = new Character(platformshadow18);
	Platform18 = new Character(platform18, _platshad18);
	this->addChild(Platform18->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform18->getShadow(0)->getSprite(), -53);//z = -50
	Platform18->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform18->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create small platforms to exit
	Sprite * platform19;
	platform19 = Sprite::create("UA/Background/platform1.png");
	platform19->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform19->setPosition(4300, 1250);
	platform19->setScale(0.1f, 0.1f);
	Sprite * platformshadow19;
	platformshadow19 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow19->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow19->setPosition(4275, 1275);
	platformshadow19->setScale(0.1f, 0.1f);
	///Add to character object
	Character * _platshad19 = new Character(platformshadow19);
	Platform19 = new Character(platform19, _platshad19);
	this->addChild(Platform19->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform19->getShadow(0)->getSprite(), -53);//z = -50
	Platform19->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform19->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create stair 1
	Sprite * wall;
	wall = Sprite::create("UA/Background/wall.png");
	wall->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall->setPosition(400, -155);
	wall->setScale(2.0, 0.5);
	Sprite * wallshadow;
	wallshadow = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow->setPosition(375, -130);
	wallshadow->setScale(2.0, 0.5);
	///add to character object
	Character * _wallshad = new Character(wallshadow);
	Wall = new Character(wall, _wallshad);
	this->addChild(Wall->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall->getShadow(0)->getSprite(), -53);// z = -50
	Wall->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create stair 2
	Sprite* wall2;
	wall2 = Sprite::create("UA/Background/wall.png");
	wall2->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall2->setPosition(600, -70);
	wall2->setScale(2.0, 0.5);
	Sprite* wallshadow2;
	wallshadow2 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow2->setPosition(575, -45);
	wallshadow2->setScale(2.0, 0.5);
	///add to character object
	Character * _wallshad2 = new Character(wallshadow2);
	Wall2 = new Character(wall2, _wallshad2);
	this->addChild(Wall2->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall2->getShadow(0)->getSprite(), -53);// z = -50 (way behind player)
	Wall2->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create stair 3
	Sprite* wall3;
	wall3 = Sprite::create("UA/Background/wall.png");
	wall3->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall3->setPosition(800, 15);
	wall3->setScale(2.0, 0.5);
	Sprite* wallshadow3;
	wallshadow3 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow3->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow3->setPosition(775, 40);
	wallshadow3->setScale(2.0, 0.5);
	///add to character object
	Character * _wallshad3 = new Character(wallshadow3);
	Wall3 = new Character(wall3, _wallshad3);
	this->addChild(Wall3->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall3->getShadow(0)->getSprite(), -53);// z = -50 (way behind player)
	Wall3->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall3->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create stair 4
	Sprite * wall4;
	wall4 = Sprite::create("UA/Background/wall.png");
	wall4->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall4->setPosition(1000, 100);
	wall4->setScale(2.0, 0.5);
	Sprite * wallshadow4;
	wallshadow4 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow4->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow4->setPosition(975, 125);
	wallshadow4->setScale(2.0, 0.5);
	///add to character object
	Character * _wallshad4 = new Character(wallshadow4);
	Wall4 = new Character(wall4, _wallshad4);
	this->addChild(Wall4->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall4->getShadow(0)->getSprite(), -53);// z = -50
	Wall4->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall4->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall platform after stairs
	Sprite * wall5;
	wall5 = Sprite::create("UA/Background/wall.png");
	wall5->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall5->setPosition(1715, 225);
	wall5->setScaleY(0.3);
	Sprite * wallshadow5;
	wallshadow5 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow5->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow5->setPosition(1690, 250);
	wallshadow5->setScaleY(0.3);
	///add to character object
	Character * _wallshad5 = new Character(wallshadow5);
	Wall5 = new Character(wall5, _wallshad5);
	this->addChild(Wall5->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall5->getShadow(0)->getSprite(), -53);// z = -50
	Wall5->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall5->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall for upper barrier thing
	Sprite * wall6;
	wall6 = Sprite::create("UA/Background/wall.png");
	wall6->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall6->setPosition(550, 825);
	wall6->setScale(5.0, 0.3);
	Sprite * wallshadow6;
	wallshadow6 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow6->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow6->setPosition(525, 850);
	wallshadow6->setScale(5.0, 0.3);
	///add to character object
	Character * _wallshad6 = new Character(wallshadow6);
	Wall6 = new Character(wall6, _wallshad6);
	this->addChild(Wall6->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall6->getShadow(0)->getSprite(), -53);// z = -50
	Wall6->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall6->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall that is attached to the falling platform
	Sprite * wall7;
	wall7 = Sprite::create("UA/Background/wall.png");
	wall7->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall7->setPosition(3070, 725);
	//wall7->setScaleY(1.5);
	Sprite * wallshadow7;
	wallshadow7 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow7->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow7->setPosition(3045, 750);
	//wallshadow7->setScaleY(1.5);
	///add to character object
	Character * _wallshad7 = new Character(wallshadow7);
	Wall7 = new Character(wall7, _wallshad7);
	this->addChild(Wall7->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall7->getShadow(0)->getSprite(), -53);// z = -50
	Wall7->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall7->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall that is after the gap for the player to scale up to go further into the level
	Sprite * wall8;
	wall8 = Sprite::create("UA/Background/wall.png");
	wall8->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall8->setPosition(3681, 250);
	wall8->setScaleY(0.8);
	Sprite * wallshadow8;
	wallshadow8 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow8->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow8->setPosition(3656, 265);
	wallshadow8->setScaleY(0.8);
	///add to character object
	Character * _wallshad8 = new Character(wallshadow8);
	Wall8 = new Character(wall8, _wallshad8);
	this->addChild(Wall8->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall8->getShadow(0)->getSprite(), -53);// z = -50
	Wall8->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall8->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall for small shadow area to scale by falling platform
	Sprite * wall9;
	wall9 = Sprite::create("UA/Background/wall.png");
	wall9->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall9->setPosition(-1725, 965);
	wall9->setScaleY(0.2);
	Sprite * wallshadow9;
	wallshadow9 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow9->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow9->setPosition(3630, 1450);
	wallshadow9->setScaleY(0.2);
	///add to character object
	Character * _wallshad9 = new Character(wallshadow9);
	Wall9 = new Character(wall9, _wallshad9);
	this->addChild(Wall9->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall9->getShadow(0)->getSprite(), -53);// z = -50
	Wall9->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall9->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create wall to close off small shadow area by falling platform
	Sprite * wall10;
	wall10 = Sprite::create("UA/Background/wall.png");
	wall10->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall10->setPosition(-1725, 965);
	wall10->setScaleY(0.0002);
	Sprite * wallshadow10;
	wallshadow10 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow10->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow10->setPosition(3906, 1525);
	wallshadow10->setScaleY(0.3);
	///add to character object
	Character * _wallshad10 = new Character(wallshadow10);
	Wall10 = new Character(wall10, _wallshad10);
	this->addChild(Wall10->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall10->getShadow(0)->getSprite(), -53);// z = -50
	Wall10->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall10->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Wall for shadow area in the second lower part of level
	Sprite * wall11;
	wall11 = Sprite::create("UA/Background/wall.png");
	wall11->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall11->setPosition(-4470, 1524);
	wall11->setScaleY(0.0006);
	Sprite * wallshadow11;
	wallshadow11 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow11->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow11->setPosition(4033, 575);
	wallshadow11->setScaleY(0.3);
	///add to character object
	Character * _wallshad11 = new Character(wallshadow11);
	Wall11 = new Character(wall11, _wallshad11);
	this->addChild(Wall11->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall11->getShadow(0)->getSprite(), -53);// z = -50
	Wall11->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall11->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Wall for physical button to open shadow area that opens exit
	Sprite * wall12;
	wall12 = Sprite::create("UA/Background/wall.png");
	wall12->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall12->setPosition(4930, 200);
	wall12->setScale(5.0, 0.3);
	Sprite * wallshadow12;
	wallshadow12 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow12->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow12->setPosition(4905, 225);
	wallshadow12->setScale(5.0, 0.3);
	///add to character object
	Character * _wallshad12 = new Character(wallshadow12);
	Wall12 = new Character(wall12, _wallshad12);
	this->addChild(Wall12->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall12->getShadow(0)->getSprite(), -53);// z = -50
	Wall12->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall12->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Wall that blocks the exit
	Sprite * wall13;
	wall13 = Sprite::create("UA/Background/wall.png");
	wall13->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall13->setPosition(4790, 1485);
	wall13->setScaleY(0.35);
	Sprite * wallshadow13;
	wallshadow13 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow13->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow13->setPosition(4765, 1510);
	wallshadow13->setScaleY(0.35);
	///add to character object
	Character * _wallshad13 = new Character(wallshadow13);
	Wall13 = new Character(wall13, _wallshad13);
	this->addChild(Wall13->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall13->getShadow(0)->getSprite(), -53);// z = -50
	Wall13->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall13->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Left Boundary Wall
	Sprite* boundary1;
	boundary1 = Sprite::create("UA/Background/wall.png");
	boundary1->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundary1->setPosition(75, 590);
	boundary1->setScaleY(2.0);
	Sprite* boundaryshadow1;
	boundaryshadow1 = Sprite::create("UA/Background/wall_shadow.png");
	boundaryshadow1->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundaryshadow1->setPosition(50, 615);
	boundaryshadow1->setScaleY(2.0);
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
	boundary2->setPosition(5075, 590);
	boundary2->setScaleY(2.0);
	Sprite* boundaryshadow2;
	boundaryshadow2 = Sprite::create("UA/Background/wall_shadow.png");
	boundaryshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundaryshadow2->setPosition(5050, 615);
	boundaryshadow2->setScaleY(2.0);
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
	ceiling->setScale(5.0f, 0.5f);
	Sprite * ceilingshadow;
	ceilingshadow = Sprite::create("UA/Background/ceiling_shadow.png");
	ceilingshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	ceilingshadow->setPosition(1390, 1825);
	ceilingshadow->setScale(5.0f, 0.5f);
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
	button->setPosition(550, 1360);
	Sprite* buttonShadow;
	buttonShadow = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadow->setPosition(2606, 1490);
	///add to character object
	Character * _buttonShad = new Character(buttonShadow);
	Button1 = new Character(button, _buttonShad);
	this->addChild(Button1->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Button1->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	Button1->getSprite()->getPhysicsBody()->setDynamic(false);
	Button1->getSprite()->getPhysicsBody()->setTag(flag1Tag);

	//Create button aesthetics
	buttonBot1 = Sprite::create("UA/Level/ButtonBottom.png");
	buttonBot1->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBot1->setPosition(550, 1360);
	this->addChild(buttonBot1, 1);

	//Create button aesthetics
	buttonBotShad1 = Sprite::create("UA/Level/ButtonBottomShadow.png");
	buttonBotShad1->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBotShad1->setPosition(2606, 1490);
	this->addChild(buttonBotShad1, -53);

	//Create Button
	Sprite* button2;
	button2 = Sprite::create("UA/Level/ButtonTop.png");
	button2->setAnchorPoint(Vec2(0.5f, 0.5f));
	button2->setPosition(4930, 426);
	Sprite* buttonShadow2;
	buttonShadow2 = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadow2->setPosition(3775, 1388);
	///add to character object
	Character * _buttonShad2 = new Character(buttonShadow2);
	Button2 = new Character(button2, _buttonShad2);
	this->addChild(Button2->getSprite(), -52);// z = -49 (way behind player)
	this->addChild(Button2->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	Button2->getSprite()->getPhysicsBody()->setDynamic(false);
	Button2->getSprite()->getPhysicsBody()->setTag(flag2Tag);

	//Create button aesthetics
	buttonBot2 = Sprite::create("UA/Level/ButtonBottom.png");
	buttonBot2->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBot2->setPosition(4930, 426);
	this->addChild(buttonBot2, 1);

	//Create button aesthetics
	buttonBotShad2 = Sprite::create("UA/Level/ButtonBottomShadow.png");
	buttonBotShad2->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBotShad2->setPosition(3775, 1388);
	this->addChild(buttonBotShad2, -53);

	//Create Button
	//Physical button will not be used
	Sprite* button3;
	button3 = Sprite::create("UA/Level/ButtonTop.png");
	button3->setAnchorPoint(Vec2(0.5f, 0.5f));
	button3->setPosition(-4230, 888);
	Sprite* buttonShadow3;
	buttonShadow3 = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadow3->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadow3->setPosition(3830, 435);
	///add to character object
	Character * _buttonShad3 = new Character(buttonShadow3);
	Button3 = new Character(button3, _buttonShad3);
	this->addChild(Button3->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Button3->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	Button3->getSprite()->getPhysicsBody()->setDynamic(false);
	Button3->getSprite()->getPhysicsBody()->setTag(flag3Tag);

	//Create button aesthetics
	buttonBot3 = Sprite::create("UA/Level/ButtonBottom.png");
	buttonBot3->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBot3->setPosition(-4230, 888);
	this->addChild(buttonBot3, 1);

	//Create button aesthetics
	buttonBotShad3 = Sprite::create("UA/Level/ButtonBottomShadow.png");
	buttonBotShad3->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBotShad3->setPosition(3830, 435);
	this->addChild(buttonBotShad3, -53);

	door = Sprite::create("UA/Level/door2.png");
	door->setAnchorPoint(Vec2(0.5f, 0.5f));
	door->setPosition(5033, 1375);
	door->setScale(0.5f, 0.5f);
	this->addChild(door, -48);

	firstDoor = Sprite::create("UA/Level/closedDoor.png");
	firstDoor->setAnchorPoint(Vec2(0.5f, 0.5f));
	firstDoor->setPosition(114, 176);
	firstDoor->setScale(0.5f, 0.5f);
	this->addChild(firstDoor, -48);
}
//Init the static physics world pointer. Set it to be a nullptr which means it points to nothing
PhysicsWorld* LevelFive::physicsWorld = nullptr;
Scene* LevelFive::sceneHandle = nullptr;