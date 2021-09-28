#include "BaseLevel.h"
#include "Transition.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"

USING_NS_CC;
using namespace Input;

Scene* BaseLevel::createScene()//DO NOT USE
{
	//Background Music
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/game_music.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/game_music.mp3", true);
	//Effects
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/jump.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("audio/dash.mp3");
	// 'scene' is an autorelease object
	Scene* scene = Scene::createWithPhysics();
	BaseLevel* layer = BaseLevel::create();
	scene->addChild(layer);
	sceneHandle = scene;
	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	//Get the physics world from the scene so that we can work with it later
	physicsWorld = scene->getPhysicsWorld();
	return scene;
}

void BaseLevel::onExit()
{
	Scene::onExit();

}

void BaseLevel::onEnter()
{
	//DISPLAY->createDebugConsole(true);
	//std::cout << "THE CONSOLE IS NOW OPEN" << std::endl;//uncoment this to remove console window
	
	Scene::onEnter();
}

// on "init" you need to initialize your instance
bool BaseLevel::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//Get the director from cocos so we can use it when needed
	director = Director::getInstance();

	//auto visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//setPosition(director->getWinSizeInPixels().width / 2, director->getWinSizeInPixels().height * 0.1);
	//Initialize Collision Callback
	//initCollisionCallback();
	//Draw objects like background
	//DrawWorld();
	//set screen boundry
	//boundry.setRect(0, 0, 4000, 700);


	//MAKE player
	Sprite * shadow_;
	shadow_ = Sprite::create("UA/Player/character.png");
	shadow_->setPosition(115, 175);
	shadow_->setRotation(0);
	shadow_->setScale(0.7f);
	shadow_->setAnchorPoint(Vec2(0.5f, 0.5f));
	Sprite* player_;
	player_ = Sprite::create("UA/Player/character.png");
	player_->setPosition(140, 150);
	player_->setRotation(0);
	player_->setScale(0.7f);
	player_->setAnchorPoint(Vec2(0.5f, 0.5f));

	//adds componants to CHaracter object
	Character * shadowChar_ = new Character(shadow_);//character for shadow

	shadowChar_->health = 1;

	Player = new Character(player_, shadowChar_);//pass shadow to character for player
	Player->getShadow(0)->getSprite()->runAction((TintTo::create(0.1f, Color3B(0, 0, 0))));

	//Add to scene
	this->addChild(Player->getSprite());
	this->addChild(Player->getShadow(0)->getSprite(), -52);
	this->addChild(Player->healthbar, 1);
	this->addChild(Player->healthframe, 2);
	Player->getShadow(0)->getSprite()->runAction((TintTo::create(0.1f, Color3B(0, 0, 0))));

	//Player->getShadow(0)->health = 1;

	//FADE EFFECT
	mask = Sprite::create("UA/Background/fade.png");
	mask->setPosition(100,100);
	mask->setRotation(0);
	mask->setScale(1.5f);
	mask->setAnchorPoint(Vec2(0.5f, 0.5f));
	mask->setOpacity(1);
	this->addChild(mask,20);

	//INITIALIZE ANIMATIONS

	//walk animation
	Vector<SpriteFrame*> arrayFrame(15);  //Creates an array to store the frames
	auto cache = SpriteFrameCache::getInstance(); //Creates a cache for the sprite sheet
	cache->addSpriteFramesWithFile("UA/Player/Walking Animation.plist"); //Grabs the sprite sheet
	char file[100] = { 0 }; //Not entirely sure what this does, but you need to grab it so you can pushback values for the vector
	for (int i = 0; i <= 14; i++) //Loops however many frames you have in the animation
	{
		sprintf(file, "%d.png", i); //Iterates by %d(+) and grabs whatever the name of the frames in the sprite sheet are
		auto frame = cache->getSpriteFrameByName(file);
		arrayFrame.pushBack(frame); //stores them into an array
	}
	auto animation = Animation::createWithSpriteFrames(arrayFrame, 0.05);
	//^Takes the array and stores it for animation. I believe 0.1 is a modifiable value for frame switch rate. Higher = slower, Lower = faster. 0.1 seems to be a good value
	auto walkAnimate = Animate::create(animation); //Stores an action
	walking = Repeat::create(walkAnimate, 999); //Stores an action
	walking->setTarget(Player->getSprite());
	walking->retain();

	walkingS = Repeat::create(Animate::create(animation), 999);
	walkingS->setTarget(Player->getShadow(0)->getSprite());
	walkingS->retain();

	//Idle Animation
	Vector<SpriteFrame*> arrayFrame1(15); //Creates an array to store the frames
	auto cache1 = SpriteFrameCache::getInstance(); //Creates a cache for the sprite sheet
	cache1->addSpriteFramesWithFile("UA/Player/New Idle Animation.plist"); //Grabs the sprite sheet
	char file1[100] = { 0 }; //Not entirely sure what this does, but you need to grab it so you can pushback values for the vector
	for (int i = 15;i < 30; i++) //Loops however many frames you have in the animation
	{
		sprintf(file1, "%d.png", i); //Iterates by %d(+) and grabs whatever the name of the frames in the sprite sheet are
		auto frame1 = cache1->getSpriteFrameByName(file1);
		arrayFrame1.pushBack(frame1); //stores them into an array
	}
	auto animation1 = Animation::createWithSpriteFrames(arrayFrame1, 0.1);
	//^Takes the array and stores it for animation. I believe 0.1 is a modifiable value for frame switch rate. Higher = slower, Lower = faster. 0.1 seems to be a good value
	auto idleAnimate = Animate::create(animation1); //Stores an action

	idle = Repeat::create(idleAnimate, 999); //Stores an action
	idle->setTarget(Player->getSprite());
	idle->retain();

	idleS = Repeat::create(Animate::create(animation1), 999);
	idleS->setTarget(Player->getShadow(0)->getSprite());
	idleS->retain();

	//Jump Animation
	Vector<SpriteFrame*> arrayFrame2(7); //Creates an array to store the frames
	auto cache2 = SpriteFrameCache::getInstance(); //Creates a cache for the sprite sheet
	cache2->addSpriteFramesWithFile("UA/Player/CharJump.plist"); //Grabs the sprite sheet
	char file2[100] = { 0 }; //Not entirely sure what this does, but you need to grab it so you can pushback values for the vector
	for (int i = 30;i < 37; i++) //Loops however many frames you have in the animation
	{
		sprintf(file2, "%d.png", i); //Iterates by %d(+) and grabs whatever the name of the frames in the sprite sheet are
		auto frame2 = cache2->getSpriteFrameByName(file2);
		arrayFrame2.pushBack(frame2); //stores them into an array
									  //std::cout << "TSM" << std::endl;
	}
	auto animation2 = Animation::createWithSpriteFrames(arrayFrame2, 0.07);
	//^Takes the array and stores it for animation. I believe 0.1 is a modifiable value for frame switch rate. Higher = slower, Lower = faster. 0.1 seems to be a good value
	jumpP = Animate::create(animation2); //Stores an action
	jumpP->setTarget(Player->getSprite());
	jumpP->retain();
	jumpS = Animate::create(animation2);
	jumpS->setTarget(Player->getShadow(0)->getSprite());
	jumpS->retain();

	//Attack Animation
	Vector<SpriteFrame*> arrayFrame4(15);
	auto cache4 = SpriteFrameCache::getInstance();
	cache4->addSpriteFramesWithFile("UA/Player/Attack.plist");
	char file4[100] = { 0 };
	for (int i = 58; i <= 68; i++)
	{
		sprintf(file4, "%d.png", i);
		auto frame4 = cache4->getSpriteFrameByName(file4);
		arrayFrame4.pushBack(frame4);
		std::cout << "CLG" << std::endl;
	}
	auto animation4 = Animation::createWithSpriteFrames(arrayFrame4, 0.05);
	attack = Animate::create(animation4);
	attack->setTarget(Player->getSprite());
	attack->retain();
	attackS = Animate::create(animation4);
	attackS->setTarget(Player->getShadow(0)->getSprite());
	attackS->retain();

	//Enemy Animation

	//Enemy walk animaeshawn
	Vector<SpriteFrame*> arrayFrame3(15);  //Creates an array to store the frames
	auto cache3 = SpriteFrameCache::getInstance(); //Creates a cache for the sprite sheet
	cache3->addSpriteFramesWithFile("UA/Enemies/Enemy Walk Animation.plist"); //Grabs the sprite sheet
	char file3[100] = { 0 }; //Not entirely sure what this does, but you need to grab it so you can pushback values for the vector
	for (int i = 46; i <= 57; i++) //Loops however many frames you have in the animation
	{
		sprintf(file3, "%d.png", i); //Iterates by %d(+) and grabs whatever the name of the frames in the sprite sheet are
		auto frame3 = cache3->getSpriteFrameByName(file3);
		arrayFrame3.pushBack(frame3); //stores them into an array
		std::cout << "TSM" << std::endl;
	}
	auto animation3 = Animation::createWithSpriteFrames(arrayFrame3, 0.1);
	//^Takes the array and stores it for animation. I believe 0.1 is a modifiable value for frame switch rate. Higher = slower, Lower = faster. 0.1 seems to be a good value
	enemWalkS = Animate::create(animation3); //Stores an action
	enemWalkP = Animate::create(animation3); //Stores an action


	//Set Player as idle
	Player->getSprite()->runAction(idle);
	Player->animState = 0;

	Player->getShadow(0)->getSprite()->runAction(idleS);
	Player->getShadow(0)->animState = 0;

	//Creating Overlay
	pauseoverlay = Sprite::create("UA/Background/pause overlay.png");
	pauseoverlay->setAnchorPoint(Vec2(0.5f, 0.5f));
	pauseoverlay->setPosition(650, 325);
	this->addChild(pauseoverlay, 80);
	pauseicon = Sprite::create("UA/Background/pause icon.png");
	pauseicon->setAnchorPoint(Vec2(0.5f, 0.5f));
	pauseicon->setPosition(650, 325);
	this->addChild(pauseicon, 80);
	pauseicon->setScale(0.67f);
	pauseoverlay->setScale(0.67f);

	pauseoverlay->setVisible(false);
	pauseicon->setVisible(false);

	//FADEIN
	black = Sprite::create("UA/Background/black.png");
	black->setAnchorPoint(Vec2(0.5f, 0.5f));
	black->setPosition(Player->getSprite()->getPosition());
	black->setScale(2.9f, 2.9f);
	this->addChild(black, 50);
	black->setOpacity(255);
	black->runAction(FadeOut::create(0.5f));

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();
	//this->getCameras().erase( this->getCameras().end());
	return true;
}

