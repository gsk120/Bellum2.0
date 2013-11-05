//
//  GameLoadingScene.cpp
//  bellum
//
//  Created by LeeBong Kyu on 13. 8. 26..
//
//

#include "GameLoadingScene.h"
#include "TestGroundScene.h"

USING_NS_CC;

CCScene* GameLoadingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLoadingScene *layer = GameLoadingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    this->setLoadingImage(visibleSize);
    //delay(2000);
    //CCDelayTime *delay = CCDelayTime::create(2.0f);
    //sleep(2000);
    //this->loadGame();
//<<<<<<< HEAD
    
    this->schedule(schedule_selector(GameLoadingScene::loadGame), 3.0f);
//=======
    //this->schedule(schedule_selector(GameLoadingScene::loadGame), 3.0f);
//>>>>>>> 493195a83d7719b0b7ab9ec4477faa274433b11f
    return true;
}


void GameLoadingScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameLoadingScene::setLoadingImage(cocos2d::CCSize visibleSize)
{
    int number = rand()%3+1;
    CCLog("number: %d",number);
    std::string numberString;
    std::ostringstream convert;
    convert << number;
    numberString = convert.str();
    
    //char *numberString =
    std::string fileName = "Loading";
    fileName.append(numberString);
    fileName.append(".png");
    
    CCSprite *background = CCSprite::create(fileName.c_str());
    background->setAnchorPoint(CCPointZero);
    background->setPosition(CCPointZero);
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    //CCLog("scale x: %f", visibleSize.width / background->getContentSize().width);
    //CCLog("scale y: %f", visibleSize.height / background->getContentSize().height);
    //CCLog("back: %f, %f",background->getContentSize().width, background->getContentSize().height);
    this->addChild(background);

}

void GameLoadingScene::loadGame()
{
    CCScene *testGroundScene = TestGroundScene::scene();
    CCDirector::sharedDirector()->replaceScene(testGroundScene);
}
