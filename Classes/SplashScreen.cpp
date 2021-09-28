#include "SplashScreen.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"
#include "TestLevel.h"

USING_NS_CC;
using namespace Input;

Scene* SplashScreen::createScene()
{
	//Background Music
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/intro.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/intro.mp3", true);
	// 'scene' is an autorelease object
	Scene* scene = Scene::create();
	SplashScreen* layer = SplashScreen::create();

	scene->addChild(layer);

	sceneHandle = scene;

	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	//Get the physics world from the scene so that we can work with it later
	//If we didn't do this, we would have to call director->getRunningScene()->getPhysicsWorld() every time we wanted to do something to the physics world
	//physicsWorld = scene->getPhysicsWorld();
	return scene;
}

void SplashScreen::onExit()
{
	Scene::onExit();
}

void SplashScreen::onEnter()
{
	DISPLAY->createDebugConsole(true);
	std::cout << "THE CONSOLE IS NOW OPEN" << std::endl;//uncoment this to remove console window
	Scene::onEnter();
}

bool SplashScreen::init()
{
	//////////////////////////////
	// super init first
	if (!Scene::init())
	{
		return false;
	}
	//Get the director from cocos so we can use it when needed
	director = Director::getInstance();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	setPosition(director->getWinSizeInPixels().width / 2, director->getWinSizeInPixels().height * 0.1);

	//Draw objects like background
	DrawWorld();

	//First
	Size winSize = Director::getInstance()->getWinSize();

	auto cache = SpriteFrameCache::getInstance(); //Creates a cache for the sprite sheet
	cache->addSpriteFramesWithFile("UA/Background/Splash Screen Cover Animation-0.plist"); //Grabs the sprite sheet
	char file[100] = { 0 }; //Not entirely sure what this does, but you need to grab it so you can pushback values for the vector
	for (int i = 0; i <= 17; i++) //Loops however many frames you have in the animation
	{
		sprintf(file, "%d.png", i); //Iterates by %d(+) and grabs whatever the name of the frames in the sprite sheet are
		auto frame = cache->getSpriteFrameByName(file);
		coverFrame.pushBack(frame); //stores them into an array
	}

	auto cache1 = SpriteFrameCache::getInstance(); //Creates a cache for the sprite sheet
	cache1->addSpriteFramesWithFile("UA/Background/Splash Screen Cover Animation-1.plist"); //Grabs the sprite sheet
	char file1[100] = { 0 }; //Not entirely sure what this does, but you need to grab it so you can pushback values for the vector
	for (int i = 18; i <= 35; i++) //Loops however many frames you have in the animation
	{
		sprintf(file1, "%d.png", i); //Iterates by %d(+) and grabs whatever the name of the frames in the sprite sheet are
		auto frame1 = cache1->getSpriteFrameByName(file1);
		coverFrame.pushBack(frame1); //stores them into an array
	}

	auto cache2 = SpriteFrameCache::getInstance(); //Creates a cache for the sprite sheet
	cache2->addSpriteFramesWithFile("UA/Background/Splash Screen Cover Animation-2.plist"); //Grabs the sprite sheet
	char file2[100] = { 0 }; //Not entirely sure what this does, but you need to grab it so you can pushback values for the vector
	for (int i = 36; i <= 53; i++) //Loops however many frames you have in the animation
	{
		sprintf(file2, "%d.png", i); //Iterates by %d(+) and grabs whatever the name of the frames in the sprite sheet are
		auto frame2 = cache2->getSpriteFrameByName(file2);
		coverFrame.pushBack(frame2); //stores them into an array
	}

	auto cache3 = SpriteFrameCache::getInstance(); //Creates a cache for the sprite sheet
	cache3->addSpriteFramesWithFile("UA/Background/Splash Screen Cover Animation-3.plist"); //Grabs the sprite sheet
	char file3[100] = { 0 }; //Not entirely sure what this does, but you need to grab it so you can pushback values for the vector
	for (int i = 54; i <= 68; i++) //Loops however many frames you have in the animation
	{
		sprintf(file3, "%d.png", i); //Iterates by %d(+) and grabs whatever the name of the frames in the sprite sheet are
		auto frame3 = cache3->getSpriteFrameByName(file3);
		coverFrame.pushBack(frame3); //stores them into an array
	}
	/////////////////////////////////////////////////Logo//////////////////////////////////////////////////////
	//First Turn (1/2)


	auto cache4 = SpriteFrameCache::getInstance();
	cache4->addSpriteFramesWithFile("UA/Background/Logo Still.plist");
	char file4[100] = { 0 };
	for (int i = 69; i <= 76; i++)
	{
		sprintf(file4, "%d.png", i);
		auto frame4 = cache4->getSpriteFrameByName(file4);
		coverFrame.pushBack(frame4);
	}


	/////////////////////////////////////////////////PAGE TURN////////////////////////////////////////////////////////////////////
	//First Turn (1/2)
	auto cache5 = SpriteFrameCache::getInstance();
	cache5->addSpriteFramesWithFile("UA/Background/First Page Turn-0.plist");
	char file5[100] = { 0 };
	for (int i = 77; i <= 94; i++)
	{
		sprintf(file5, "%d.png", i);
		auto frame5 = cache5->getSpriteFrameByName(file5);
		coverFrame.pushBack(frame5);
	}

	//First Turn (2/2)
	auto cache6 = SpriteFrameCache::getInstance();
	cache6->addSpriteFramesWithFile("UA/Background/First Page Turn-1.plist");
	char file6[100] = { 0 };
	for (int i = 95; i <= 101; i++)
	{
		sprintf(file6, "%d.png", i);
		auto frame6 = cache6->getSpriteFrameByName(file6);
		coverFrame.pushBack(frame6);
	}
	animation6 = Animation::createWithSpriteFrames(coverFrame, 0.0175);



	//Second Turn (1/2)
	auto cache7 = SpriteFrameCache::getInstance();
	cache7->addSpriteFramesWithFile("UA/Background/Second Page Turn-0.plist");
	char file7[100] = { 0 };
	for (int i = 102; i <= 119; i++)
	{
		sprintf(file7, "%d.png", i);
		auto frame7 = cache7->getSpriteFrameByName(file7);
		blankFrame.pushBack(frame7);
	}

	//Second Turn (2/2)
	auto cache8 = SpriteFrameCache::getInstance();
	cache8->addSpriteFramesWithFile("UA/Background/Second Page Turn-1.plist");
	char file8[100] = { 0 };
	for (int i = 120; i <= 121; i++)
	{
		sprintf(file8, "%d.png", i);
		auto frame8 = cache6->getSpriteFrameByName(file8);
		blankFrame.pushBack(frame8);
	}
	animation8 = Animation::createWithSpriteFrames(blankFrame, 0.014);

	//Third Page Turn
	auto cache9 = SpriteFrameCache::getInstance();
	cache9->addSpriteFramesWithFile("UA/Background/Third Page Turn-0.plist");
	char file9[100] = { 0 };
	for (int i = 122; i <= 139; i++)
	{
		sprintf(file9, "%d.png", i);
		auto frame9 = cache6->getSpriteFrameByName(file9);
		roomFrame.pushBack(frame9);
	}
	animation9 = Animation::createWithSpriteFrames(roomFrame, 0.022);



	//New Zoom 1/4
	auto cache10 = SpriteFrameCache::getInstance();
	cache10->addSpriteFramesWithFile("UA/Background/openScene-0.plist");
	char file10[100] = { 0 };
	for (int i = 140; i <= 157; i++)
	{
		sprintf(file10, "%d.png", i);
		auto frame10 = cache10->getSpriteFrameByName(file10);
		introFrame.pushBack(frame10);
	}

	//New Zoom 2/4
	//Vector<SpriteFrame*> introFrame(18);
	auto cache12 = SpriteFrameCache::getInstance();
	cache12->addSpriteFramesWithFile("UA/Background/openScene-1.plist");
	char file12[100] = { 0 };
	for (int i = 158; i <= 175; i++)
	{
		sprintf(file12, "%d.png", i);
		auto frame12 = cache12->getSpriteFrameByName(file12);
		introFrame.pushBack(frame12);
	}

	//New Zoom 3/4
	//Vector<SpriteFrame*> introFrame(18);
	auto cache13 = SpriteFrameCache::getInstance();
	cache13->addSpriteFramesWithFile("UA/Background/openScene-2.plist");
	char file13[100] = { 0 };
	for (int i = 176; i <= 194; i++)
	{
		sprintf(file13, "%d.png", i);
		auto frame13 = cache13->getSpriteFrameByName(file13);
		introFrame.pushBack(frame13);
	}

	//New Zoom 4/4
	//Vector<SpriteFrame*> introFrame(18);
	auto cache14 = SpriteFrameCache::getInstance();
	cache14->addSpriteFramesWithFile("UA/Background/openScene-3.plist");
	char file14[100] = { 0 };
	for (int i = 195; i <= 205; i++)
	{
		sprintf(file14, "%d.png", i);
		auto frame14 = cache14->getSpriteFrameByName(file14);
		introFrame.pushBack(frame14);
	}
	animation14 = Animation::createWithSpriteFrames(introFrame, 0.095);


	auto animate6 = Animate::create(animation6);
	auto animate8 = Animate::create(animation8);
	auto animate9 = Animate::create(animation9);
	auto animate14 = Animate::create(animation14);
	flip = Sequence::create(animate6, Repeat::create(animate8, 8), animate9, animate14, NULL);

	flip->retain();

	start->runAction(Repeat::create(Blink::create(9999, 9999), 9999));

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();

	return true;
}

