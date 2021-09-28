#include "LevelFour.h"
#include "LevelFiveTransition.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"

USING_NS_CC;
using namespace Input;

Scene* LevelFour::createScene()
{
	//Background Music
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/game_music.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/game_music.mp3", true);
	//Effects
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/jump.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/dash.mp3");
	// 'scene' is an autorelease object
	Scene* scene = Scene::createWithPhysics();
	LevelFour* layer = LevelFour::create();
	scene->addChild(layer);
	sceneHandle = scene;
	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	//Get the physics world from the scene so that we can work with it later
	physicsWorld = scene->getPhysicsWorld();
	return scene;
}

void LevelFour::onExit()
{
	Scene::onExit();
}

void LevelFour::onEnter()
{
	DISPLAY->createDebugConsole(true);
	std::cout << "THE CONSOLE IS NOW OPEN" << std::endl;//uncoment this to remove console window
	Scene::onEnter();
}

// on "init" you need to initialize your instance
bool LevelFour::init()
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
	boundry.setRect(0, 0, 3810, 1120);

	//Player->getShadow(0)->health = 1;
	for (int i = 0; i < 2; i++) {
		Sprite * enemies;
		enemies = Sprite::create("UA/Enemies/placeholderV2.png");
		if (i == 0) enemies->setPosition(355, 407);
		if (i == 1) enemies->setPosition(1175, 148);
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
	/*Sprite * enemies2;
	enemies2 = Sprite::create("UA/Enemies/placeholderV2.png");
	enemies2->setPosition(558, 808);
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

	en2->getShadow(0)->getSprite()->setColor(Color3B(0, 0, 0));*/

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();
	//this->getCameras().erase( this->getCameras().end());

	return true;
}

void LevelFour::FlipWorld()
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
	//Platform10->flipWorld(wallCollisionTag);
	Platform11->flipWorld(wallCollisionTag);
	Platform12->flipWorld(wallCollisionTag);
	Platform13->flipWorld(wallCollisionTag);
	Platform14->flipWorld(wallCollisionTag);
	Platform15->flipWorld(wallCollisionTag);
	Platform16->flipWorld(wallCollisionTag);
	Platform17->flipWorld(wallCollisionTag);
	Platform18->flipWorld(wallCollisionTag);
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
	Wall14->flipWorld(wallCollisionTag);
	Wall15->flipWorld(wallCollisionTag);
	Wall16->flipWorld(wallCollisionTag);
	Wall17->flipWorld(wallCollisionTag);
	Boundary1->flipWorld(wallCollisionTag);
	Boundary2->flipWorld(wallCollisionTag);
	Ceiling->flipWorld(wallCollisionTag);
	Ceiling2->flipWorld(wallCollisionTag);
	ButtonTop->flipWorld(flag1Tag);
	ButtonTop2->flipWorld(flag2Tag);
	ButtonTop3->flipWorld(flag3Tag);
	ButtonTop4->flipWorld(flag4Tag);
	ButtonTop5->flipWorld(flag5Tag);
	//Button2->flipWorld(flag2Tag);
	for (int i = 0; i < Enemies.size(); i++)
		Enemies.at(i)->flipWorld(enemyCollisionTag);

	if (Player->isShadow == false) {
		//back to idle
		if (Player->animState != 0 && grounded == true && onWall == false) {
			if (Player->animState == 1) {
				Player->getSprite()->stopAction(walking);
			}
			Player->getSprite()->runAction(idle);
			Player->animState = 0;
		}
		if (Player->getShadow(0)->animState != 0 && grounded == true && onWall == false) {
			if (Player->getShadow(0)->animState == 1) {
				Player->getShadow(0)->getSprite()->stopAction(walkingS);
			}
			Player->getShadow(0)->getSprite()->runAction(idleS);
			Player->getShadow(0)->animState = 0;
		}
	}
	else {
		Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x * 0.9, Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));
		//back to idle
		if (Player->getShadow(0)->animState != 0 && grounded == true && onWall == false) {
			if (Player->getShadow(0)->animState == 1) {
				Player->getShadow(0)->getSprite()->stopAction(walkingS);
			}
			//if (Player->animState == 2) {
			//	Player->getShadow(0)->getSprite()->stopAction(jumpS);
			//}
			Player->getShadow(0)->getSprite()->runAction(idleS);
			Player->getShadow(0)->animState = 0;
		}
	}
}

void LevelFour::update(float deltaTime)//UPDATE LOOP
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
		std::cout << "level5t" << std::endl;
		this->stopAllActions();
		this->removeAllComponents();
		cocos2d::CCDirector::sharedDirector()->purgeCachedData();
		SpriteFrameCache::getInstance()->removeSpriteFrames();
		SpriteFrameCache::destroyInstance();
		this->cleanup();
		DISPLAY->init(1000.0f, 500.0f, "Shadow Game (Stalactites)", false);
		Scene* level5t = LevelFiveTransition::createScene();
		director->getInstance()->replaceScene(level5t);
	}
	else if (Player->getSprite()->getPosition().x >= 3645 && Player->getSprite()->getPosition().y >= 800)
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

void LevelFour::UpdatePositions(float dt)
{
	//not in use
}

bool LevelFour::checkEnd()
{
	//not in use
	return false;
}

void LevelFour::CheckCollision()
{

	//not in use
}

