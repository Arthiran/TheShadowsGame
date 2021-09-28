#include "AppDelegate.h"
#include "DisplayHandler.h"
#include "InputHandler.h"
//#include "TestLevel.h"
#include "SplashScreen.h"
//#include "LevelOne.h"
//#include "LevelTwo.h"
#include "BossLevel.h"
//#include "LevelFour.h"
//#include "LevelFive.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1600, 900);


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
	AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director

	Director* director = Director::getInstance();
	//auto screen = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		//glview = GLViewImpl::createWithRect("The Shadow's Game", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
		glview = GLViewImpl::createWithFullScreen("The Shadow's Game");


#else
		glview = GLViewImpl::create("The Shadow's Game");
#endif
		director->setOpenGLView(glview);
		DISPLAY->init(1000.0f, 500.0f, "The Shadow's Game", false);
	}

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	// Set the design resolution
	//glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
	glview->setDesignResolutionSize(1300, 650, ResolutionPolicy::NO_BORDER);
	auto frameSize = glview->getFrameSize();


	//if the frame's height is larger than the height of medium size.
	//	if (frameSize.height > mediumResolutionSize.height)
	//{        
	//    director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
	//}
	//// if the frame's height is larger than the height of small size.
	//	else if (frameSize.height > smallResolutionSize.height)
	//{        
	//    director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
	//}
	//// if the frame's height is smaller than the height of medium size.
	//else
	//{        
	//    director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
	//}
	//
	//    register_all_packages();
	//
	//    // create a scene. it's an autorelease object
	//    auto scene = HelloWorld::createScene();
	//
	//    // run
	//    director->runWithScene(scene);

	//Director* director = Director::getInstance();

	//DISPLAY->init(1000.0f, 500.0f, "The Shadow's Game", true);

	Scene* splash = SplashScreen::createScene();
	//Scene* splash = LevelFive::createScene();
	director->runWithScene(splash);



	///Unsure if this is necessary to have
	/*if (INPUTS->getKeyPress(KeyCode::KEY_SPACE))
	{
	DISPLAY->init(1000.0f, 500.0f, "Shadow Game (Stalactites)", false);

	Scene* scene = HelloWorld::createScene();
	director->getInstance()->replaceScene(scene);
	//director->runWithScene(scene);
	}*/

	INPUTS->init();
	INPUTS->setExitOnEscape(false);


	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
