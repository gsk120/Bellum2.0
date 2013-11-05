//
//  MainMenuScene.h
//  bellum
//
//  Created by Bong Kyu Lee on 13. 7. 29..
//
//

#ifndef __bellum__MainMenuScene__
#define __bellum__MainMenuScene__

#include "cocos2d.h"
#include "TestGroundScene.h"
#include "SoundAndEffectPlay.h"

class MainMenuScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    //game menu function
    void gameStartTapped();
    void gameContinueTapped();
    void gameOptionTapped();
    
    float widthScale;
    float heightScale;
    
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainMenuScene);
    
    //virtual void registerWithTouchDispatcher();
    //virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    
    void drawSceneAndSettingVariable();
    virtual bool isTouchEnabled	();
    void ccTouchesBegan(CCSet *touches, CCEvent *event);
    //virtual bool ccTouchBegan	(CCTouch * 	pTouch, CCEvent * 	pEvent );
    
    /*
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    */
    
private:
    float startPointX;
    float startPointY;
    
    float continuePointX;
    float continuePointY;
    
    float optionPointX;
    float optionPointY;
    
    float menuWidth;
    float menuHeight;
};

#endif /* defined(__bellum__MainMenuScene__) */