void BaseLevel::updateInputs()
{

	for (int i = 0; i < Enemies.size(); i++) {
		
		if (Enemies.at(i)->health <= 0) {
			for (int j = 0; j < 6; j++) {
				auto dust = Sprite::create("UA/Player/dust.png");
				dust->setPosition(Enemies.at(i)->getPosition() + Vec2(0, 0).rotateByAngle(Vec2(0, 0), j*60.0f));
				dust->setRotation(j*60.0f);
				dust->setScale(0.5f);
				dust->setAnchorPoint(Vec2(0.5f, 0.5f));
				dust->setOpacity(255);
				int layer = -51;
				if (Player->isShadow == true) {
					dust->setColor(Color3B(0, 0, 0));
					layer = -60;
				}
				this->addChild(dust, layer);
				//+ Vec2(j * 5, j * 10)
				dust->runAction(MoveBy::create(0.5f, Vec2(0,60).rotateByAngle(Vec2(0,0),j*60.0f) ));
				dust->runAction(ScaleTo::create(0.5, 2.0f));
				dust->runAction(Sequence::create(FadeOut::create(0.55f), RemoveSelf::create(), NULL));
				dustlist.pushBack(dust);
			}
			//if (Enemies.at(i)->noShadow == false){
				//this->removeChild(Enemies.at(i)->getShadow(0)->getSprite());
				//Enemies[i]->getShadow(0)->getSprite()->runAction(RemoveSelf::create());
			//}
			Enemies[i]->getSprite()->runAction(RemoveSelf::create());
			if (Enemies[i]->noShadow == false) {
				for (int j = 0; j < 6; j++) {
					auto dust = Sprite::create("UA/Player/dust.png");
					dust->setPosition(Enemies.at(i)->getShadow(0)->getSprite()->getPosition() + Vec2(0, 0).rotateByAngle(Vec2(0, 0), j*60.0f));
					dust->setRotation(j*60.0f);
					dust->setScale(0.5f);
					dust->setAnchorPoint(Vec2(0.5f, 0.5f));
					dust->setOpacity(255);
					this->addChild(dust, -60);
					dust->setColor(Color3B(0, 0, 0));
					dust->runAction(MoveBy::create(0.5f, Vec2(0, 60).rotateByAngle(Vec2(0, 0), j*60.0f)));
					dust->runAction(ScaleTo::create(0.5, 2.0f));
					dust->runAction(Sequence::create(FadeOut::create(0.55f), RemoveSelf::create(), NULL));
					dustlist.pushBack(dust);
				}
				Enemies[i]->getShadow(0)->getSprite()->runAction(RemoveSelf::create());
				//*(Enemies[i]->getShadow(0)) = NULL;
			}
			//this->removeChild(Enemies.at(i)->getSprite());
			Enemies[i] = NULL;
			Enemies.erase(Enemies.begin() + i);
			
		}
	}
	//Controler Ready.
	//Keep last frames inputs saved for comparing, to track ButtonPress, and ButtonRelease.
	//if was pressed las frame but not this frame, ButtonRelease() == true
	//if  not pressed last frame, but is pressed this frame, ButtonPress() == true
	Aold = Anew;
	Bold = Bnew;
	Yold = Ynew;
	Xold = Xnew;
	Sold = Snew;
	LBold = LBnew;
	RBold = RBnew;
	LTold = LTnew;
	RTold = RTnew;
	//Update inputs
	XBoxController.DownloadPackets(1);
	if (XBoxController.GetConnected(0)) {
		if (XBoxController.GetButton(0, Input::Start))
			Snew = true;
		else Snew = false;
	}

	if (gamePaused == false) {
		updateKeyboardInputs();
		updateControllerInputs();
	}
	else {
		bool Y = false;
		bool B = false;
		bool select = false;
		if (XBoxController.GetConnected(0)) {
			Y = XBoxController.GetButton(0, Input::Y);
			B = XBoxController.GetButton(0, Input::B);
			select = XBoxController.GetButton(0, Input::Select);
		}
		if (INPUTS->getKeyPress(KeyCode::KEY_ESCAPE) || (Snew == true && Sold == false) || B) {
			director->getRunningScene()->getPhysicsWorld()->setSpeed(gameSpeed);
			gamePaused = false;
			//Overlay
			pauseicon->stopAllActions();
			pauseoverlay->setVisible(false);
			pauseicon->setVisible(false);
		}

		if (INPUTS->getKeyPress(KeyCode::KEY_1) || Y) {
			exit(0);
		}
		else if (INPUTS->getKeyPress(KeyCode::KEY_2) || select) {
			this->stopAllActions();
			this->removeAllComponents();
			cocos2d::CCDirector::sharedDirector()->purgeCachedData();
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			SpriteFrameCache::destroyInstance();
			this->cleanup();
			DISPLAY->init(1000.0f, 500.0f, "Shadow Game (Stalactites)", false);
			Scene* splash = SplashScreen::createScene();
			director->getInstance()->replaceScene(splash);
		}
	}

	fadectr++;
	if (fadectr >= 360) fadectr = 0;
	mask->setPosition(Player->getShadow(0)->getSprite()->getPosition());
	mask->setRotation(fadectr);

}

