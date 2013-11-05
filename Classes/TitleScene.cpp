//
//  TitleScene.cpp
//  bellum
//
//  Created by Bong Kyu Lee on 13. 7. 29..
//
//

#include "TitleScene.h"

USING_NS_CC;

CCScene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleScene *layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
        {
        return false;
        }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCSprite *background = CCSprite::create("Main.png");
    background->setAnchorPoint(CCPointZero);
    background->setPosition(CCPointZero);
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    this->addChild(background);
    
    /*
    CCLabelTTF* pLabel = CCLabelTTF::create("bellum", "Arial", 32);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(pLabel, 1);
    */
    
    //CCMenuItemFont *mainItem = CCMenuItemFont::create("touch to start", this, menu_selector(TitleScene::startMenuTapped));
    CCMenuItemLabel *mainItem = CCMenuItemLabel::create(CCLabelTTF::create("touch to start", "Arial", 24), this, menu_selector(TitleScene::startMenuTapped));
    //mainItem->setAnchorPoint(CCPointZero);
    //mainItem->setPosition(CCPointZero);
    //mainItem->setScaleX(visibleSize.width / background->getContentSize().width);
    //mainItem->setScaleY(visibleSize.height / background->getContentSize().height);
    CCMenu *mainMenu = CCMenu::create(mainItem,NULL);
    //mainMenu->setAnchorPoint(CCPointZero);
    //mainMenu->setPosition(CCPointZero);
    //mainMenu->setScaleX(visibleSize.width / background->getContentSize().width);
    //mainMenu->setScaleY(visibleSize.height / background->getContentSize().height);
    
    this->addChild(mainMenu);
    
    
    //bgm 틀기
    this->playBGM();
    
    return true;
}


void TitleScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void TitleScene::startMenuTapped(CCObject* psender)
{
    CCScene *mainScene = MainMenuScene::scene();
    CCDirector::sharedDirector()->replaceScene(mainScene);
}


void TitleScene::playBGM()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("main_bgm.mp3", true);
    
    /*
    //엔진 설정하기
    audioEngine = CocosDenshion::SimpleAudioEngine::sharedEngine();
    
    //옵션 저장값 불러오기
    //std::string bgmOption = dataContol
    
    //배경음 처리
    audioEngine->playBackgroundMusic("bgm_day02.mp3", true);
    //audioEngine->stopBackgroundMusic();
    audioEngine->setBackgroundMusicVolume(0.5);
    */
    
    
    
}