void LevelFour::initCollisionCallback()
{
	//Create the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	//Assign the callback function
	contactListener->onContactBegin = CC_CALLBACK_1(LevelFour::onContactBeginCallback, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(LevelFour::onSepBeginCallback, this);
	//Add the contact listener to the event dispatcher
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}


bool LevelFour::onContactBeginCallback(PhysicsContact& contact)
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
					//shift->runAction(FadeOut::create(1.0f));
					ButtonTop->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall9->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall9->getShadow(0)->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1))); 
					//Wall9->getSprite()->runAction(DelayTime::create(1.0));
					Wall9->getSprite()->runAction(MoveBy::create(0.1, Vec2(0, +30)));
					Wall9->getShadow(0)->getSprite()->runAction(MoveBy::create(0.1, Vec2(0, +100)));
					Wall->getShadow(0)->getSprite()->setPosition(950, 30);
				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					ButtonTop->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall9->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall9->getShadow(0)->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall9->getSprite()->runAction(DelayTime::create(1.0));
					Wall9->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
					Wall9->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
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
				if (Player->isShadow == false) {
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					//shift->runAction(FadeOut::create(1.0f));
					ButtonTop2->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall10->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall10->getShadow(0)->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall10->getSprite()->runAction(DelayTime::create(1.0));
					Wall10->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
					Wall10->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					ButtonTop2->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall10->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall10->getShadow(0)->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall10->getSprite()->runAction(DelayTime::create(1.0));
					Wall10->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
					Wall10->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
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
					ButtonTop3->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Platform14->getSprite()->setPosition(Vec2(2995, 591));
					//Wall14->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall14->getShadow(0)->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall14->getSprite()->runAction(DelayTime::create(1.0));
					Wall14->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
					Wall14->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
					Platform11->getSprite()->setPosition(Vec2(2770, 410));
					Wall17->getSprite()->setPosition(Vec2(2875, 638));
				}
				return true;
			}
			if (tagB == flag4Tag)
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
					ButtonTop4->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall15->getSprite()->setPosition(Vec2(975, 533));
					Wall15->getShadow(0)->getSprite()->setPosition(Vec2(950, 558));

				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					ButtonTop4->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall15->getSprite()->setPosition(Vec2(975, 533));
					Wall15->getShadow(0)->getSprite()->setPosition(Vec2(950, 558));
				}
				return true;
			}
			if (tagB == flag5Tag)
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
					ButtonTop5->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Platform9->getSprite()->setPosition(Vec2(1500, 605));
					Wall10->getSprite()->setScaleY(0.184);
					Wall10->getShadow(0)->getSprite()->setScaleY(0.184);
					Wall10->getSprite()->setPosition(1724, 528);
					Wall10->getShadow(0)->getSprite()->setPosition(1699, 553);
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
					//shift->runAction(FadeOut::create(1.0f));
					ButtonTop->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall9->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall9->getShadow(0)->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall9->getSprite()->runAction(DelayTime::create(1.0));
					Wall9->getSprite()->runAction(MoveBy::create(0.1, Vec2(0, +30)));
					Wall9->getShadow(0)->getSprite()->runAction(MoveBy::create(0.1, Vec2(0, +100)));

				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					ButtonTop->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall9->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall9->getShadow(0)->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall9->getSprite()->runAction(DelayTime::create(1.0));
					Wall9->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
					Wall9->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
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
				if (Player->isShadow == false) {
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					//shift->runAction(FadeOut::create(1.0f));
					ButtonTop2->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall10->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall10->getShadow(0)->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall10->getSprite()->runAction(DelayTime::create(1.0));
					Wall10->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
					Wall10->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					ButtonTop2->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall10->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall10->getShadow(0)->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall10->getSprite()->runAction(DelayTime::create(1.0));
					Wall10->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
					Wall10->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
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
					ButtonTop3->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Platform14->getSprite()->setPosition(Vec2(2995, 591));
					//Wall14->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall14->getShadow(0)->getSprite()->runAction(ScaleBy::create(0.5, (-1, -1)));
					//Wall14->getSprite()->runAction(DelayTime::create(1.0));
					Wall14->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
					Wall14->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, +100)));
					Platform11->getSprite()->setPosition(Vec2(2770, 410));
					Wall17->getSprite()->setPosition(Vec2(2875, 638));
				}
				return true;
			}
			if (tagA == flag4Tag)
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
					ButtonTop4->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall15->getSprite()->setPosition(Vec2(975, 533));
					Wall15->getShadow(0)->getSprite()->setPosition(Vec2(950, 558));
					//Platform9->getSprite()->setPosition(Vec2(1500, 605));

				}
				else if (Player->isShadow == true) {
					//shift2->runAction(FadeOut::create(1.0f));
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 0));
					ButtonTop4->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					//Wall15->getSprite()->setPosition(Vec2(975, 533));
					Wall15->getShadow(0)->getSprite()->setPosition(Vec2(950, 558));
					//Platform9->getSprite()->setPosition(Vec2(1500, 605));
				}
				return true;
			}
			if (tagA == flag5Tag)
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
					ButtonTop5->getShadow(0)->getSprite()->runAction(MoveBy::create(0.5, Vec2(0, -4)));
					Platform9->getSprite()->setPosition(Vec2(1500, 605));
					Wall10->getSprite()->setScaleY(0.184);
					Wall10->getShadow(0)->getSprite()->setScaleY(0.184);
					Wall10->getSprite()->setPosition(1724, 528);
					Wall10->getShadow(0)->getSprite()->setPosition(1699, 553);
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