void BaseLevel::updateControllerInputs()
{
	if (XBoxController.GetConnected(0)) {
		//Allow Release and Press
		if (XBoxController.GetButton(0, Input::A)) {
			Anew = true;
			pad = true;
		}
		else Anew = false;
		if (XBoxController.GetButton(0, Input::B)) {
			Bnew = true;
			pad = true;
		}
		else Bnew = false;
		if (XBoxController.GetButton(0, Input::Y)) {
			Ynew = true;
			pad = true;
		}
		else Ynew = false;
		if (XBoxController.GetButton(0, Input::X)) {
			Xnew = true;
			pad = true;
		}
		else Xnew = false;
		if (XBoxController.GetButton(0, Input::RB)) {
			RBnew = true;
			pad = true;
		}
		else RBnew = false;
		if (XBoxController.GetButton(0, Input::LB)) {
			LBnew = true;
			pad = true;
		}
		else LBnew = false;

		XBoxController.GetTriggers(0, lTrig, rTrig);
		if (rTrig > 0.5) {
			RTnew = true;
			pad = true;
		}
		else RTnew = false;
		if (lTrig > 0.5) {
			LTnew = true;
			pad = true;
		}
		else LTnew = false;


		//Pause
		if (Sold == false && Snew == true) {

			if (gamePaused == false) {
				gameSpeed = director->getRunningScene()->getPhysicsWorld()->getSpeed();
				director->getRunningScene()->getPhysicsWorld()->setSpeed(0);
				gamePaused = true;

				//Overlay
				pauseoverlay->setPosition(Vec2(Player->getPosition().x, Player->getPosition().y + 100));
				if ((Player->getPosition().x) > (boundry.getMaxX() - 650))
					pauseoverlay->setPositionX(boundry.getMaxX() - 650);
				else if ((Player->getPosition().x) < 650)
					pauseoverlay->setPositionX(650);
				if ((Player->getPosition().y) > (boundry.getMaxY() - 325))
					pauseoverlay->setPositionY(boundry.getMaxY() - 325);
				else if ((Player->getPosition().y) < 325)
					pauseoverlay->setPositionY(325);

				pauseicon->setPosition(pauseoverlay->getPosition());
				pauseoverlay->setVisible(true);
				pauseicon->setVisible(true);
				pauseicon->runAction(Repeat::create(Blink::create(100.0f, 100), 9999));

			}
		}

		//Attack
		if (Xnew == true && Xold == false && grounded == true) {
			Player->attack(this);

			//Animations
			if (Player->animState != 4)
			{
				if (Player->animState == 0)
				{
					Player->getSprite()->stopAction(idle);
				}
				else if (Player->animState == 1)
				{
					Player->getSprite()->stopAction(walking);
				}
				else if (Player->animState == 2)
				{
					Player->getSprite()->stopAction(jumpP);
				}
				Player->getSprite()->runAction(attack);
				Player->animState = 4;
			}
			if (Player->getShadow(0)->animState != 4 && Player->isShadow == true)
			{
				if (Player->getShadow(0)->animState == 0)
				{
					Player->getShadow(0)->getSprite()->stopAction(idleS);
				}
				else if (Player->getShadow(0)->animState == 1)
				{
					Player->getShadow(0)->getSprite()->stopAction(walkingS);
				}
				else if (Player->getShadow(0)->animState == 2)
				{
					Player->getShadow(0)->getSprite()->stopAction(jumpS);
				}

				Player->getShadow(0)->getSprite()->runAction(attackS);
				Player->getShadow(0)->animState = 4;

			}
		}

		//JUMP input
		if (Anew == true && Aold == false) {
			//jump stillframe
			if (Player->isShadow == false) {
				if (Player->animState != 2 && (onWall || grounded)) {
					if (Player->animState == 0) {
						Player->getSprite()->stopAction(idle);
					}
					else if (Player->animState == 1) {
						Player->getSprite()->stopAction(walking);
					}
					else if (Player->animState == 4)
					{
						Player->getSprite()->stopAction(attack);
					}
					//Player->getSprite()->setTexture("UA/Player/character.png");
					Player->getSprite()->runAction(jumpP);
					Player->animState = 2;
				}
			}
			if (Player->getShadow(0)->animState != 2 && (onWall || grounded)) {
				if (Player->getShadow(0)->animState == 0) {
					Player->getShadow(0)->getSprite()->stopAction(idleS);
				}
				else if (Player->getShadow(0)->animState == 1) {
					Player->getShadow(0)->getSprite()->stopAction(walkingS);
				}
				else if (Player->getShadow(0)->animState == 4)
				{
					Player->getShadow(0)->getSprite()->stopAction(attackS);
				}
				//Player->getShadow(0)->getSprite()->setTexture("UA/Player/character.png");
				Player->getShadow(0)->getSprite()->runAction(jumpS);
				Player->getShadow(0)->animState = 2;
			}

			if (onWall == true) {//if was walljump
				falling = false;
				onWall = false;
			}
			if (falling == false) {//if was grounded jump
				grounded = false;//set no grounded)
			}

			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/jump.mp3");
		}
		if (Anew == true && falling == false) {//if key held and not falling
			if (Player->isShadow == false) {//if no shadow
				Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 250));//add force
																																	  //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/jump.mp3");
			}
			else if (Player->isShadow == true) {//if shadow
				Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 250));//add force
																																								  //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/jump.mp3");
			}
			//grounded = false;//set no grounded
			jump++;//incement counter
		}
		if (Anew == false && Aold == true)//when u let go
		{
			falling = true;//cant jump until touching the ground
			jump = 0;//reset counter
			if (grounded == true) {//if u touch the ground, allow jump again
				falling = false;
				jump = 0;
			}
		}
		else if (jump >= 20.0f) {//if counter more than 20, stop jumping (fall)
			if (grounded == false) falling = true;
		}

		//DASH input
		if (Bnew == true && candash == true)//if key held, able to dash, and not standing still
		{
			//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/dash.mp3");
			if (dash < 10) {//if frames of dash left
				if (Player->isShadow == false) {//if not shadow
					if (Player->getSprite()->isFlippedX() == true && Player->getSprite()->getPhysicsBody()->getVelocity().x < -1)
						Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(-800, -1));//dash
					else if (Player->getSprite()->isFlippedX() == false && Player->getSprite()->getPhysicsBody()->getVelocity().x > 1)
						Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(800, -1));//dash
					dash++;//incement counter

						   //DashTrail

					if (blurctr >= 3) {
						auto blur = Sprite::create("UA/Player/character.png");
						blur->setPosition(Player->getPosition());
						blur->setRotation(0);
						blur->setScale(0.7f);
						blur->setAnchorPoint(Vec2(0.5f, 0.5f));
						blur->setOpacity(120);
						if (Player->getSprite()->isFlippedX() == true)
							blur->setFlippedX(true);
						this->addChild(blur, -10);
						blur->runAction(TintTo::create(0.001f, Color3B(100, 100, 250)));
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
				else if (Player->isShadow == true) {//if shadow
					if (Player->getShadow(0)->getSprite()->isFlippedX() == true && Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x < -1)
						Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(-800, -1));//shadow dash
					else if (Player->getShadow(0)->getSprite()->isFlippedX() == false && Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x > 1)
						Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(800, -1));//shadow dash
					dash++;//incement counter

						   //Shadow DashTrail
					if (blurctr >= 3) {
						auto blur = Sprite::create("UA/Player/character.png");
						blur->setPosition(Player->getPosition());
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
		}
		if (Bnew == false && Bold == true)//if u let go
		{
			if (dash < 10) //if more dash frames left
				dash = 10;//set so none are
			candash = false;//either way, no dashing until cooldown is set
		}
		else if (dash >= 40.0f && pad == true) {//else if been 50frames since last intal dash frame
			candash = true;//can dash again
			dash = 0;//reset counter
		}
		else if (dash >= 10.0f && pad == true) {//else if not 50 frames yet
			candash = false;//cant dash
			dash++;//keep adding
		}
		///Can only dash again exactly 50 frames after the inital dash frame of last dash. counter will count to 50 then reset to 0 so you can dash again.

		Input::Stick lStick, rStick;
		XBoxController.GetSticks(0, lStick, rStick);
		if ((lStick.xAxis <= -0.7 || lStick.xAxis >= 0.7))
			pad = true;

		//Dust Shit
		if ((grounded || onWall) && (lStick.xAxis <= -0.7 || lStick.xAxis >= 0.7)) {//if key held
			if (dustctr >= 5) {
				auto dust = Sprite::create("UA/Player/dust.png");
				if (onWall == true) {
					if (right == true) {
						dust->setPosition(Player->getPosition() + Vec2(-15, -20));
					}
					else {
						dust->setPosition(Player->getPosition() + Vec2(15, -20));
					}
					dust->setRotation(90);
					dust->setScale(0.1f);
				}
				else {
					dust->setPosition(Player->getPosition() + Vec2(-2, -30));
					dust->setRotation(0);
					dust->setScale(0.2f);
				}
				dust->setAnchorPoint(Vec2(0.5f, 0.5f));
				dust->setOpacity(255);
				int layer = -50;
				if (Player->isShadow == true) {
					dust->setColor(Color3B(0, 0, 0));
					layer = -60;
				}
				this->addChild(dust, layer);
				dust->runAction(ScaleTo::create(0.3, 1.0f));
				dust->runAction(Sequence::create(FadeOut::create(0.35f), RemoveSelf::create(), NULL));
				dustlist.pushBack(dust);
				dustctr = 0;
			}
			dustctr++;
			for (int i = 0; i < dustlist.size(); i++) {
				if (dustlist.at(i)->getOpacity() == 0) {
					dustlist.erase(dustlist.begin() + i);
				}
			}
		}

		//Moveing LEFT
		if (lStick.xAxis <= -0.7)//if key held
		{
			if (Player->animState != 1 && grounded == true) {
				if (Player->isShadow == false && onWall == false) {
					if (Player->animState == 0) {
						Player->getSprite()->stopAction(idle);
					}
					else if (Player->animState == 2) {
						Player->getSprite()->stopAction(jumpP);
					}
					else if (Player->animState == 4)
					{
						Player->getSprite()->stopAction(attack);
					}
					Player->getSprite()->runAction(walking);
					Player->animState = 1;
				}
			}
			if (Player->getShadow(0)->animState != 1 && grounded == true) {
				if (Player->isShadow == false && onWall == false) {
					if (Player->getShadow(0)->animState == 0) {
						Player->getShadow(0)->getSprite()->stopAction(idleS);
					}
					else if (Player->getShadow(0)->animState == 2) {
						Player->getShadow(0)->getSprite()->stopAction(jumpS);
					}
					else if (Player->getShadow(0)->animState == 4)
					{
						Player->getShadow(0)->getSprite()->stopAction(attackS);
					}
					Player->getShadow(0)->getSprite()->runAction(walkingS);
					Player->getShadow(0)->animState = 1;
				}
				if (Player->isShadow == true && onWall == false) {
					if (Player->getShadow(0)->animState == 0) {
						Player->getShadow(0)->getSprite()->stopAction(idleS);
					}
					else if (Player->getShadow(0)->animState == 2) {
						Player->getShadow(0)->getSprite()->stopAction(jumpS);
					}
					else if (Player->getShadow(0)->animState == 4)
					{
						Player->getShadow(0)->getSprite()->stopAction(attackS);
					}
					Player->getShadow(0)->getSprite()->runAction(walkingS);
					Player->getShadow(0)->animState = 1;
				}
			}

		}
		if (lStick.xAxis <= -0.7)//if key held
		{

			if (Player->isShadow == false) {//if not shadow
				if (Player->getSprite()->getPhysicsBody()->getVelocity().x > 0)//if was moving in other direction, 
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x *0.9, Player->getSprite()->getPhysicsBody()->getVelocity().y));//90% velocity in that direction

				Player->getSprite()->getPhysicsBody()->applyImpulse(Vec2(-20, 0));//move
				Player->getSprite()->setFlippedX(true);//face left
				Player->getShadow(0)->getSprite()->setFlippedX(true);//shadow face left
			}
			else if (Player->isShadow == true) {//if shadow
				if (Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x > 0)//if was moving in other direction, 
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x *0.9, Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));//90% velocity in that direction

				Player->getShadow(0)->getSprite()->getPhysicsBody()->applyImpulse(Vec2(-20, 0));//move shadow
				Player->getShadow(0)->getSprite()->setFlippedX(true);//shadow face left
			}
		}
		//Move RIGHT
		if (lStick.xAxis >= 0.7)//if key held
		{
			if (Player->animState != 1 && grounded == true) {
				if (Player->isShadow == false && onWall == false) {
					if (Player->animState == 0) {
						Player->getSprite()->stopAction(idle);
					}
					else if (Player->animState == 2)
					{
						Player->getSprite()->stopAction(jumpP);
					}
					else if (Player->animState == 4)
					{
						Player->getSprite()->stopAction(attack);
					}
					Player->getSprite()->runAction(walking);
					Player->animState = 1;
				}
			}
			if (Player->getShadow(0)->animState != 1 && grounded == true) {
				if (Player->isShadow == false && onWall == false) {
					if (Player->getShadow(0)->animState == 0) {
						Player->getShadow(0)->getSprite()->stopAction(idleS);
					}
					else if (Player->getShadow(0)->animState == 2)
					{
						Player->getShadow(0)->getSprite()->stopAction(jumpS);
					}
					else if (Player->getShadow(0)->animState == 4)
					{
						Player->getShadow(0)->getSprite()->stopAction(attackS);
					}
					Player->getShadow(0)->getSprite()->runAction(walkingS);
					Player->getShadow(0)->animState = 1;
				}
				if (Player->isShadow == true && onWall == false) {
					if (Player->getShadow(0)->animState == 0) {
						Player->getShadow(0)->getSprite()->stopAction(idleS);
					}
					else if (Player->getShadow(0)->animState == 2)
					{
						Player->getShadow(0)->getSprite()->stopAction(jumpS);
					}
					else if (Player->getShadow(0)->animState == 4)
					{
						Player->getShadow(0)->getSprite()->stopAction(attackS);
					}
					Player->getShadow(0)->getSprite()->runAction(walkingS);
					Player->getShadow(0)->animState = 1;
				}
			}
		}
		if (lStick.xAxis >= 0.7)//if key held
		{

			if (Player->isShadow == false) {//if not shadow
				if (Player->getSprite()->getPhysicsBody()->getVelocity().x < 0)//if was moving in other direction, 
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x *0.9, Player->getSprite()->getPhysicsBody()->getVelocity().y));//90% velocity in that direction

				Player->getSprite()->getPhysicsBody()->applyImpulse(Vec2(20, 0));//move
				Player->getSprite()->setFlippedX(false);//face right
				Player->getShadow(0)->getSprite()->setFlippedX(false);//shadow face right
			}
			else if (Player->isShadow == true) {//if shadow
				if (Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x < 0)//if was moving in other direction, 
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x *0.9, Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));//90% velocity in that direction

				Player->getShadow(0)->getSprite()->getPhysicsBody()->applyImpulse(Vec2(20, 0));//shadow move
				Player->getShadow(0)->getSprite()->setFlippedX(false);//shadow face right
			}
		}
		//friction
		if ((lStick.xAxis < 0.7) && (lStick.xAxis > -0.7) && pad == true) {//if no key pressed apply friction
			if (Player->isShadow == false) {
				Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x * 0.9, Player->getSprite()->getPhysicsBody()->getVelocity().y));
				//back to idle
				if (Player->animState != 0 && grounded == true && onWall == false && (Player->animState != 4 || (Player->animState == 4 && attack->isDone() == true))) {
					if (Player->animState == 1) {
						Player->getSprite()->stopAction(walking);
					}
					else if (Player->animState == 2)
					{
						Player->getSprite()->stopAction(jumpP);
					}
					else if (Player->animState == 4)
					{
						Player->getSprite()->stopAction(attack);
					}
					Player->getSprite()->runAction(idle);
					Player->animState = 0;
				}
				if (Player->getShadow(0)->animState != 0 && grounded == true && onWall == false && (Player->getShadow(0)->animState != 4 || (Player->getShadow(0)->animState == 4 && attackS->isDone() == true))) {
					if (Player->getShadow(0)->animState == 1) {
						Player->getShadow(0)->getSprite()->stopAction(walkingS);
					}
					else if (Player->getShadow(0)->animState == 2)
					{
						Player->getShadow(0)->getSprite()->stopAction(jumpS);
					}
					else if (Player->getShadow(0)->animState == 4)
					{
						Player->getShadow(0)->getSprite()->stopAction(attackS);
					}
					Player->getShadow(0)->getSprite()->runAction(idleS);
					Player->getShadow(0)->animState = 0;
				}
			}
			else {
				Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x * 0.9, Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));
				//back to idle
				if (Player->getShadow(0)->animState != 0 && grounded == true && onWall == false && (Player->getShadow(0)->animState != 4 || (Player->getShadow(0)->animState == 4 && attackS->isDone() == true))) {
					if (Player->getShadow(0)->animState == 1) {
						Player->getShadow(0)->getSprite()->stopAction(walkingS);
					}
					else if (Player->getShadow(0)->animState == 2) {
						Player->getShadow(0)->getSprite()->stopAction(jumpS);
					}
					else if (Player->getShadow(0)->animState == 4) {
						Player->getShadow(0)->getSprite()->stopAction(attackS);
					}
					Player->getShadow(0)->getSprite()->runAction(idleS);
					Player->getShadow(0)->animState = 0;
				}
			}

		}

		//SHADOW button
		if (Ynew == true && Yold == false && grounded == true)
		{
			FlipWorld();
		}
	}
}