//Call constantly
void SplashScreen::update(float deltaTime)//UPDATE LOOP
{
	if (!background->isFlippedX()) {
		XBoxController.DownloadPackets(1);
		bool connect = false;
		if (XBoxController.GetConnected(0))
			connect = XBoxController.GetButton(0, Input::Start);

		if (INPUTS->getKeyPress(KeyCode::KEY_F))
		{
			this->stopAllActions();
			this->removeAllComponents();
			cocos2d::CCDirector::sharedDirector()->purgeCachedData();
			SpriteFrameCache::getInstance()->removeSpriteFrames();
			SpriteFrameCache::destroyInstance();
			this->cleanup();
			DISPLAY->init(1000.0f, 500.0f, "Shadow Game (Stalactites)", false);
			Scene* scene = TestLevel::createScene();
			director->getInstance()->replaceScene(scene);
		}
		if (INPUTS->getKeyPress(KeyCode::KEY_ENTER) || connect)
		{

			//splash11->setVisible(true);
			//splash11->runAction(willThisWork);

			//animate8->setTarget(splash11);
			//animate8->retain();
			//willThisWork->retain();


			Size winSize = Director::getInstance()->getWinSize();
			splash = CCSprite::create("UA/Background/Splash Screen VFINAL.png");
			splash->setPosition(winSize.width *0.5, winSize.height *0.5);
			splash->setScaleX(0.9f);
			splash->setOpacity(255);
			this->addChild(splash, -101);

			//Run Animations
			//6 - Cover/Logo
			//8 - Blank
			//9 - Room
			//10 - Old Zoom
			//11 - New Zoom
			fullting = Sequence::create(flip, TintTo::create(0.5f,0,0,0), RemoveSelf::create(true), NULL);
			fullting->retain();

			splash->runAction(fullting);
			background->setTexture("black.png");
			white->setOpacity(0);
			background->setFlippedX(true);
			start->stopAllActions();
			start->runAction(RemoveSelf::create());
			start = nullptr;
		}
	}
	else if (fullting->isDone()) {
		this->stopAllActions();
		this->removeAllComponents();
		cocos2d::CCDirector::sharedDirector()->purgeCachedData();
		SpriteFrameCache::getInstance()->removeSpriteFrames();
		SpriteFrameCache::destroyInstance();
		this->cleanup();
		DISPLAY->init(1000.0f, 500.0f, "Shadow Game (Stalactites)", false);
		Scene* scene = TestLevel::createScene();
		director->getInstance()->replaceScene(scene);
	}

}

void SplashScreen::DrawWorld()
{
	///ALL SHADOWS ARE OFFSET BY Vec2(-25,25)

	//Creating the background
	background = Sprite::create("UA/Background/Splash Screen VFINAL.png");
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(650, 325);
	background->setScaleX(0.9f);
	white = Sprite::create("UA/Background/white.png");
	white->setAnchorPoint(Vec2(0.5f, 0.5f));
	white->setPosition(650, 325);
	white->setScaleX(0.9f);
	background->setOpacity(0);
	background->runAction(FadeIn::create(0.5f));
	//Creating the background
	start = Sprite::create("UA/Background/Press_to_Start.png");
	start->setAnchorPoint(Vec2(0.5f, 0.5f));
	start->setPosition(650, 255);
	//background->setScale(0.5);
	this->addChild(white, -103);
	this->addChild(background, -102);
	this->addChild(start, -90);
}

//Init the static physics world pointer. Set it to be a nullptr which means it points to nothing
Scene* SplashScreen::sceneHandle = nullptr;