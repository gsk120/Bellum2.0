//
//  StageSelectScene.h
//  bellum
//
//  Created by Bong Kyu Lee on 13. 8. 5..
//
//

#ifndef __bellum__StageSelectScene__
#define __bellum__StageSelectScene__

//#include <iostream>
#include "cocos2d.h"

class StageSelectScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(StageSelectScene);
    
    void menuCallbackBuyCharater(CCObject* pSender);

};

#endif /* defined(__bellum__StageSelectScene__) */
