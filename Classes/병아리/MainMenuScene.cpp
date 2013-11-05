//
//  MainMenuScene.cpp
//  bellum
//
//  Created by Bong Kyu Lee on 13. 7. 29..
//
//

#include "MainMenuScene.h"
#include "StageSelectScene.h"
#include "ConfigMenuScene.h"
#include "GameLoadingScene.h"

USING_NS_CC;

CCScene* MainMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainMenuScene *layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->setTouchEnabled(true);
    this->drawSceneAndSettingVariable();
    
    SoundAndEffectPlay sound = SoundAndEffectPlay();
    sound.playMainBGM();
    
    return true;
}


void MainMenuScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MainMenuScene::drawSceneAndSettingVariable()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCSprite *background = CCSprite::create("Main.png");
    background->setAnchorPoint(CCPointZero);
    background->setPosition(CCPointZero);
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    
    this->addChild(background);
    
    widthScale = visibleSize.width / background->getContentSize().width;
    heightScale = visibleSize.height / background->getContentSize().height;
    
    //게임 메뉴 만들기 - 강제로 sprite를 써서 만든다.
    //해상도에 따른 크기 조절이 CCMenu를 이용하면 깨진다.
    
    CCSprite *startSprite = CCSprite::create("Main-Start.png");
    startSprite->setAnchorPoint(CCPointZero);
    startSprite->setPosition(CCPointZero);
    startSprite->setScaleX(widthScale);
    startSprite->setScaleY(heightScale);
    startSprite->setPosition(ccp(visibleSize.width - (widthScale * startSprite->getContentSize().width) - 20, (heightScale * startSprite->getContentSize().height) * 3 - 20));
    this->addChild(startSprite);
    
    
    CCSprite *continueSprite = CCSprite::create("Main-Continue.png");
    continueSprite->setAnchorPoint(CCPointZero);
    continueSprite->setPosition(CCPointZero);
    continueSprite->setScaleX(widthScale);
    continueSprite->setScaleY(heightScale);
    continueSprite->setPosition(ccp(visibleSize.width - (widthScale * continueSprite->getContentSize().width) - 20, (heightScale * continueSprite->getContentSize().height) * 2 - 20));
    this->addChild(continueSprite);
    
    
    CCSprite *optionSprite = CCSprite::create("Main-Option.png");
    optionSprite->setAnchorPoint(CCPointZero);
    optionSprite->setPosition(CCPointZero);
    optionSprite->setScaleX(widthScale);
    optionSprite->setScaleY(heightScale);
    optionSprite->setPosition(ccp(visibleSize.width - (widthScale * optionSprite->getContentSize().width) - 20, (heightScale * optionSprite->getContentSize().height) * 1 - 20));
    this->addChild(optionSprite);
    
    
    startPointX = visibleSize.width - (widthScale * startSprite->getContentSize().width) - 20;
    startPointY = (heightScale * startSprite->getContentSize().height) * 3 - 20;
    
    continuePointX = visibleSize.width - (widthScale * continueSprite->getContentSize().width) - 20;
    continuePointY = (heightScale * continueSprite->getContentSize().height) * 2 - 20;
    
    optionPointX = visibleSize.width - (widthScale * optionSprite->getContentSize().width) - 20;
    optionPointY = (heightScale * optionSprite->getContentSize().height) * 1 - 20;
    
    menuWidth = widthScale * startSprite->getContentSize().width;
    menuHeight = heightScale * startSprite->getContentSize().height;
}

//menu control

void MainMenuScene::gameStartTapped()
{
    
    CCScene *testGroundScene = TestGroundScene::scene();
    CCDirector::sharedDirector()->replaceScene(testGroundScene);
    
    /*
    CCScene *loadingScene = GameLoadingScene::scene();
    CCDirector::sharedDirector()->pushScene(loadingScene);
    */
}

void MainMenuScene::gameContinueTapped()
{
    //continue 정보를 확인합니다.
    
}

void MainMenuScene::gameOptionTapped()
{
    CCScene *configScene = ConfigMenuScene::scene();
    CCDirector::sharedDirector()->pushScene(configScene);
}

/*
void MainMenuScene::registerWithTouchDispatcher()
{
    //CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);

}
 */

bool MainMenuScene::isTouchEnabled()
{
    return true;
}

void MainMenuScene::ccTouchesBegan(CCSet *touches, CCEvent *event){
    
    // 이곳에 터치를 할 경우에 대한 소스를 작성한다.
    //CCLog("0");
    CCSetIterator it = touches->begin();
    CCTouch *touch = (CCTouch *)(*it);
    CCPoint touchPoint = touch->getLocation();
    //CCLog("touch %f %f",touchPoint.x, touchPoint.y);

    //CCLog("start %f", startPointX);
    //CCLog("start %f", startPointX + menuWidth);
    
    //CCLog("start %f", startPointY);
    //CCLog("start %f", startPointY + menuHeight);
    
    if ((touchPoint.x >= startPointX && touchPoint.x <= startPointX + menuWidth) && (touchPoint.y >= startPointY && touchPoint.y <= startPointY + menuHeight)) {
        //CCLog("start tapped");
        this->gameStartTapped();
    }
    
    if ((touchPoint.x >= continuePointX && touchPoint.x <= continuePointX + menuWidth) && (touchPoint.y >= continuePointY && touchPoint.y <= continuePointY + menuHeight)) {
        //CCLog("start tapped");
        this->gameContinueTapped();
    }
    
    if ((touchPoint.x >= optionPointX && touchPoint.x <= optionPointX + menuWidth) && (touchPoint.y >= optionPointY && touchPoint.y <= optionPointY + menuHeight)) {
        //CCLog("start tapped");
        this->gameOptionTapped();
    }
    
    
    
}