void BaseLevel::updateKeyboardInputs()
{
	//Pause
	if (INPUTS->getKeyPress(KeyCode::KEY_ESCAPE)) {
		
		if(gamePaused == false) {
			gameSpeed = director->getRunningScene()->getPhysicsWorld()->getSpeed();
			director->getRunningScene()->getPhysicsWorld()->setSpeed(0);
			gamePaused = true;

			//Overlay
			pauseoverlay->setPosition(Vec2(Player->getPosition().x, Player->getPosition().y + 100));
			if ((Player->getPosition().x) > (boundry.getMaxX() - 650))
				pauseoverlay->setPositionX(boundry.getMaxX() - 650);
			else if ((Player->getPosition().x) < 650)
				pauseoverlay->setPositionX(650);
			if ((Player->getPosition().y) > (boundry.getMaxY() - 325))
				pauseoverlay->setPositionY(boundry.getMaxY() - 325);
			else if ((Player->getPosition().y) < 325)
				pauseoverlay->setPositionY(325);

			pauseicon->setPosition(pauseoverlay->getPosition());
			pauseoverlay->setVisible(true);
			pauseicon->setVisible(true);
			pauseicon->runAction(Repeat::create(Blink::create(100.0f, 100), 9999));

		}
	}


	if (INPUTS->getAnyButton() == true) {
		pad = false;
	}

	//Attack
	if (INPUTS->getKeyPress(KeyCode::KEY_E) && grounded == true) {
		Player->attack(this);

		//Animations
		if (Player->animState != 4)
		{
			if (Player->animState == 0)
			{
				Player->getSprite()->stopAction(idle);
			}
			else if (Player->animState == 1)
			{
				Player->getSprite()->stopAction(walking);
			}
			else if (Player->animState == 2)
			{
				Player->getSprite()->stopAction(jumpP);
			}
			Player->getSprite()->runAction(attack);
			Player->animState = 4;
		}
		if (Player->getShadow(0)->animState != 4 && Player->isShadow == true)
		{
			if (Player->getShadow(0)->animState == 0)
			{
				Player->getShadow(0)->getSprite()->stopAction(idleS);
			}
			else if (Player->getShadow(0)->animState == 1)
			{
				Player->getShadow(0)->getSprite()->stopAction(walkingS);
			}
			else if (Player->getShadow(0)->animState == 2)
			{
				Player->getShadow(0)->getSprite()->stopAction(jumpS);
			}

			Player->getShadow(0)->getSprite()->runAction(attackS);
			Player->getShadow(0)->animState = 4;

		}
	}

	//JUMP input
	if (INPUTS->getKeyPress(KeyCode::KEY_SPACE)) {
		//jump stillframe
		if (Player->isShadow == false) {
			if (Player->animState != 2 && (onWall || grounded)) {
				if (Player->animState == 0) {
					Player->getSprite()->stopAction(idle);
				}
				else if (Player->animState == 1) {
					Player->getSprite()->stopAction(walking);
				}
				else if (Player->animState == 4)
				{
					Player->getSprite()->stopAction(attack);
				}
				//Player->getSprite()->setTexture("UA/Player/character.png");
				Player->getSprite()->runAction(jumpP);
				Player->animState = 2;
			}
		}
		if (Player->getShadow(0)->animState != 2 && (onWall || grounded)) {
			if (Player->getShadow(0)->animState == 0) {
				Player->getShadow(0)->getSprite()->stopAction(idleS);
			}
			else if (Player->getShadow(0)->animState == 1) {
				Player->getShadow(0)->getSprite()->stopAction(walkingS);
			}
			else if (Player->getShadow(0)->animState == 4)
			{
				Player->getShadow(0)->getSprite()->stopAction(attackS);
			}
			//Player->getShadow(0)->getSprite()->setTexture("UA/Player/character.png");
			Player->getShadow(0)->getSprite()->runAction(jumpS);
			Player->getShadow(0)->animState = 2;
		}

		if (onWall == true) {//if was walljump
			falling = false;
			onWall = false;
		}
		if (falling == false) {//if was grounded jump
			grounded = false;//set no grounded)
		}

		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/jump.mp3");
	}
	if (INPUTS->getKey(KeyCode::KEY_SPACE) && falling == false) {//if key held and not falling
		if (Player->isShadow == false) {//if no shadow
			Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 250));//add force
																																  //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/jump.mp3");
		}
		else if (Player->isShadow == true) {//if shadow
			Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 250));//add force
																																							  //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/jump.mp3");
		}
		//grounded = false;//set no grounded
		jump++;//incement counter
	}
	if (INPUTS->getKeyRelease(KeyCode::KEY_SPACE))//when u let go
	{
		falling = true;//cant jump until touching the ground
		jump = 0;//reset counter
		if (grounded == true) {//if u touch the ground, allow jump again
			falling = false;
			jump = 0;
		}
	}
	else if (jump >= 20.0f) {//if counter more than 20, stop jumping (fall)
		if (grounded == false) falling = true;
	}

	//DASH input
	if (INPUTS->getKey(KeyCode::KEY_W) && candash == true)//if key held, able to dash, and not standing still
	{
		//CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/dash.mp3");
		if (dash < 10) {//if frames of dash left
			if (Player->isShadow == false) {//if not shadow
				if (Player->getSprite()->isFlippedX() == true && Player->getSprite()->getPhysicsBody()->getVelocity().x < -1)
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(-800, -1));//dash
				else if (Player->getSprite()->isFlippedX() == false && Player->getSprite()->getPhysicsBody()->getVelocity().x > 1)
					Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(800, -1));//dash
				dash++;//incement counter

					   //DashTrail

				if (blurctr >= 3) {
					auto blur = Sprite::create("UA/Player/character.png");
					blur->setPosition(Player->getPosition());
					blur->setRotation(0);
					blur->setScale(0.7f);
					blur->setAnchorPoint(Vec2(0.5f, 0.5f));
					blur->setOpacity(120);
					if (Player->getSprite()->isFlippedX() == true)
						blur->setFlippedX(true);
					this->addChild(blur, -10);
					blur->runAction(TintTo::create(0.001f, Color3B(100, 100, 250)));
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
			else if (Player->isShadow == true) {//if shadow
				if (Player->getShadow(0)->getSprite()->isFlippedX() == true && Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x < -1)
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(-800, -1));//shadow dash
				else if (Player->getShadow(0)->getSprite()->isFlippedX() == false && Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x > 1)
					Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(800, -1));//shadow dash
				dash++;//incement counter

					   //Shadow DashTrail
				if (blurctr >= 3) {
					auto blur = Sprite::create("UA/Player/character.png");
					blur->setPosition(Player->getPosition());
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
	}
	if (INPUTS->getKeyRelease(KeyCode::KEY_W))//if u let go
	{
		if (dash < 10) //if more dash frames left
			dash = 10;//set so none are
		candash = false;//either way, no dashing until cooldown is set
	}
	else if (dash >= 40.0f && pad == false) {//else if been 50frames since last intal dash frame
		candash = true;//can dash again
		dash = 0;//reset counter
	}
	else if (dash >= 10.0f && pad == false) {//else if not 50 frames yet
		candash = false;//cant dash
		dash++;//keep adding
	}
	///Can only dash again exactly 50 frames after the inital dash frame of last dash. counter will count to 50 then reset to 0 so you can dash again.

	//Dust Shit
	if ((grounded || onWall) && (INPUTS->getKey(KeyCode::KEY_RIGHT_ARROW) || INPUTS->getKey(KeyCode::KEY_LEFT_ARROW))) {//if key held
		if (dustctr >= 5) {
			auto dust = Sprite::create("UA/Player/dust.png");
			if (onWall == true) {
				if (right == true) {
					dust->setPosition(Player->getPosition() + Vec2(-15, -20));
				}
				else {
					dust->setPosition(Player->getPosition() + Vec2(15, -20));
				}
				dust->setRotation(90);
				dust->setScale(0.1f);
			}
			else {
				dust->setPosition(Player->getPosition() + Vec2(-2, -30));
				dust->setRotation(0);
				dust->setScale(0.2f);
			}
			dust->setAnchorPoint(Vec2(0.5f, 0.5f));
			dust->setOpacity(255);
			int layer = -50;
			if (Player->isShadow == true) {
				dust->setColor(Color3B(0, 0, 0));
				layer = -60;
			}
			this->addChild(dust, layer);
			dust->runAction(ScaleTo::create(0.3, 1.0f));
			dust->runAction(Sequence::create(FadeOut::create(0.35f), RemoveSelf::create(), NULL));
			dustlist.pushBack(dust);
			dustctr = 0;
		}
		dustctr++;
		for (int i = 0; i < dustlist.size(); i++) {
			if (dustlist.at(i)->getOpacity() == 0) {
				dustlist.erase(dustlist.begin() + i);
			}
		}
	}

	//Moveing LEFT
	if (INPUTS->getKey(KeyCode::KEY_LEFT_ARROW))//if key held
	{
		if (Player->animState != 1 && grounded == true) {
			if (Player->isShadow == false && onWall == false) {
				if (Player->animState == 0) {
					Player->getSprite()->stopAction(idle);
				}
				else if (Player->animState == 2) {
					Player->getSprite()->stopAction(jumpP);
				}
				else if (Player->animState == 4)
				{
					Player->getSprite()->stopAction(attack);
				}
				Player->getSprite()->runAction(walking);
				Player->animState = 1;
			}
		}
		if (Player->getShadow(0)->animState != 1 && grounded == true) {
			if (Player->isShadow == false && onWall == false) {
				if (Player->getShadow(0)->animState == 0) {
					Player->getShadow(0)->getSprite()->stopAction(idleS);
				}
				else if (Player->getShadow(0)->animState == 2) {
					Player->getShadow(0)->getSprite()->stopAction(jumpS);
				}
				else if (Player->getShadow(0)->animState == 4)
				{
					Player->getShadow(0)->getSprite()->stopAction(attackS);
				}
				Player->getShadow(0)->getSprite()->runAction(walkingS);
				Player->getShadow(0)->animState = 1;
			}
			if (Player->isShadow == true && onWall == false) {
				if (Player->getShadow(0)->animState == 0) {
					Player->getShadow(0)->getSprite()->stopAction(idleS);
				}
				else if (Player->getShadow(0)->animState == 2) {
					Player->getShadow(0)->getSprite()->stopAction(jumpS);
				}
				else if (Player->getShadow(0)->animState == 4)
				{
					Player->getShadow(0)->getSprite()->stopAction(attackS);
				}
				Player->getShadow(0)->getSprite()->runAction(walkingS);
				Player->getShadow(0)->animState = 1;
			}
		}

	}
	if (INPUTS->getKey(KeyCode::KEY_LEFT_ARROW))//if key held
	{

		if (Player->isShadow == false) {//if not shadow
			if (Player->getSprite()->getPhysicsBody()->getVelocity().x > 0)//if was moving in other direction, 
				Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x *0.9, Player->getSprite()->getPhysicsBody()->getVelocity().y));//90% velocity in that direction

			Player->getSprite()->getPhysicsBody()->applyImpulse(Vec2(-20, 0));//move
			Player->getSprite()->setFlippedX(true);//face left
			Player->getShadow(0)->getSprite()->setFlippedX(true);//shadow face left
		}
		else if (Player->isShadow == true) {//if shadow
			if (Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x > 0)//if was moving in other direction, 
				Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x *0.9, Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));//90% velocity in that direction

			Player->getShadow(0)->getSprite()->getPhysicsBody()->applyImpulse(Vec2(-20, 0));//move shadow
			Player->getShadow(0)->getSprite()->setFlippedX(true);//shadow face left
		}
	}
	//Move RIGHT
	if (INPUTS->getKey(KeyCode::KEY_RIGHT_ARROW))//if key held
	{
		if (Player->animState != 1 && grounded == true) {
			if (Player->isShadow == false && onWall == false) {
				if (Player->animState == 0) {
					Player->getSprite()->stopAction(idle);
				}
				else if (Player->animState == 2)
				{
					Player->getSprite()->stopAction(jumpP);
				}
				else if (Player->animState == 4)
				{
					Player->getSprite()->stopAction(attack);
				}
				Player->getSprite()->runAction(walking);
				Player->animState = 1;
			}
		}
		if (Player->getShadow(0)->animState != 1 && grounded == true) {
			if (Player->isShadow == false && onWall == false) {
				if (Player->getShadow(0)->animState == 0) {
					Player->getShadow(0)->getSprite()->stopAction(idleS);
				}
				else if (Player->getShadow(0)->animState == 2)
				{
					Player->getShadow(0)->getSprite()->stopAction(jumpS);
				}
				else if (Player->getShadow(0)->animState == 4)
				{
					Player->getShadow(0)->getSprite()->stopAction(attackS);
				}
				Player->getShadow(0)->getSprite()->runAction(walkingS);
				Player->getShadow(0)->animState = 1;
			}
			if (Player->isShadow == true && onWall == false) {
				if (Player->getShadow(0)->animState == 0) {
					Player->getShadow(0)->getSprite()->stopAction(idleS);
				}
				else if (Player->getShadow(0)->animState == 2)
				{
					Player->getShadow(0)->getSprite()->stopAction(jumpS);
				}
				else if (Player->getShadow(0)->animState == 4)
				{
					Player->getShadow(0)->getSprite()->stopAction(attackS);
				}
				Player->getShadow(0)->getSprite()->runAction(walkingS);
				Player->getShadow(0)->animState = 1;
			}
		}
	}
	if (INPUTS->getKey(KeyCode::KEY_RIGHT_ARROW))//if key held
	{

		if (Player->isShadow == false) {//if not shadow
			if (Player->getSprite()->getPhysicsBody()->getVelocity().x < 0)//if was moving in other direction, 
				Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x *0.9, Player->getSprite()->getPhysicsBody()->getVelocity().y));//90% velocity in that direction

			Player->getSprite()->getPhysicsBody()->applyImpulse(Vec2(20, 0));//move
			Player->getSprite()->setFlippedX(false);//face right
			Player->getShadow(0)->getSprite()->setFlippedX(false);//shadow face right
		}
		else if (Player->isShadow == true) {//if shadow
			if (Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x < 0)//if was moving in other direction, 
				Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x *0.9, Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));//90% velocity in that direction

			Player->getShadow(0)->getSprite()->getPhysicsBody()->applyImpulse(Vec2(20, 0));//shadow move
			Player->getShadow(0)->getSprite()->setFlippedX(false);//shadow face right
		}
	}
	//friction
	if (!(INPUTS->getKey(KeyCode::KEY_RIGHT_ARROW)) && !(INPUTS->getKey(KeyCode::KEY_LEFT_ARROW)) && pad == false) {//if no key pressed apply friction
		if (Player->isShadow == false) {
			Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x * 0.9, Player->getSprite()->getPhysicsBody()->getVelocity().y));
			//back to idle
			if (Player->animState != 0 && grounded == true && onWall == false && (Player->animState != 4 || (Player->animState == 4 && attack->isDone() == true))) {
				if (Player->animState == 1) {
					Player->getSprite()->stopAction(walking);
				}
				else if (Player->animState == 2)
				{
					Player->getSprite()->stopAction(jumpP);
				}
				else if (Player->animState == 4)
				{
					Player->getSprite()->stopAction(attack);
				}
				Player->getSprite()->runAction(idle);
				Player->animState = 0;
			}
			if (Player->getShadow(0)->animState != 0 && grounded == true && onWall == false && (Player->getShadow(0)->animState != 4 || (Player->getShadow(0)->animState == 4 && attackS->isDone() == true))) {
				if (Player->getShadow(0)->animState == 1) {
					Player->getShadow(0)->getSprite()->stopAction(walkingS);
				}
				else if (Player->getShadow(0)->animState == 2)
				{
					Player->getShadow(0)->getSprite()->stopAction(jumpS);
				}
				else if (Player->getShadow(0)->animState == 4)
				{
					Player->getShadow(0)->getSprite()->stopAction(attackS);
				}
				Player->getShadow(0)->getSprite()->runAction(idleS);
				Player->getShadow(0)->animState = 0;
			}
		}
		else {
			Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x * 0.9, Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().y));
			//back to idle
			if (Player->getShadow(0)->animState != 0 && grounded == true && onWall == false && (Player->getShadow(0)->animState != 4 || (Player->getShadow(0)->animState == 4 && attackS->isDone() == true))) {
				if (Player->getShadow(0)->animState == 1) {
					Player->getShadow(0)->getSprite()->stopAction(walkingS);
				}
				else if (Player->getShadow(0)->animState == 2) {
					Player->getShadow(0)->getSprite()->stopAction(jumpS);
				}
				else if (Player->getShadow(0)->animState == 4) {
					Player->getShadow(0)->getSprite()->stopAction(attackS);
				}
				Player->getShadow(0)->getSprite()->runAction(idleS);
				Player->getShadow(0)->animState = 0;
			}
		}

	}

	//debug reset jump
	if (INPUTS->getKeyPress(KeyCode::KEY_Z))
	{
		falling = false;
		jump = 0;
	}

	//debug reset jump
	if (INPUTS->getKeyPress(KeyCode::KEY_X))
	{
		if (Player->isShadow == false)
			std::cout << Player->getSprite()->getPosition().x << ", " << Player->getSprite()->getPosition().y << std::endl;
		else
			std::cout << Player->getShadow(0)->getSprite()->getPosition().x << ", " << Player->getShadow(0)->getSprite()->getPosition().y << std::endl;
	}


	//SHADOW button
	if (INPUTS->getKeyPress(KeyCode::KEY_Q) && grounded == true)
	{
		FlipWorld();
	}

	////Zoom Buttons
	//if (INPUTS->getKeyPress(KeyCode::KEY_O)) {
	//	zoom = zoom + 0.1;
	//	//this->runAction(ScaleTo::create(0.1f, zoom));
	//	this->getCameras()[0]->setScale(0.9f);
	//	std::cout << "zoom in" << std::endl;
	//}
	//if (INPUTS->getKeyPress(KeyCode::KEY_P)) {
	//	zoom = zoom - 0.1;
	//	//this->runAction(ScaleTo::create(0.1f, zoom));
	//	
	//	std::cout << "zoom out" << std::endl;
	//}
}


