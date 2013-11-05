//
//  ConfigSettingScene.cpp
//  bellum
//
//  Created by LeeBong Kyu on 13. 8. 20..
//
//

#include "ConfigSettingScene.h"
#include "InternalDataControl.h"

USING_NS_CC;

CCScene* ConfigSettingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ConfigSettingScene *layer = ConfigSettingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ConfigSettingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    //이전 화면으로 돌아가기 위한 버튼을 만든다.
    CCMenuItemImage *popButton = CCMenuItemImage::create("CloseNormal.png",
                                                         "CloseSelected.png", this, menu_selector(ConfigSettingScene::popScene));
    CCMenu *popMenu = CCMenu::create(popButton, NULL);
    popMenu->setPosition(ccp(origin.x + popButton->getContentSize().width/2, origin.y + popButton->getContentSize().height/2 + visibleSize.height - popButton->getContentSize().height));
    
    this->addChild(popMenu);
    settingOptionString = CCUserDefault::sharedUserDefault()->getStringForKey("optionValue");
    CCLog("setting string: %s",settingOptionString.c_str());
    
    if (settingOptionString.compare("bgm") == 0) {
        CCLog("bgm setting");
        this->BGMAndEffectSceneSetting(settingOptionString);
    }
    else if(settingOptionString.compare("effect") == 0)
    {
        CCLog("effect setting");
        this->BGMAndEffectSceneSetting(settingOptionString);
    }
    else if(settingOptionString.compare("vibration") == 0)
    {
        CCLog("vibration setting");
        this->VibrationSceneSetting();
    }
    else
    {
        CCLog("setting error");
    }

    
    
    return true;
}


void ConfigSettingScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void ConfigSettingScene::popScene(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

/*
void ConfigSettingScene::setSettingOptionSeting(std::string optionValue)
{
    settingOptionString = optionValue;
}
 */

void ConfigSettingScene::BGMAndEffectSceneSetting(std::string optionValue)
{
    //on off setting 메뉴를 윗쪽에 제작한다.
    
    //볼륨 컨트롤이 가능한 슬라이드를 만든다.
    
    //CCUserDefault::sharedUserDefault()->setStringForKey("optionValue", "bgm");
    CCLog("setting start - %s",optionValue.c_str());
    
    //설정할 타이틀 주기
    
    
    //스위치 메뉴 추가
    InternalDataControl dataControl;
    if (optionValue.compare("bgm") == 0) {
        switchStatus =  dataControl.getBackgroundSoundOption();
        volumeData = dataControl.getBackgroundSoundValueUsingOption();
    }
    else if (optionValue.compare("effect") == 0)
    {
        switchStatus = dataControl.getEffectSoundOption();
        volumeData = dataControl.getEffectSoundValueUsingOption();
    }
    
    CCLog("status: %s, data: %d",switchStatus.c_str(),volumeData);
    
    CCLabelTTF *switchLabel = CCLabelTTF::create(switchStatus.c_str(), "Arial", 30);
    CCMenuItemLabel *switchItem = CCMenuItemLabel::create(switchLabel, this, menu_selector(ConfigSettingScene::setSwitchData));
    
    CCMenu *switchMenu = CCMenu::create(switchItem, NULL);
    switchMenu->setPosition(ccp(visibleSize.width/2 , visibleSize.height*2/3));
    this->addChild(switchMenu);
    
    //볼륨 조절할 스크롤 추가
    //볼륨 설정값 불러오기
    volumeString = "50";
    CCLabelTTF *valueLabel = CCLabelTTF::create(volumeString.c_str(), "Arial", 18);
    valueLabel->setPosition(ccp(visibleSize.width/2 , visibleSize.height*1/2));
    this->addChild(valueLabel);
    
    /*
    cocos2d::extension::CCControlSlider *slider = cocos2d::extension::CCControlSlider::create(NULL, "", "");
    slider->setMinimumValue(0);
    slider->setM/Users/caucapstone/Downloads/adt-bundle-mac-x86_64-20130729aximumValue(100);
    slider->setPosition(ccp(visibleSize.width/2 , visibleSize.height*1/3));
    this->addChild(slider);/Users/caucapstone/Downloads/adt-bundle-mac-x86_64-20130729
    */
    
}

void ConfigSettingScene::VibrationSceneSetting()
{
    //그냥 진동 가능한지 아닌지만 확인하는 수준으로 메뉴를 만들어 처리한다.
    //기존 소스 이용해도 문제 없음.
/*    
    CCMenuItemLabel *switchItem = CCMenuItemLabel::create(CCLabelTTF::create("on", "Arial", 20), this, menu_selector(ConfigSettingScene::setConfigData));
    CCMenu *switchMenu = CCMenu::create(switchItem, NULL);
    this->addChild(switchMenu);
	*/
    
    //CCUserDefault::sharedUserDefault()->setStringForKey("optionValue", "vibration");
}

void ConfigSettingScene::setVolumeData()
{
    
}

void ConfigSettingScene::setSwitchData(CCObject* pSneder)
{
    
}



