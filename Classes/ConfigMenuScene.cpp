//
//  ConfigMenuScene.cpp
//  bellum
//
//  Created by Bong Kyu Lee on 13. 8. 7..
//
//

#include "ConfigMenuScene.h"
#include "ConfigSettingScene.h"

using namespace cocos2d;

CCScene* ConfigMenuScene::scene()
{
    CCScene *scene = CCScene::create();
    ConfigMenuScene *layer = ConfigMenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool ConfigMenuScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->drawScene();
    
    return true;
}

/*
void ConfigMenuScene::menuCloseCallback(CCObject* pSender)
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

*/

void ConfigMenuScene::popScene(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void ConfigMenuScene::drawScene()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCSprite *background = CCSprite::create("Main.png");
    background->setAnchorPoint(CCPointZero);
    background->setPosition(CCPointZero);
    background->setScaleX(visibleSize.width / background->getContentSize().width);
    background->setScaleY(visibleSize.height / background->getContentSize().height);
    
    this->addChild(background);
    
    widthScale = visibleSize.width / background->getContentSize().width;
    heightScale = visibleSize.height / background->getContentSize().height;
    
    
    //메뉴 설정 작업을 진행한다.
    bgmLabelString = "BGM ";
    effectLabelString = "EFFECT ";
    vibrationLabelString = "VIBRATION ";
    
    //설정 메뉴에 표시할 데이터를 불러온다.
    dataControl = InternalDataControl();
    onBGM = dataControl.getBackgroundSoundOption();
    onEffect = dataControl.getEffectSoundOption();
    onVibration = dataControl.getVibrationOption();
    
    //CCLog("bgm: %s, effect: %s, vibration: %s",onBGM.c_str(),onEffect.c_str(), onVibration.c_str());
    
    int fontSize = 0;
    int paddingSize = 0;
    if (visibleSize.width <= 960) {
        fontSize = 24;
        paddingSize = 20;
    }
    else
    {
        fontSize = 80;
        paddingSize = 70;
    }
    
    //menu
    string input1 = bgmLabelString + onBGM;
    bgmLabel = CCLabelTTF::create(input1.c_str(), "Arial", fontSize);
    //bgmLabel = CCLabelTTF::create(bgmLabelString.c_str(), "Arial", 24);
    bgmMenu = CCMenuItemLabel::create(bgmLabel, this, menu_selector(ConfigMenuScene::bgmSettingMenuTapped));
    
    string input2 = effectLabelString + onEffect;
    effectLabel = CCLabelTTF::create(input2.c_str(), "Arial", fontSize);
    //effectLabel = CCLabelTTF::create(effectLabelString.c_str(), "Arial", 24);
    effectMenu = CCMenuItemLabel::create(effectLabel, this, menu_selector(ConfigMenuScene::effectSettingMenuTapped));
    /*
     string input3 = vibrationLabelString + onVibration;
     vibrationLabel = CCLabelTTF::create(input3.c_str(), "Arial", 24);
     //vibrationLabel = CCLabelTTF::create(vibrationLabelString.c_str(), "Arial", 24);
     vibrationMenu = CCMenuItemLabel::create(vibrationLabel, this, menu_selector(ConfigMenuScene::vibrationSettingMenuTapped));
     */
    
    //메뉴를 만들고 추가하기. 메뉴의 위치는 그냥 기본위치로 둔다. (기본위치: 정가운데)
    //mainMenu = CCMenu::create(bgmMenu, effectMenu, vibrationMenu, NULL);
    mainMenu = CCMenu::create(bgmMenu, effectMenu, vibrationMenu, NULL);
    //mainMenu->setPosition(ccp(origin.x / 3, origin.y / 3));
    mainMenu->alignItemsVerticallyWithPadding(paddingSize);
    this->addChild(mainMenu);
    
    
    //이전 화면으로 돌아가기 위한 버튼을 만든다.
    CCMenuItemImage *popButton = CCMenuItemImage::create("backButton.png",
                                                         "backButton.png", this, menu_selector(ConfigMenuScene::popScene));
    CCMenu *popMenu = CCMenu::create(popButton, NULL);
    popMenu->setPosition(ccp(origin.x + popButton->getContentSize().width/2, origin.y + popButton->getContentSize().height/2 + visibleSize.height - popButton->getContentSize().height));
    
    this->addChild(popMenu);
    
    ////CCLog("(%f, %f)",origin.x, origin.y);
    ////CCLog("(%f, %f)",visibleSize.width, visibleSize.height);
    ////CCLog("(%f, %f)",origin.x + popButton->getContentSize().width/2, origin.y + popButton->getContentSize().height/2);
}

//menu action

void ConfigMenuScene::bgmSettingMenuTapped(CCObject* pSender)
{
    SoundAndEffectPlay sound = SoundAndEffectPlay();
    
    if ( onBGM.compare("on") == 0 )
    {
        //켜져있다. 끄면 된다.
        //CCLog("on");
        onBGM = "off";
        string input = bgmLabelString + onBGM;
        bgmLabel->setString(input.c_str());
        
    }
    else
    {
        //CCLog("off");
        onBGM = "on";
        string input = bgmLabelString + onBGM;
        bgmLabel->setString(input.c_str());
        
    }
    dataControl.setBackgroundSoundOption(onBGM,0.5);
    
    sound.playMainBGM();
    
    /*
    CCUserDefault::sharedUserDefault()->setStringForKey("optionValue", "bgm");
    CCScene *scene = ConfigSettingScene::scene();
    CCDirector::sharedDirector()->pushScene(scene);
     */
}

void ConfigMenuScene::effectSettingMenuTapped(CCObject* pSender)
{
    
    if ( onEffect.compare("on") == 0 )
    {
        //켜져있다. 끄면 된다.
        //CCLog("on");
        onEffect = "off";
    string input = effectLabelString + onEffect;
    effectLabel->setString(input.c_str());
    }
    else
    {
        //CCLog("off");
        onEffect = "on";
    string input = effectLabelString + onEffect;
    effectLabel->setString(input.c_str());
    }
    dataControl.setEffectSoundOption(onEffect,0.5);
    
    /*
    
    CCUserDefault::sharedUserDefault()->setStringForKey("optionValue", "effect");
    CCScene *scene = ConfigSettingScene::scene();
    CCDirector::sharedDirector()->pushScene(scene);
     */
}

void ConfigMenuScene::vibrationSettingMenuTapped(CCObject* pSender)
{
    
    if ( onVibration.compare("on") == 0 )
    {
        //켜져있다. 끄면 된다.
        //CCLog("on");
        onVibration = "off";
    string input = vibrationLabelString + onVibration;
    vibrationLabel->setString(input.c_str());
    }
    else
    {
        //CCLog("off");
        onVibration = "on";
    string input = vibrationLabelString + onVibration;
    vibrationLabel->setString(input.c_str());

    }
    dataControl.setVibrationOption(onVibration);
     /*
    //ConfigSettingScene configSetting;
    //configSetting.setSettingOptionSeting("vibration");
      */
    /*
    CCScene *scene = ConfigSettingScene::scene("vibration");
    CCDirector::sharedDirector()->pushScene(scene);
    */
    
    /*
    
    CCUserDefault::sharedUserDefault()->setStringForKey("optionValue", "vibration");
    CCScene *scene = ConfigSettingScene::scene();
    CCDirector::sharedDirector()->pushScene(scene);
     
     */
}