void LevelFour::DrawWorld()
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
	platform->setPosition(350, 20);
	platform->setScale(0.4f, 0.5f);
	Sprite * platformshadow;
	platformshadow = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow->setPosition(325, 45);
	platformshadow->setScale(0.5f, 0.5f);
	///Add to character object
	Character * _platshad = new Character(platformshadow);
	Platform = new Character(platform, _platshad);
	this->addChild(Platform->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform->getShadow(0)->getSprite(), -53);//z = -50
	Platform->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform 2
	Sprite * platform2;
	platform2 = Sprite::create("UA/Background/platform3.png");
	platform2->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform2->setPosition(791, 0);
	platform2->setScale(0.5f, 0.5f);
	Sprite * platformshadow2;
	platformshadow2 = Sprite::create("UA/Background/platform3_shadow.png");
	platformshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow2->setPosition(766, 25);
	platformshadow2->setScale(0.5f, 0.5f);
	///Add to character object
	Character * _platshad2 = new Character(platformshadow2);
	Platform2 = new Character(platform2, _platshad2);
	this->addChild(Platform2->getSprite(), -48);// z = -49 (way behind player)
	this->addChild(Platform2->getShadow(0)->getSprite(), -53);//z = -50
	Platform2->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall  (door that collapses) Button 1
	Sprite * wall9;
	wall9 = Sprite::create("UA/Background/wall.png");
	wall9->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall9->setPosition(980, 950);
	wall9->setScaleY(0.8);
	Sprite * wallshadow9;
	wallshadow9 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow9->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow9->setPosition(955, 558);
	wallshadow9->setScaleY(0.13);
	///add to character object
	Character * _wallshad9 = new Character(wallshadow9);
	Wall9 = new Character(wall9, _wallshad9);
	this->addChild(Wall9->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall9->getShadow(0)->getSprite(), -53);// z = -50
	Wall9->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall9->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall  for wall jummp
	Sprite * wall15;
	wall15 = Sprite::create("UA/Background/wall.png");
	wall15->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall15->setPosition(-975, -533);
	wall15->setScaleY(0.13);
	Sprite * wallshadow15;
	wallshadow15 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow15->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow15->setPosition(-950, -558);
	wallshadow15->setScaleY(0.13);
	///add to character object
	Character * _wallshad15 = new Character(wallshadow15);
	Wall15 = new Character(wall15, _wallshad15);
	this->addChild(Wall15->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall15->getShadow(0)->getSprite(), -53);// z = -50
	Wall15->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall15->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall
	Sprite * wall;
	wall = Sprite::create("UA/Background/wall.png");
	wall->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall->setPosition(975, 150);
	wall->setScaleY(0.45);
	Sprite * wallshadow;
	wallshadow = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow->setPosition(950, 175);
	wallshadow->setScaleY(0.45);
	///add to character object
	Character * _wallshad = new Character(wallshadow);
	Wall = new Character(wall, _wallshad);
	this->addChild(Wall->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall->getShadow(0)->getSprite(), -53);// z = -50
	Wall->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Ceiling - beginning - physical cant scale up
	Sprite * ceiling2;
	ceiling2 = Sprite::create("UA/Background/ceiling.png");
	ceiling2->setAnchorPoint(Vec2(0.5f, 0.5f));
	ceiling2->setPosition(549, 642);
	ceiling2->setScale(0.075f, 0.12f);
	Sprite * ceilingshadow2;
	ceilingshadow2 = Sprite::create("UA/Background/ceiling_shadow.png");
	ceilingshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	ceilingshadow2->setPosition(-524, -665);
	ceilingshadow2->setScale(0.00075, 0.000012f);
	///Add to character object
	Character * _ceilingshad2 = new Character(ceilingshadow2);
	Ceiling2 = new Character(ceiling2, _ceilingshad2);
	this->addChild(Ceiling2->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Ceiling2->getShadow(0)->getSprite(), -53);//z = -50
	Ceiling2->getSprite()->getPhysicsBody()->setDynamic(false);
	Ceiling2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform 
	Sprite * platform3;
	platform3 = Sprite::create("UA/Background/platform1.png");
	platform3->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform3->setPosition(-540, -700);
	platform3->setScale(0.00067f, 0.0005f);
	Sprite * platformshadow3;
	platformshadow3 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow3->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow3->setPosition(530, 700);
	platformshadow3->setScale(0.67f, 0.5f);
	///Add to character object
	Character * _platshad3 = new Character(platformshadow3);
	Platform3 = new Character(platform3, _platshad3);
	this->addChild(Platform3->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform3->getShadow(0)->getSprite(), -53);//z = -50
	Platform3->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform3->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall
	Sprite * wall2;
	wall2 = Sprite::create("UA/Background/wall.png");
	wall2->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall2->setPosition(825, 325);
	wall2->setScaleY(0.2);
	Sprite * wallshadow2;
	wallshadow2 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow2->setPosition(800, 350);
	wallshadow2->setScaleY(0.2);
	///add to character object
	Character * _wallshad2 = new Character(wallshadow2);
	Wall2 = new Character(wall2, _wallshad2);
	this->addChild(Wall2->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall2->getShadow(0)->getSprite(), -53);// z = -50
	Wall2->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall2->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform 
	Sprite * platform4;
	platform4 = Sprite::create("UA/Background/platform1.png");
	platform4->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform4->setPosition(1346, 40);
	platform4->setScale(0.5f, 0.5f);
	Sprite * platformshadow4;
	platformshadow4 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow4->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow4->setPosition(1321, 65);
	platformshadow4->setScale(0.5f, 0.5f);
	///Add to character object
	Character * _platshad4 = new Character(platformshadow4);
	Platform4 = new Character(platform4, _platshad4);
	this->addChild(Platform4->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform4->getShadow(0)->getSprite(), -53);//z = -50
	Platform4->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform4->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall 3
	Sprite * wall3;
	wall3 = Sprite::create("UA/Background/wall.png");
	wall3->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall3->setPosition(-800, -840);
	wall3->setScaleY(0.0000025);
	Sprite * wallshadow3;
	wallshadow3 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow3->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow3->setPosition(775, 865);
	wallshadow3->setScaleY(0.25);
	///add to character object
	Character * _wallshad3 = new Character(wallshadow3);
	Wall3 = new Character(wall3, _wallshad3);
	this->addChild(Wall3->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall3->getShadow(0)->getSprite(), -53);// z = -50
	Wall3->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall3->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall 1
	Sprite * wall4;
	wall4 = Sprite::create("UA/Background/wall.png");
	wall4->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall4->setPosition(-440, -840);
	wall4->setScaleY(0.000025);
	Sprite * wallshadow4;
	wallshadow4 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow4->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow4->setPosition(415, 865);
	wallshadow4->setScaleY(0.25);
	///add to character object
	Character * _wallshad4 = new Character(wallshadow4);
	Wall4 = new Character(wall4, _wallshad4);
	this->addChild(Wall4->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall4->getShadow(0)->getSprite(), -53);// z = -50
	Wall4->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall4->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall 2
	Sprite * wall5;
	wall5 = Sprite::create("UA/Background/wall.png");
	wall5->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall5->setPosition(-620, -1100);
	wall5->setScaleY(0.00003);
	Sprite * wallshadow5;
	wallshadow5 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow5->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow5->setPosition(595, 1125);
	wallshadow5->setScaleY(0.3);
	///add to character object
	Character * _wallshad5 = new Character(wallshadow5);
	Wall5 = new Character(wall5, _wallshad5);
	this->addChild(Wall5->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall5->getShadow(0)->getSprite(), -53);// z = -50
	Wall5->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall5->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall 
	Sprite * wall6;
	wall6 = Sprite::create("UA/Background/wall.png");
	wall6->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall6->setPosition(1719, 50);
	wall6->setScaleY(0.5);
	Sprite * wallshadow6;
	wallshadow6 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow6->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow6->setPosition(1694, 75);
	wallshadow6->setScaleY(0.5);
	///add to character object
	Character * _wallshad6 = new Character(wallshadow6);
	Wall6 = new Character(wall6, _wallshad6);
	this->addChild(Wall6->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall6->getShadow(0)->getSprite(), -53);// z = -50
	Wall6->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall6->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall (opens with platform) button 2
	Sprite * wall10;
	wall10 = Sprite::create("UA/Background/wall.png");
	wall10->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall10->setPosition(1724, 958);
	wall10->setScaleY(0.8);
	Sprite * wallshadow10;
	wallshadow10 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow10->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow10->setPosition(1699, 983);
	wallshadow10->setScaleY(0.8);
	///add to character object
	Character * _wallshad10 = new Character(wallshadow10);
	Wall10 = new Character(wall10, _wallshad10);
	this->addChild(Wall10->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall10->getShadow(0)->getSprite(), -53);// z = -50
	Wall10->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall10->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform 
	Sprite * platform5;
	platform5 = Sprite::create("UA/Background/platform1.png");
	platform5->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform5->setPosition(2438, 10);
	platform5->setScale(1.0f, 0.5f);
	Sprite * platformshadow5;
	platformshadow5 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow5->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow5->setPosition(2413, 35);
	platformshadow5->setScale(1.0f, 0.5f);
	///Add to character object
	Character * _platshad5 = new Character(platformshadow5);
	Platform5 = new Character(platform5, _platshad5);
	this->addChild(Platform5->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform5->getShadow(0)->getSprite(), -53);//z = -50
	Platform5->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform5->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform 
	Sprite * platform6;
	platform6 = Sprite::create("UA/Background/platform1.png");
	platform6->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform6->setPosition(325, 330);
	platform6->setScale(0.37f, 0.3f);
	Sprite * platformshadow6;
	platformshadow6 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow6->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow6->setPosition(300, 355);
	platformshadow6->setScale(0.37f, 0.3f);
	///Add to character object
	Character * _platshad6 = new Character(platformshadow6);
	Platform6 = new Character(platform6, _platshad6);
	this->addChild(Platform6->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform6->getShadow(0)->getSprite(), -53);//z = -50
	Platform6->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform6->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall 
	Sprite * wall7;
	wall7 = Sprite::create("UA/Background/wall.png");
	wall7->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall7->setPosition(630, 375);
	wall7->setScale(2.0f, 0.13f);
	Sprite * wallshadow7;
	wallshadow7 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow7->setScale(2.0f, 0.13f);
	wallshadow7->setPosition(605, 400);
	wallshadow7->setAnchorPoint(Vec2(0.5f, 0.5f));
	///add to character object
	Character * _wallshad7 = new Character(wallshadow7);
	Wall7 = new Character(wall7, _wallshad7);
	this->addChild(Wall7->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall7->getShadow(0)->getSprite(), -53);// z = -50
	Wall7->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall7->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//149.001, 807.8
	//	3273.87, 807.798

	//Create Wall - blocking exit rises (button 3)
	Sprite * wall14;
	wall14 = Sprite::create("UA/Background/wall.png");
	wall14->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall14->setPosition(3253, 950);
	wall14->setScale(2.0f, 1.0f);
	Sprite * wallshadow14;
	wallshadow14 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow14->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow14->setPosition(3227, 975);
	wallshadow14->setScale(2.0f, 1.0f);
	///add to character object
	Character * _wallshad14 = new Character(wallshadow14);
	Wall14 = new Character(wall14, _wallshad14);
	this->addChild(Wall14->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall14->getShadow(0)->getSprite(), -53);// z = -50
	Wall14->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall14->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);


	//Create Platform (square) end
	Sprite * platform7;
	platform7 = Sprite::create("UA/Background/platform6.png");
	platform7->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform7->setPosition(3418, 375);
	platform7->setScale(0.8f, 1.0f);
	Sprite * platformshadow7;
	platformshadow7 = Sprite::create("UA/Background/platform6_shadow.png");
	platformshadow7->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow7->setPosition(3393, 400);
	platformshadow7->setScale(0.8f, 1.0f);
	///Add to character object
	Character * _platshad7 = new Character(platformshadow7);
	Platform7 = new Character(platform7, _platshad7);
	this->addChild(Platform7->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform7->getShadow(0)->getSprite(), -53);//z = -50
	Platform7->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform7->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Platform for button
	Sprite * platform8;
	platform8 = Sprite::create("UA/Background/platform1.png");
	platform8->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform8->setPosition(1800, 702);
	platform8->setScale(0.15f, 0.3f);
	Sprite * platformshadow8;
	platformshadow8 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow8->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow8->setPosition(1775, 727);
	platformshadow8->setScale(0.15f, 0.3f);
	///Add to character object
	Character * _platshad8 = new Character(platformshadow8);
	Platform8 = new Character(platform8, _platshad8);
	this->addChild(Platform8->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform8->getShadow(0)->getSprite(), -53);//z = -50
	Platform8->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform8->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Wall 
	Sprite * wall8;
	wall8 = Sprite::create("UA/Background/wall.png");
	wall8->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall8->setPosition(1940, 1005);
	wall8->setScale(1.5f, 0.5f);
	Sprite * wallshadow8;
	wallshadow8 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow8->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow8->setPosition(1915, 1030);
	wallshadow8->setScale(1.5f, 0.5f);
	///add to character object
	Character * _wallshad8 = new Character(wallshadow8);
	Wall8 = new Character(wall8, _wallshad8);
	this->addChild(Wall8->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall8->getShadow(0)->getSprite(), -53);// z = -50
	Wall8->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall8->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//2222.8, 117.805
	//2490.03, 117.803
	//2788.31, 117.805

	//Create likkle jump platforms (square) 1
	Sprite * wall11;
	wall11 = Sprite::create("UA/Background/wall.png");
	wall11->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall11->setPosition(2200, 189);
	wall11->setScale(1.0f, 0.15f);
	Sprite * wallshadow11;
	wallshadow11 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow11->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow11->setPosition(2175, 214);
	wallshadow11->setScale(1.0f, 0.15f);
	///Add to character object
	Character * _wallshad11 = new Character(wallshadow11);
	Wall11 = new Character(wall11, _wallshad11);
	this->addChild(Wall11->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall11->getShadow(0)->getSprite(), -53);// z = -50
	Wall11->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall11->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create likkle jump platforms (square) 2
	Sprite * wall12;
	wall12 = Sprite::create("UA/Background/wall.png");
	wall12->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall12->setPosition(2550, 189);
	wall12->setScale(1.0f, 0.15f);
	Sprite * wallshadow12;
	wallshadow12 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow12->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow12->setPosition(2525, 214);
	wallshadow12->setScale(1.0f, 0.15f);
	///Add to character object
	Character * _wallshad12 = new Character(wallshadow12);
	Wall12 = new Character(wall12, _wallshad12);
	this->addChild(Wall12->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall12->getShadow(0)->getSprite(), -53);// z = -50
	Wall12->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall12->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create likkle jump platforms (square) 3
	Sprite *wall13;
	wall13 = Sprite::create("UA/Background/wall.png");
	wall13->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall13->setPosition(2910, 189);
	wall13->setScale(1.0f, 0.15f);
	Sprite * wallshadow13;
	wallshadow13 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow13->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow13->setPosition(2885, 214);
	wallshadow13->setScale(1.0f, 0.15f);
	///Add to character object
	Character * _wallshad13 = new Character(wallshadow13);
	Wall13 = new Character(wall13, _wallshad13);
	this->addChild(Wall13->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall13->getShadow(0)->getSprite(), -53);// z = -50
	Wall13->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall13->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create likkle jump platforms UP (square) 1
	Sprite * platform12;
	platform12 = Sprite::create("UA/Background/platform3.png");
	platform12->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform12->setPosition(2000, 410);
	platform12->setScale(0.2f, 0.4f);
	Sprite * platformshadow12;
	platformshadow12 = Sprite::create("UA/Background/platform3_shadow.png");
	platformshadow12->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow12->setPosition(1975, 435);
	platformshadow12->setScale(0.2f, 0.4f);
	///Add to character object
	Character * _platshad12 = new Character(platformshadow12);
	Platform12 = new Character(platform12, _platshad12);
	this->addChild(Platform12->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform12->getShadow(0)->getSprite(), -53);//z = -50
	Platform12->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform12->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create likkle jump platforms UP (square) 2
	Sprite * platform13;
	platform13 = Sprite::create("UA/Background/platform3.png");
	platform13->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform13->setPosition(2400, 410);
	platform13->setScale(0.2f, 0.4f);
	Sprite * platformshadow13;
	platformshadow13 = Sprite::create("UA/Background/platform3_shadow.png");
	platformshadow13->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow13->setPosition(2375, 435);
	platformshadow13->setScale(0.2f, 0.4f);
	///Add to character object
	Character * _platshad13 = new Character(platformshadow13);
	Platform13 = new Character(platform13, _platshad13);
	this->addChild(Platform13->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform13->getShadow(0)->getSprite(), -53);//z = -50
	Platform13->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform13->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);
	//2762.04, 430.903
	//Create likkle jump platforms UP (square) 3
	Sprite * platform11;
	platform11 = Sprite::create("UA/Background/platform3.png");
	platform11->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform11->setPosition(-2770, -410);
	platform11->setScale(0.2f, 0.4f);
	Sprite * platformshadow11;
	platformshadow11 = Sprite::create("UA/Background/platform3_shadow.png");
	platformshadow11->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow11->setPosition(2745, 435);
	platformshadow11->setScale(0.2f, 0.4f);
	///Add to character object
	Character * _platshad11 = new Character(platformshadow11);
	Platform11 = new Character(platform11, _platshad11);
	this->addChild(Platform11->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform11->getShadow(0)->getSprite(), -53);//z = -50
	Platform11->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform11->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Shadow only - turns into solid after button press button 3
	Sprite * platform14;
	platform14 = Sprite::create("UA/Background/platform1.png");
	platform14->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform14->setPosition(-3240, -800);
	platform14->setScale(0.15f, 0.4f);
	Sprite * platformshadow14;
	platformshadow14 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow14->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow14->setPosition(2970, 616);
	platformshadow14->setScale(0.15f, 0.4f);
	///Add to character object
	Character * _platshad14 = new Character(platformshadow14);
	Platform14 = new Character(platform14, _platshad14);
	this->addChild(Platform14->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform14->getShadow(0)->getSprite(), -53);//z = -50
	Platform14->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform14->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);


	//Shadow only 
	Sprite * platform15;
	platform15 = Sprite::create("UA/Background/platform1.png");
	platform15->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform15->setPosition(-3240, -800);
	platform15->setScale(0.00000000000077f, 0.000000004444f);
	Sprite * platformshadow15;
	platformshadow15 = Sprite::create("UA/Background/platform1_shadow.png");
	platformshadow15->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow15->setPosition(2320, 616);
	platformshadow15->setScale(0.5f, 0.4f);
	///Add to character object
	Character * _platshad15 = new Character(platformshadow15);
	Platform15 = new Character(platform15, _platshad15);
	this->addChild(Platform15->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform15->getShadow(0)->getSprite(), -53);//z = -50
	Platform15->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform15->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);
	//2700.48, 727.09
	//	2708.81, 482.095
	//	2769.33, 294.29
	//	2939.8, 722.576
	//	2870.07, 745.746


	//Create wall for wall jump
	Sprite *wall16;
	wall16 = Sprite::create("UA/Background/wall.png");
	wall16->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall16->setPosition(-2650, -670);
	wall16->setScale(1.0f, 0.15f);
	Sprite * wallshadow16;
	wallshadow16 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow16->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow16->setPosition(2650, 663);
	wallshadow16->setScale(1.0f, 0.15f);
	///Add to character object
	Character * _wallshad16 = new Character(wallshadow16);
	Wall16 = new Character(wall16, _wallshad16);
	this->addChild(Wall16->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall16->getShadow(0)->getSprite(), -53);// z = -50
	Wall16->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall16->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create wall for wall jump
	Sprite *wall17;
	wall17 = Sprite::create("UA/Background/wall.png");
	wall17->setAnchorPoint(Vec2(0.5f, 0.5f));
	wall17->setPosition(-2870, -670);
	wall17->setScale(1.0f, 0.15f);
	Sprite * wallshadow17;
	wallshadow17 = Sprite::create("UA/Background/wall_shadow.png");
	wallshadow17->setAnchorPoint(Vec2(0.5f, 0.5f));
	wallshadow17->setPosition(2850, 663);
	wallshadow17->setScale(1.0f, 0.15f);
	///Add to character object
	Character * _wallshad17 = new Character(wallshadow17);
	Wall17 = new Character(wall17, _wallshad17);
	this->addChild(Wall17->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(Wall17->getShadow(0)->getSprite(), -53);// z = -50
	Wall17->getSprite()->getPhysicsBody()->setDynamic(false);
	Wall17->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);


	//Create likkle jump platforms (square) 1 Scene 2
	Sprite * platform16;
	platform16 = Sprite::create("UA/Background/platform6.png");
	platform16->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform16->setPosition(-1200, -305);
	platform16->setScale(0.001f, 0.001f);
	Sprite * platformshadow16;
	platformshadow16 = Sprite::create("UA/Background/platform6_shadow.png");
	platformshadow16->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow16->setPosition(1175, 330);
	platformshadow16->setScale(0.1f, 0.1f);
	///Add to character object
	Character * _platshad16 = new Character(platformshadow16);
	Platform16 = new Character(platform16, _platshad16);
	this->addChild(Platform16->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform16->getShadow(0)->getSprite(), -53);//z = -50
	Platform16->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform16->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create likkle jump platforms (square) 2 Scene 2
	Sprite * platform17;
	platform17 = Sprite::create("UA/Background/platform6.png");
	platform17->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform17->setPosition(1500, 305);
	platform17->setScale(0.1f, 0.1f);
	Sprite * platformshadow17;
	platformshadow17 = Sprite::create("UA/Background/platform6_shadow.png");
	platformshadow17->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow17->setPosition(1475, 330);
	platformshadow17->setScale(0.1f, 0.1f);
	///Add to character object
	Character * _platshad17 = new Character(platformshadow17);
	Platform17 = new Character(platform17, _platshad17);
	this->addChild(Platform17->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform17->getShadow(0)->getSprite(), -53);//z = -50
	Platform17->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform17->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create likkle jump platforms (square) 3 Scene 2
	Sprite * platform18;
	platform18 = Sprite::create("UA/Background/platform6.png");
	platform18->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform18->setPosition(-1200, -605);
	platform18->setScale(0.0001f, 0.00015f);
	Sprite * platformshadow18;
	platformshadow18 = Sprite::create("UA/Background/platform6_shadow.png");
	platformshadow18->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow18->setPosition(1175, 630);
	platformshadow18->setScale(0.1f, 0.15f);
	///Add to character object
	Character * _platshad18 = new Character(platformshadow18);
	Platform18 = new Character(platform18, _platshad18);
	this->addChild(Platform18->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform18->getShadow(0)->getSprite(), -53);//z = -50
	Platform18->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform18->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create likkle jump platforms (square) 3 Scene 2 - shadow turns into physical
	Sprite * platform9;
	platform9 = Sprite::create("UA/Background/platform6.png");
	platform9->setAnchorPoint(Vec2(0.5f, 0.5f));
	platform9->setPosition(-1500, -605);
	platform9->setScale(0.1f, 0.15f);
	Sprite * platformshadow9;
	platformshadow9 = Sprite::create("UA/Background/platform6_shadow.png");
	platformshadow9->setAnchorPoint(Vec2(0.5f, 0.5f));
	platformshadow9->setPosition(1475, 630);
	platformshadow9->setScale(0.1f, 0.15f);
	///Add to character object
	Character * _platshad9 = new Character(platformshadow9);
	Platform9 = new Character(platform9, _platshad9);
	this->addChild(Platform9->getSprite(), -50);// z = -49 (way behind player)
	this->addChild(Platform9->getShadow(0)->getSprite(), -53);//z = -50
	Platform9->getSprite()->getPhysicsBody()->setDynamic(false);
	Platform9->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);


	//Create Left Boundary Wall
	Sprite* boundary1;
	boundary1 = Sprite::create("UA/Background/wall.png");
	boundary1->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundary1->setPosition(75, 290);
	boundary1->setScaleY(2);
	Sprite* boundaryshadow1;
	boundaryshadow1 = Sprite::create("UA/Background/wall_shadow.png");
	boundaryshadow1->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundaryshadow1->setPosition(50, 315);
	boundaryshadow1->setScaleY(2);
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
	boundary2->setPosition(3710, 290);
	boundary2->setScale(2.0f, 2.0f);
	Sprite* boundaryshadow2;
	boundaryshadow2 = Sprite::create("UA/Background/wall_shadow.png");
	boundaryshadow2->setAnchorPoint(Vec2(0.5f, 0.5f));
	boundaryshadow2->setPosition(3685, 315);
	boundaryshadow2->setScale(2.0f, 2.0f);
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
	ceiling->setPosition(1415, 1220);
	ceiling->setScale(3.0f, 0.5f);
	Sprite * ceilingshadow;
	ceilingshadow = Sprite::create("UA/Background/ceiling_shadow.png");
	ceilingshadow->setAnchorPoint(Vec2(0.5f, 0.5f));
	ceilingshadow->setPosition(1415, 1220);
	ceilingshadow->setScale(3.0f, 0.5f);
	///Add to character object
	Character * _ceilingshad = new Character(ceilingshadow);
	Ceiling = new Character(ceiling, _ceilingshad);
	this->addChild(Ceiling->getSprite(), -49);// z = -49 (way behind player)
	this->addChild(Ceiling->getShadow(0)->getSprite(), -53);//z = -50
	Ceiling->getSprite()->getPhysicsBody()->setDynamic(false);
	Ceiling->getSprite()->getPhysicsBody()->setTag(wallCollisionTag);

	//Create Button (1)
	buttonBottom = Sprite::create("UA/Level/ButtonBottom.png");
	buttonBottom->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBottom->setPosition(200, 392);
	this->addChild(buttonBottom, 1);

	//Create Button (1)
	Sprite* buttonTop;
	buttonTop = Sprite::create("UA/Level/ButtonTop.png");
	buttonTop->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonTop->setPosition(200, 392);
	Sprite* buttonShadowTop;
	buttonShadowTop = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadowTop->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadowTop->setPosition(-3095, -480);
	///add to character object
	Character * _buttonShadTop = new Character(buttonShadowTop);
	ButtonTop = new Character(buttonTop, _buttonShadTop);
	this->addChild(ButtonTop->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(ButtonTop->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	ButtonTop->getSprite()->getPhysicsBody()->setDynamic(false);
	ButtonTop->getSprite()->getPhysicsBody()->setTag(flag1Tag);


	//Create Button (2)
	buttonBottom2 = Sprite::create("UA/Level/ButtonBottom.png");
	buttonBottom2->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBottom2->setPosition(1807, 764);
	this->addChild(buttonBottom2, 1);

	//Create Button (2)
	Sprite* buttonTop2;
	buttonTop2 = Sprite::create("UA/Level/ButtonTop.png");
	buttonTop2->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonTop2->setPosition(1807, 764);
	Sprite* buttonShadowTop2;
	buttonShadowTop2 = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadowTop2->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadowTop2->setPosition(-1807, -764);
	///add to character object
	Character * _buttonShadTop2 = new Character(buttonShadowTop2);
	ButtonTop2 = new Character(buttonTop2, _buttonShadTop2);
	this->addChild(ButtonTop2->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(ButtonTop2->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	ButtonTop2->getSprite()->getPhysicsBody()->setDynamic(false);
	ButtonTop2->getSprite()->getPhysicsBody()->setTag(flag2Tag);

	//2163.74, 808.8
	//Create Button (3) -Shadow
	buttonBottom3 = Sprite::create("UA/Level/ButtonBottomShadow.png");
	buttonBottom3->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBottom3->setPosition(2163, 690);
	this->addChild(buttonBottom3, 1);

	//Create Button (3) - shadow
	Sprite* buttonTop3;
	buttonTop3 = Sprite::create("UA/Level/ButtonTop.png");
	buttonTop3->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonTop3->setPosition(-1807, -764);
	Sprite* buttonShadowTop3;
	buttonShadowTop3 = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadowTop3->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadowTop3->setPosition(2163, 690);
	///add to character object
	Character * _buttonShadTop3 = new Character(buttonShadowTop3);
	ButtonTop3 = new Character(buttonTop3, _buttonShadTop3);
	this->addChild(ButtonTop3->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(ButtonTop3->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	ButtonTop3->getSprite()->getPhysicsBody()->setDynamic(false);
	ButtonTop3->getSprite()->getPhysicsBody()->setTag(flag3Tag);

	//Create Button(4) 
	buttonBottom4 = Sprite::create("UA/Level/ButtonBottom.png");
	buttonBottom4->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBottom4->setPosition(1580, 130);
	this->addChild(buttonBottom4, 1);

	//Create Button (4) makes wall appear for wall jump
	Sprite* buttonTop4;
	buttonTop4 = Sprite::create("UA/Level/ButtonTop.png");
	buttonTop4->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonTop4->setPosition(1580, 130);
	Sprite* buttonShadowTop4;
	buttonShadowTop4 = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadowTop4->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadowTop4->setPosition(-1580, -130);
	///add to character object
	Character * _buttonShadTop4 = new Character(buttonShadowTop4);
	ButtonTop4 = new Character(buttonTop4, _buttonShadTop4);
	this->addChild(ButtonTop4->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(ButtonTop4->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	ButtonTop4->getSprite()->getPhysicsBody()->setDynamic(false);
	ButtonTop4->getSprite()->getPhysicsBody()->setTag(flag4Tag);

	//Create Button(5)
	buttonBottom5 = Sprite::create("UA/Level/ButtonBottomShadow.png");
	buttonBottom5->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonBottom5->setPosition(190, 790);
	this->addChild(buttonBottom5, 1);

	//Create Button (5) - makes square appear
	Sprite* buttonTop5;
	buttonTop5 = Sprite::create("UA/Level/ButtonTop.png");
	buttonTop5->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonTop5->setPosition(-190, -790);
	Sprite* buttonShadowTop5;
	buttonShadowTop5 = Sprite::create("UA/Level/ButtonTopShadow.png");
	buttonShadowTop5->setAnchorPoint(Vec2(0.5f, 0.5f));
	buttonShadowTop5->setPosition(190, 790);
	///add to character object
	Character * _buttonShadTop5 = new Character(buttonShadowTop5);
	ButtonTop5 = new Character(buttonTop5, _buttonShadTop5);
	this->addChild(ButtonTop5->getSprite(), -51);// z = -49 (way behind player)
	this->addChild(ButtonTop5->getShadow(0)->getSprite(), -51);// z = -50 (way behind player)
	ButtonTop5->getSprite()->getPhysicsBody()->setDynamic(false);
	ButtonTop5->getSprite()->getPhysicsBody()->setTag(flag5Tag);
	//159.755, 807.8
	//1587.81, 147.801

	door = Sprite::create("UA/Level/door2.png");
	door->setAnchorPoint(Vec2(0.5f, 0.5f));
	door->setPosition(3644, 858);
	door->setScale(0.5f, 0.5f);
	this->addChild(door, -50);

	firstDoor = Sprite::create("UA/Level/closedDoor.png");
	firstDoor->setAnchorPoint(Vec2(0.5f, 0.5f));
	firstDoor->setPosition(114, 177);
	firstDoor->setScale(0.5f, 0.5f);
	this->addChild(firstDoor, -48);
}
//Init the static physics world pointer. Set it to be a nullptr which means it points to nothing
PhysicsWorld* LevelFour::physicsWorld = nullptr;
Scene* LevelFour::sceneHandle = nullptr;