#include "LevelFiveTransition.h"
#include "SimpleAudioEngine.h"
#include "InputHandler.h"
#include "DisplayHandler.h"
#include "LevelFive.h"

USING_NS_CC;
using namespace Input;

Scene* LevelFiveTransition::createScene()
{
	//Background Music
	//CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/opening.mp3");
	//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/opening.mp3", true);
	// 'scene' is an autorelease object
	Scene* scene = Scene::create();
	LevelFiveTransition* layer = LevelFiveTransition::create();

	scene->addChild(layer);

	sceneHandle = scene;

	Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	//Get the physics world from the scene so that we can work with it later
	//If we didn't do this, we would have to call director->getRunningScene()->getPhysicsWorld() every time we wanted to do something to the physics world
	//physicsWorld = scene->getPhysicsWorld();
	return scene;
}

void LevelFiveTransition::onExit()
{
	Scene::onExit();
}

void LevelFiveTransition::onEnter()
{
	DISPLAY->createDebugConsole(true);
	std::cout << "THE CONSOLE IS NOW OPEN" << std::endl;//uncoment this to remove console window
	Scene::onEnter();
}

bool LevelFiveTransition::init()
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

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();

	return true;
}

//Call constantly
void LevelFiveTransition::update(float deltaTime)//UPDATE LOOP
{
	XBoxController.DownloadPackets(1);
	bool connect = false;
	if (XBoxController.GetConnected(0))
		connect = XBoxController.GetButton(0, Input::Start);

	DISPLAY->init(1000.0f, 500.0f, "Shadow Game (Stalactites)", false);

	SceneChange();

	/*if (cycle <= 50) start->setVisible(false);
	else if (cycle > 50 && cycle <= 100) start->setVisible(true);
	else if (cycle > 100) cycle = 0;
	else if (cycle < 0) cycle = 100;
	cycle++;*/

}

void LevelFiveTransition::SceneChange()
{
	Scene* scene = LevelFive::createScene();
	director->getInstance()->replaceScene(scene);

	//director->runWithScene(scene);
}

void LevelFiveTransition::DrawWorld()
{
	///ALL SHADOWS ARE OFFSET BY Vec2(-25,25)

	//Creating the background
	background = Sprite::create("UA/Background/black.png");
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(500, 250);
	//background->setScale(0.5);
	//Creating the background
	/*start = Sprite::create("UA/Background/Press_to_Start.png");
	start->setAnchorPoint(Vec2(0.5f, 0.5f));
	start->setPosition(500, 250);
	//background->setScale(0.5);*/
	this->addChild(background, -100);
	//this->addChild(start, -90);
}

//Init the static physics world pointer. Set it to be a nullptr which means it points to nothing
Scene* LevelFiveTransition::sceneHandle = nullptr;