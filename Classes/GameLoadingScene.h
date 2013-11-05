//
//  GameLoadingScene.h
//  bellum
//
//  Created by LeeBong Kyu on 13. 8. 26..
//
//

#ifndef __bellum__GameLoadingScene__
#define __bellum__GameLoadingScene__

#include <iostream>
#include <sstream>
#include <string>
#include <ostream>
#include "cocos2d.h"

class GameLoadingScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(GameLoadingScene);
    
    void setLoadingImage(cocos2d::CCSize visibleSize);
    void loadGame();
};


#endif /* defined(__bellum__GameLoadingScene__) */
