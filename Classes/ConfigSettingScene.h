//
//  ConfigSettingScene.h
//  bellum
//
//  Created by LeeBong Kyu on 13. 8. 20..
//
//

#ifndef __bellum__ConfigSettingScene__
#define __bellum__ConfigSettingScene__

#include <iostream>
#include <string>
#include "cocos2d.h"
#include "InternalDataControl.h"
//#include "CCControlSlider.h"

class ConfigSettingScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    //static cocos2d::CCScene* scene(std::string optionValue);
    
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(ConfigSettingScene);
    
    void popScene(CCObject* pSender);
    
    //void setSettingOptionSeting(std::string optionValue);
    
    void BGMAndEffectSceneSetting(std::string optionValue);
    void VibrationSceneSetting();
    void setVolumeData();
    
    void setSwitchData(CCObject* pSender);
    
private:
    std::string settingOptionString;
    
    InternalDataControl dataControl;
    
    cocos2d::CCSize visibleSize;
    cocos2d::CCPoint origin;
    
    std::string switchStatus;
    int volumeData;
    std::string volumeString;
    
    std::string loadSwitchData();
    std::string loadVolumeData();

};

#endif /* defined(__bellum__ConfigSettingScene__) */
