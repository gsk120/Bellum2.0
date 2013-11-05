//
//  TitleScene.h
//  bellum
//
//  Created by Bong Kyu Lee on 13. 7. 29..
//
//

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//#include "CocosDenshion.h"
//#include "CocosDenshion.h"
#include "SimpleAudioEngine.h"
#include "InternalDataControl.h"
#include "MainMenuScene.h"


class TitleScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    void startMenuTapped(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(TitleScene);
    
    //사운드 처리
    //SimpleAudioEngine *audioEngine;
    void playBGM();
    
    //내부 데이터(옵션값) 확인용
    InternalDataControl dataControl;
};

#endif // __HELLOWORLD_SCENE_H__