void BaseLevel::initCollisionCallback()
{
	//Create the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	//Assign the callback function
	contactListener->onContactBegin = CC_CALLBACK_1(BaseLevel::onContactBeginCallback, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(BaseLevel::onSepBeginCallback, this);
	//Add the contact listener to the event dispatcher
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool BaseLevel::onContactBeginCallback(PhysicsContact& contact)
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
		//ENEMY COLLISIONS
		if (tagA == enemyCollisionTag)
		{
			if (tagB == attackTag) {
				for (int i = 0; i < Enemies.size(); i++) {
					if (Player->isShadow == false) {
						if (Enemies.at(i)->getSprite()->getPhysicsBody()->getShape(0)->getBody()->getNode() == nodeA) {
							Enemies.at(i)->getHit(Player->getPosition().x);
							return true;
						}
					}
					else {
						if (Enemies.at(i)->getShadow(0)->getSprite()->getPhysicsBody()->getShape(0)->getBody()->getNode() == nodeA) {
							Enemies.at(i)->getShadow(0)->getHit(Player->getPosition().x);
							return true;
						}
					}
				}
				return false;

			}
			if (tagB == playerCollisionTag) {
				if (Player->isShadow == true) {
					Player->getShadow(0)->health = 0;
				}
				else {
					Player->getHit(nodeA->getPosition().x);

				}
				return true;
			}
			if (tagB == wallCollisionTag)
			{
				
				//on top
				if (nodeA->getPosition().y >= nodeA->getPosition().y + (nodeA->getContentSize().height * nodeA->getScaleY() * 0.5)) {
					nodeA->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 10));
				}
				return true;
			}
		}
		else if (tagB == enemyCollisionTag)
		{
			if (tagA == attackTag) {
				for (int i = 0; i < Enemies.size(); i++) {
					if (Player->isShadow == false) {
						if (Enemies.at(i)->getSprite()->getPhysicsBody()->getShape(0)->getBody()->getNode() == nodeB) {
							Enemies.at(i)->getHit(Player->getPosition().x);
							return true;
						}
					}
					else {
						if (Enemies.at(i)->getShadow(0)->getSprite()->getPhysicsBody()->getShape(0)->getBody()->getNode() == nodeB) {
							Enemies.at(i)->getShadow(0)->getHit(Player->getPosition().x);
							return true;
						}
					}
				}

				return false;
			}
			if (tagA == playerCollisionTag) {
				if (Player->isShadow == true) {
					Player->getShadow(0)->health = 0;
				}
				else {

					Player->getHit(nodeB->getPosition().x);
				}
				return true;
			}
			if (tagA == wallCollisionTag)
			{
				//on top
				if (nodeB->getPosition().y >= nodeA->getPosition().y + (nodeA->getContentSize().height * nodeA->getScaleY() * 0.5)) {
					nodeB->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 100));
				}
				return true;
			}

		}

		//PLAYER COLLISONS
		else if (tagA == playerCollisionTag)
		{
			//If the first object was the player and the second was a wall
			if (tagB == wallCollisionTag)
			{

				//IF NOT SHADOW
				if (Player->isShadow == false) {
					//on top
					if (nodeA->getPosition().y >= nodeB->getPosition().y + (nodeB->getContentSize().height * nodeB->getScaleY() * 0.5)) {
						onWall = false;
						//reset jump and dash
						candash = true;
						dash = 0;
						falling = false;
						grounded = true;
						//remove bounce
						Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 10));

						//back to idle
						if (Player->isShadow == false) {
							if (Player->animState != 0 && grounded == true && onWall == false) {
								if (Player->animState == 1) {
									Player->getSprite()->stopAction(walking);
								}
								else if (Player->animState == 2) {
									Player->getSprite()->stopAction(jumpP);
								}
								else if (Player->animState == 4)
								{
									Player->getSprite()->stopAction(attack);
								}
								Player->getSprite()->runAction(idle);
								Player->animState = 0;
							}
						}
						if (Player->getShadow(0)->animState != 0 && grounded == true && onWall == false) {
							if (Player->getShadow(0)->animState == 1) {
								Player->getShadow(0)->getSprite()->stopAction(walkingS);
							}
							else if (Player->getShadow(0)->animState == 2) {
								Player->getShadow(0)->getSprite()->stopAction(jumpS);
							}
							else if (Player->getShadow(0)->animState == 4)
							{
								Player->getShadow(0)->getSprite()->stopAction(attackS);
							}
							Player->getShadow(0)->getSprite()->runAction(idleS);
							Player->getShadow(0)->animState = 0;
						}

					}
					//Below
					else if (nodeA->getPosition().y <= nodeB->getPosition().y - (nodeB->getContentSize().height * nodeB->getScaleY() * 0.5))
					{
						//reset jump and dash
						candash = true;
						dash = 0;
						falling = true;
						grounded = false;
						//remove bounce
						Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 10));
					}
					else {//if not on top
						falling = false;
						candash = false;
						dash = 10;
						if (!(INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false) {
							//allow wall jump
							falling = false;
						}
						else if (!(XBoxController.GetButton(0, A)) && pad == true) {
							//allow wall jump
							falling = false;
						}
						onWall = true;
						Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x / 2.0, 10));
						//Player->getSprite()->runAction((TintTo::create(0.1f, Color3B(0, 0, 255))));

						//walljump animation
						if (Player->animState != 3) {
							if (Player->animState == 0) {
								Player->getSprite()->stopAction(idle);
							}
							else if (Player->animState == 1) {
								Player->getSprite()->stopAction(walking);
							}
							else if (Player->animState == 2) {
								Player->getSprite()->stopAction(jumpP);
							}
							Player->getSprite()->setTexture("UA/Player/walljump.png");
							Player->animState = 3;
						}
						if (Player->getShadow(0)->animState != 3) {
							if (Player->getShadow(0)->animState == 0) {
								Player->getShadow(0)->getSprite()->stopAction(idleS);
							}
							else if (Player->getShadow(0)->animState == 1) {
								Player->getShadow(0)->getSprite()->stopAction(walkingS);
							}
							else if (Player->getShadow(0)->animState == 2) {
								Player->getShadow(0)->getSprite()->stopAction(jumpS);
							}
							else if (Player->getShadow(0)->animState == 4)
							{
								Player->getShadow(0)->getSprite()->stopAction(attackS);
							}
							Player->getShadow(0)->getSprite()->setTexture("UA/Player/walljump.png");
							Player->getShadow(0)->animState = 3;
						}
						//on left side of wall
						if (nodeA->getPosition().x < nodeB->getPosition().x) {
							right = false;
							Player->getSprite()->setFlippedX(true);//face left
							Player->getShadow(0)->getSprite()->setFlippedX(true);//shadow face left

						}
						//on right side of wall
						else if (nodeA->getPosition().x >= nodeB->getPosition().x) {
							right = true;
							Player->getSprite()->setFlippedX(false);//face right
							Player->getShadow(0)->getSprite()->setFlippedX(false);//shadow face right
						}

					}

				}
				//IF YOU ARE SHADOW
				else if (Player->isShadow == true) {

					//on top
					if (nodeA->getPosition().y >= nodeB->getPosition().y + (nodeB->getContentSize().height * nodeB->getScaleY() * 0.5)) {
						//reset jump and dash
						onWall = false;
						candash = true;
						dash = 0;
						falling = false;
						grounded = true;
						//remove bounce
						Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 10));

						//back to idle
						if (Player->getShadow(0)->animState != 0 && grounded == true && onWall == false) {
							if (Player->getShadow(0)->animState == 1) {
								Player->getShadow(0)->getSprite()->stopAction(walkingS);
							}
							else if (Player->getShadow(0)->animState == 2) {
								Player->getShadow(0)->getSprite()->stopAction(jumpS);
							}
							else if (Player->getShadow(0)->animState == 4)
							{
								Player->getShadow(0)->getSprite()->stopAction(attackS);
							}
							Player->getShadow(0)->getSprite()->runAction(idleS);
							Player->getShadow(0)->animState = 0;
						}
					}
					//Below
					else if (nodeA->getPosition().y <= nodeB->getPosition().y - (nodeB->getContentSize().height * nodeB->getScaleY() * 0.5))
					{
						//reset jump and dash
						candash = true;
						dash = 0;
						falling = true;
						grounded = false;
						//remove bounce
						Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 10));
					}
					else {//if not on top
						falling = false;
						candash = false;
						dash = 10;
						if (!(INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false) {
							//allow wall jump
							falling = false;
						}
						else if (!(XBoxController.GetButton(0, A)) && pad == true) {
							//allow wall jump
							falling = false;
						}
						onWall = true;
						Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x / 2, 10));
						//Player->getShadow(0)->getSprite()->runAction((TintTo::create(0.1f, Color3B(125, 125, 255))));

						//walljump animation
						if (Player->getShadow(0)->animState != 3) {
							if (Player->getShadow(0)->animState == 0) {
								Player->getShadow(0)->getSprite()->stopAction(idleS);
							}
							else if (Player->getShadow(0)->animState == 1) {
								Player->getShadow(0)->getSprite()->stopAction(walkingS);
							}
							else if (Player->getShadow(0)->animState == 2) {
								Player->getShadow(0)->getSprite()->stopAction(jumpS);
							}
							Player->getShadow(0)->getSprite()->setTexture("UA/Player/walljump.png");
							Player->getShadow(0)->animState = 3;
						}

						//on left side of wall
						if (nodeA->getPosition().x <= nodeB->getPosition().x) {
							right = false;
							Player->getShadow(0)->getSprite()->setFlippedX(true);//shadow face left
						}
						//on right side of wall
						else if (nodeA->getPosition().x >= nodeB->getPosition().x) {
							right = true;
							Player->getShadow(0)->getSprite()->setFlippedX(false);//shadow face right
						}
					}
				}

				//Return true since the collision was correct and we want these two objects to collide
				return true;
			}
		}
		else if (tagB == playerCollisionTag)
		{
			//If the second object was the player and the first was a wall
			if (tagA == wallCollisionTag)
			{
				//IF NOT YOUR SHADOW
				if (Player->isShadow == false) {

					//on top
					if (nodeB->getPosition().y >= nodeA->getPosition().y + (nodeA->getContentSize().height * nodeA->getScaleY() * 0.5)) {
						onWall = false;
						//reset jump and dash
						candash = true;
						dash = 0;
						falling = false;
						grounded = true;
						//remove bounce
						nodeB->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 10));

						//back to idle
						if (Player->isShadow == false) {
							if (Player->animState != 0 && grounded == true && onWall == false) {
								if (Player->animState == 1) {
									Player->getSprite()->stopAction(walking);
								}
								else if (Player->animState == 2) {
									Player->getSprite()->stopAction(jumpP);
								}
								else if (Player->animState == 4)
								{
									Player->getSprite()->stopAction(attack);
								}
								Player->getSprite()->runAction(idle);
								Player->animState = 0;
							}
						}
						if (Player->getShadow(0)->animState != 0 && grounded == true && onWall == false) {
							if (Player->getShadow(0)->animState == 1) {
								Player->getShadow(0)->getSprite()->stopAction(walkingS);
							}
							else if (Player->getShadow(0)->animState == 2) {
								Player->getShadow(0)->getSprite()->stopAction(jumpS);
							}
							else if (Player->getShadow(0)->animState == 4)
							{
								Player->getShadow(0)->getSprite()->stopAction(attackS);
							}
							Player->getShadow(0)->getSprite()->runAction(idleS);
							Player->getShadow(0)->animState = 0;
						}
					}
					//Below
					else if (nodeB->getPosition().y  <= nodeA->getPosition().y - (nodeA->getContentSize().height * nodeA->getScaleY() * 0.5))
					{
						//reset jump and dash
						candash = true;
						dash = 0;
						falling = true;
						grounded = false;
						//remove bounce
						nodeB->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x, 10));
					}
					else {//if not on top
						onWall = true;
						falling = false;
						candash = false;
						dash = 10;
						if (!(INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false) {
							//allow wall jump
							falling = false;
						}
						else if (!(XBoxController.GetButton(0, A)) && pad == true) {
							//allow wall jump
							falling = false;
						}

						//walljump animation
						if (Player->animState != 3) {
							if (Player->animState == 0) {
								Player->getSprite()->stopAction(idle);
							}
							else if (Player->animState == 1) {
								Player->getSprite()->stopAction(walking);
							}
							else if (Player->animState == 2) {
								Player->getSprite()->stopAction(jumpP);
							}
							else if (Player->animState == 4)
							{
								Player->getSprite()->stopAction(attack);
							}
							Player->getSprite()->setTexture("UA/Player/walljump.png");
							Player->animState = 3;
						}
						if (Player->getShadow(0)->animState != 3) {
							if (Player->getShadow(0)->animState == 0) {
								Player->getShadow(0)->getSprite()->stopAction(idleS);
							}
							else if (Player->getShadow(0)->animState == 1) {
								Player->getShadow(0)->getSprite()->stopAction(walkingS);
							}
							else if (Player->getShadow(0)->animState == 2) {
								Player->getShadow(0)->getSprite()->stopAction(jumpS);
							}
							else if (Player->getShadow(0)->animState == 4)
							{
								Player->getShadow(0)->getSprite()->stopAction(attackS);
							}
							Player->getShadow(0)->getSprite()->setTexture("UA/Player/walljump.png");
							Player->getShadow(0)->animState = 3;
						}

						//on left side of wall
						if (nodeB->getPosition().x <= nodeA->getPosition().x) {
							right = false;
							Player->getSprite()->setFlippedX(true);//face left
							Player->getShadow(0)->getSprite()->setFlippedX(true);//shadow face left
							Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x / 2, 10));
							//Player->getSprite()->runAction((TintTo::create(0.1f, Color3B(0, 0, 255))));
						}
						//on right side of wall
						else if (nodeB->getPosition().x >= nodeA->getPosition().x) {
							right = true;
							Player->getSprite()->setFlippedX(false);//face right
							Player->getShadow(0)->getSprite()->setFlippedX(false);//shadow face right
							Player->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getSprite()->getPhysicsBody()->getVelocity().x / 2, 10));
							//Player->getSprite()->runAction((TintTo::create(0.1f, Color3B(0, 0, 255))));
						}
					}
				}
				//IF YOUR SHADOW
				else if (Player->isShadow == true) {

					//on top
					if (nodeB->getPosition().y >= nodeA->getPosition().y + (nodeA->getContentSize().height * nodeA->getScaleY() * 0.5)) {
						//reset jump and dash
						onWall = false;
						candash = true;
						dash = 0;
						falling = false;
						grounded = true;
						//remove bounce
						Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 10));

						//back to idle
						if (Player->getShadow(0)->animState != 0 && grounded == true && onWall == false) {
							if (Player->getShadow(0)->animState == 1) {
								Player->getShadow(0)->getSprite()->stopAction(walkingS);
							}
							else if (Player->getShadow(0)->animState == 2) {
								Player->getShadow(0)->getSprite()->stopAction(jumpS);
							}
							else if (Player->getShadow(0)->animState == 4)
							{
								Player->getShadow(0)->getSprite()->stopAction(attackS);
							}
							Player->getShadow(0)->getSprite()->runAction(idleS);
							Player->getShadow(0)->animState = 0;
						}
					}
					//Below
					else if (nodeB->getPosition().y <= nodeA->getPosition().y - (nodeA->getContentSize().height * nodeA->getScaleY() * 0.5))
					{
						//reset jump and dash
						candash = true;
						dash = 0;
						falling = true;
						grounded = false;
						//remove bounce
						Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x, 10));
					}
					else {//if not on top
						onWall = true;
						falling = false;
						candash = false;
						dash = 10;
						if (!(INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false) {
							//allow wall jump
							falling = false;
						}
						else if (!(XBoxController.GetButton(0, A)) && pad == true) {
							//allow wall jump
							falling = false;
						}

						//walljump animation
						if (Player->getShadow(0)->animState != 3) {
							if (Player->getShadow(0)->animState == 0) {
								Player->getShadow(0)->getSprite()->stopAction(idleS);
							}
							else if (Player->getShadow(0)->animState == 1) {
								Player->getShadow(0)->getSprite()->stopAction(walkingS);
							}
							else if (Player->getShadow(0)->animState == 2) {
								Player->getShadow(0)->getSprite()->stopAction(jumpS);
							}
							else if (Player->getShadow(0)->animState == 4)
							{
								Player->getShadow(0)->getSprite()->stopAction(attackS);
							}
							Player->getShadow(0)->getSprite()->setTexture("UA/Player/walljump.png");
							Player->getShadow(0)->animState = 3;
						}

						//on left side of wall
						if (nodeB->getPosition().x <= nodeA->getPosition().x) {
							right = false;
							Player->getShadow(0)->getSprite()->setFlippedX(true);//shadow face left
							Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x / 2, 10));
							//Player->getShadow(0)->getSprite()->runAction((TintTo::create(0.1f, Color3B(125, 125, 255))));
						}
						//on right side of wall
						else if (nodeB->getPosition().x >= nodeA->getPosition().x) {
							right = true;
							Player->getShadow(0)->getSprite()->setFlippedX(false);//shadow face right
							Player->getShadow(0)->getSprite()->getPhysicsBody()->setVelocity(Vec2(Player->getShadow(0)->getSprite()->getPhysicsBody()->getVelocity().x / 2, 10));
							//Player->getShadow(0)->getSprite()->runAction((TintTo::create(0.1f, Color3B(125, 125, 255))));
						}

					}
				}

				//Return true since the collision was correct and we want these two objects to collide
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

