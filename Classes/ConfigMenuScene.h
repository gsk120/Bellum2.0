//
//  ConfigMenuScene.h
//  bellum
//
//  Created by Bong Kyu Lee on 13. 8. 7..
//
//

#ifndef __bellum__ConfigMenuScene__
#define __bellum__ConfigMenuScene__

#include "cocos2d.h"
//#include "GUI\CCScrollView\CCTableView.h"
//#include "CCTableView.h"
#include "InternalDataControl.h"
#include "SoundAndEffectPlay.h"


class ConfigMenuScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    //void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(ConfigMenuScene);

    //variable
    std::string onBGM;
    std::string onEffect;
    std::string onVibration;
    
    cocos2d::CCMenu *mainMenu;
    
    std::string bgmLabelString;
    std::string effectLabelString;
    std::string vibrationLabelString;
    
    cocos2d::CCLabelTTF *bgmLabel;
    cocos2d::CCLabelTTF *effectLabel;
    cocos2d::CCLabelTTF *vibrationLabel;
    
    cocos2d::CCMenuItemLabel *bgmMenu;
    cocos2d::CCMenuItemLabel *effectMenu;
    cocos2d::CCMenuItemLabel *vibrationMenu;
    
    InternalDataControl dataControl;
    
    float widthScale;
    float heightScale;
    
    //method
    
    //menu action method
    void bgmSettingMenuTapped(CCObject* pSender);
    void effectSettingMenuTapped(CCObject* pSender);
    void vibrationSettingMenuTapped(CCObject* pSender);
    
    //pop scene method
    void popScene(CCObject* pSender);
    
    void drawScene();
    
    
};



#endif /* defined(__bellum__ConfigMenuScene__) */
