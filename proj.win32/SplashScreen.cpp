#include "SplashScreen.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"

USING_NS_CC;
using namespace Input;

Scene* SplashScreen::createScene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::createWithPhysics();
	SplashScreen* layer = SplashScreen::create();

	scene->addChild(layer);

	sceneHandle = scene;

	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	//Get the physics world from the scene so that we can work with it later
	//If we didn't do this, we would have to call director->getRunningScene()->getPhysicsWorld() every time we wanted to do something to the physics world
	physicsWorld = scene->getPhysicsWorld();
	return scene;
}

void SplashScreen::onExit()
{
	Scene::onExit();
}

void SplashScreen::onEnter()
{
	DISPLAY->createDebugConsole(true);
	//std::cout << "THE CONSOLE IS NOW OPEN" << std::endl;
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

	return true;
}

void SplashScreen::DrawWorld()
{
	///ALL SHADOWS ARE OFFSET BY Vec2(-25,25)

	//Creating the background
	background = Sprite::create("UA/Background/Splash_Screen.jpg");
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(1000, 450);
	this->addChild(background, -100);
}