bool BaseLevel::onSepBeginCallback(PhysicsContact & contact)
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
		//ENEMY SEPERATION
		if (tagA == enemyCollisionTag)
		{
			if (tagB == playerCollisionTag) {
				//if (Player->isShadow == false)
				//	Enemies->getSprite()->runAction((TintTo::create(0.1f, Color3B(255, 255, 255))));
				//else
				//	Enemies->getShadow(0)->getSprite()->runAction((TintTo::create(0.1f, Color3B(0, 0, 0))));

				return true;
			}
		}
		else if (tagB == enemyCollisionTag)
		{
			if (tagA == playerCollisionTag) {
				//if (Player->isShadow == false)
				//	Enemies->getSprite()->runAction((TintTo::create(0.1f, Color3B(255, 255, 255))));
				//else
				//	Enemies->getShadow(0)->getSprite()->runAction((TintTo::create(0.1f, Color3B(0, 0, 0))));

				return true;
			}
		}

		//PLAYER SEPERATION
		if (tagA == playerCollisionTag)
		{
			//If the first object was the player and the second was a wall
			if (tagB == wallCollisionTag)
			{
				//on top
				if (nodeA->getPosition().y >= nodeB->getPosition().y + (nodeB->getContentSize().height * nodeB->getScaleY() * 0.4)) {
					if (!(INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false) {
						//allow wall jump
						falling = true;
					}
					else if (!(XBoxController.GetButton(0, A)) && pad == true) {
						//allow wall jump
						falling = true;
					}
					grounded = false;
				}
				else {
					//if (Player->animState == 1) {
					//	falling = false;
					//	grounded = true;
					//}
					onWall = false;
					//TintTo::create(0.1f, Color3B(255, 255, 255)
					//grounded = false;
					if (!(INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false) {
						//allow wall jump
						if (grounded == false)
							falling = true;
					}
					else if (!(XBoxController.GetButton(0, A)) && pad == true) {
						//allow wall jump
						if (grounded == false)
							falling = true;
					}
					else if (grounded == true)
						falling = false;
				}
				//Seems to make tings work
				//jump stillframe
				if (Player->isShadow == false) {
					if (Player->animState != 2 && grounded == false) {
						if (Player->animState == 0) {
							Player->getSprite()->stopAction(idle);
						}
						else if (Player->animState == 1) {
							Player->getSprite()->stopAction(walking);
						}
						else if (Player->animState == 4)
						{
							Player->getSprite()->stopAction(attack);
						}
						Player->getSprite()->setTexture("UA/Player/character.png");
						//Player->getSprite()->runAction(jumpP);
						Player->animState = 3;
					}
				}
				if (Player->getShadow(0)->animState != 2 && grounded == false) {
					if (Player->getShadow(0)->animState == 0) {
						Player->getShadow(0)->getSprite()->stopAction(idleS);
					}
					else if (Player->getShadow(0)->animState == 1) {
						Player->getShadow(0)->getSprite()->stopAction(walkingS);
					}
					else if (Player->getShadow(0)->animState == 4)
					{
						Player->getShadow(0)->getSprite()->stopAction(attackS);
					}
					Player->getShadow(0)->getSprite()->setTexture("UA/Player/character.png");
					//Player->getShadow(0)->getSprite()->runAction(jumpS);
					Player->getShadow(0)->animState = 3;
				}
				//Return true since the collision was correct and we want these two objects to collide
				return true;
			}
			if (tagB == flag1Tag || tagB == flag2Tag)
			{
				if ((INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false) {
					//allow wall jump
					falling = false;
					grounded = false;
				}
				else if ((XBoxController.GetButton(0, A)) && pad == true) {
					//allow wall jump
					falling = false;
					grounded = false;
				}
				if (!(INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false && grounded == false) {
					//allow wall jump
					falling = true;
				}
				else if (!(XBoxController.GetButton(0, A)) && pad == true && grounded == false) {
					//allow wall jump
					falling = true;
				}
				//Seems to make tings work
				//jump stillframe
				if (Player->isShadow == false) {
					if (Player->animState != 2 && grounded == false) {
						if (Player->animState == 0) {
							Player->getSprite()->stopAction(idle);
						}
						else if (Player->animState == 1) {
							Player->getSprite()->stopAction(walking);
						}
						else if (Player->animState == 4)
						{
							Player->getSprite()->stopAction(attack);
						}
						Player->getSprite()->setTexture("UA/Player/character.png");
						//Player->getSprite()->runAction(jumpP);
						Player->animState = 3;
					}
				}
				if (Player->getShadow(0)->animState != 2 && grounded == false) {
					if (Player->getShadow(0)->animState == 0) {
						Player->getShadow(0)->getSprite()->stopAction(idleS);
					}
					else if (Player->getShadow(0)->animState == 1) {
						Player->getShadow(0)->getSprite()->stopAction(walkingS);
					}
					else if (Player->getShadow(0)->animState == 4)
					{
						Player->getShadow(0)->getSprite()->stopAction(attackS);
					}
					Player->getShadow(0)->getSprite()->setTexture("UA/Player/character.png");
					//Player->getShadow(0)->getSprite()->runAction(jumpS);
					Player->getShadow(0)->animState = 3;
				}
				//grounded = false;
				return true;
			}
		}
		else if (tagB == playerCollisionTag)
		{

			//If the second object was the player and the first was a wall
			if (tagA == wallCollisionTag)
			{

				//on top
				if (nodeB->getPosition().y >= nodeA->getPosition().y + (nodeA->getContentSize().height * nodeA->getScaleY() * 0.4)) {
					if (!(INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false) {
						//allow wall jump
						falling = true;
					}
					else if (!(XBoxController.GetButton(0, A)) && pad == true) {
						//allow wall jump
						falling = true;
					}
					grounded = false;
				}
				else{
					//if (Player->animState == 1) {
					//	falling = false;
					//	grounded = true;
					//}
					onWall = false;
					//grounded = false;
					if (!(INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false) {
						//allow wall jump
						if (grounded == false)
							falling = true;
					}
					else if (!(XBoxController.GetButton(0, A)) && pad == true) {
						//allow wall jump
						if (grounded == false)
							falling = true;
					}
					else if (grounded == true)
						falling = false;

				}

				//jump stillframe
				if (Player->isShadow == false) {
					if (Player->animState != 2 && grounded == false) {
						if (Player->animState == 0) {
							Player->getSprite()->stopAction(idle);
						}
						else if (Player->animState == 1) {
							Player->getSprite()->stopAction(walking);
						}
						else if (Player->animState == 4)
						{
							Player->getSprite()->stopAction(attack);
						}
						Player->getSprite()->setTexture("UA/Player/character.png");
						Player->animState = 2;
					}
				}
				if (Player->getShadow(0)->animState != 2 && grounded == false) {
					if (Player->getShadow(0)->animState == 0) {
						Player->getShadow(0)->getSprite()->stopAction(idleS);
					}
					else if (Player->getShadow(0)->animState == 1) {
						Player->getShadow(0)->getSprite()->stopAction(walkingS);
					}
					else if (Player->getShadow(0)->animState == 4)
					{
						Player->getShadow(0)->getSprite()->stopAction(attackS);
					}
					Player->getShadow(0)->getSprite()->setTexture("UA/Player/character.png");
					Player->getShadow(0)->animState = 2;
				}

				//Return true since the collision was correct and we want these two objects to collide
				return true;
			}
			if (tagA == flag1Tag)
			{
				if ((INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false) {
					//allow wall jump
					falling = false;
					grounded = false;
				}
				else if ((XBoxController.GetButton(0, A)) && pad == true) {
					//allow wall jump
					falling = false;
					grounded = false;
				}
				if (!(INPUTS->getKey(KeyCode::KEY_SPACE)) && pad == false && grounded == false) {
					//allow wall jump
					falling = true;
				}
				else if (!(XBoxController.GetButton(0, A)) && pad == true && grounded == false) {
					//allow wall jump
					falling = true;
				}
				//jump stillframe
				if (Player->isShadow == false) {
					if (Player->animState != 2 && grounded == false) {
						if (Player->animState == 0) {
							Player->getSprite()->stopAction(idle);
						}
						else if (Player->animState == 1) {
							Player->getSprite()->stopAction(walking);
						}
						else if (Player->animState == 4)
						{
							Player->getSprite()->stopAction(attack);
						}
						Player->getSprite()->setTexture("UA/Player/character.png");
						Player->animState = 2;
					}
				}
				if (Player->getShadow(0)->animState != 2 && grounded == false) {
					if (Player->getShadow(0)->animState == 0) {
						Player->getShadow(0)->getSprite()->stopAction(idleS);
					}
					else if (Player->getShadow(0)->animState == 1) {
						Player->getShadow(0)->getSprite()->stopAction(walkingS);
					}
					else if (Player->getShadow(0)->animState == 4)
					{
						Player->getShadow(0)->getSprite()->stopAction(attackS);
					}
					Player->getShadow(0)->getSprite()->setTexture("UA/Player/character.png");
					Player->getShadow(0)->animState = 2;
				}
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


void BaseLevel::DrawWorld()
{
	///ALL SHADOWS ARE OFFSET BY Vec2(-25,25)

	//Creating the background
	background = Sprite::create("UA/Background/Warehouse.jpg");
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(1500, 675);
	background->setPositionZ(-250);
	background->setScale(0.9f, 0.9f);
	this->addChild(background, -100);

	
}

void BaseLevel::FlipWorld()
{
	if (!Player->isShadow) {
		director->getRunningScene()->stopAllActions();
		director->getRunningScene()->runAction(MoveBy::create(0.5f,Vec2(25,-10)));
		//Player->getSprite()->runAction(MoveTo::create(0.5f, Player->getShadow(0)->getSprite()->getPosition() + Vec2(25, -25)));
		mask->stopAllActions();
		mask->setOpacity(0);
		mask->runAction(FadeIn::create(0.5f));
	}
	else {
		director->getRunningScene()->stopAllActions();
		director->getRunningScene()->runAction(Follow::createWithOffset(Player->getShadow(0)->getSprite(), 0, -175, boundry));
		Player->getShadow(0)->getSprite()->runAction(MoveTo::create(0.5f, Player->getSprite()->getPosition() + Vec2(-25, 25)));
		mask->stopAllActions();
		mask->setOpacity(255);
		mask->runAction(FadeOut::create(0.5f));
	}
	//back to idle
	if (Player->animState != 0) {
		if (Player->animState == 1) {
			Player->getSprite()->stopAction(walking);
		}
		else if (Player->animState == 2)
		{
			Player->getSprite()->stopAction(jumpP);
		}
		else if (Player->animState == 4)
		{
			Player->getSprite()->stopAction(attack);
		}
		Player->getSprite()->runAction(idle);
		Player->animState = 0;
	}
	if (Player->getShadow(0)->animState != 0) {
		if (Player->getShadow(0)->animState == 1) {
			Player->getShadow(0)->getSprite()->stopAction(walkingS);
		}
		else if (Player->getShadow(0)->animState == 2)
		{
			Player->getShadow(0)->getSprite()->stopAction(jumpS);
		}
		else if (Player->getShadow(0)->animState == 4)
		{
			Player->getShadow(0)->getSprite()->stopAction(attackS);
		}
		Player->getShadow(0)->getSprite()->runAction(idleS);
		Player->getShadow(0)->animState = 0;
	}
}
//Init the static physics world pointer. Set it to be a nullptr which means it points to nothing
PhysicsWorld* BaseLevel::physicsWorld = nullptr;
Scene* BaseLevel::sceneHandle = nullptr;