//
//  ScrollMenu.h
//  bellum
//
//  Created by Bong Kyu Lee on 13. 8. 14..
//
//

#ifndef __bellum__ScrollMenu__
#define __bellum__ScrollMenu__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;

class ScrollMenu:public CCMenu
{
public:
    ScrollMenu();
    virtual ~ScrollMenu();
    
    CREATE_FUNC(ScrollMenu);
    
    static ScrollMenu* create(CCMenuItem* item,...);
    static ScrollMenu* createWithArray(CCArray* pArrayOfItems);
    static ScrollMenu* createWithItems(CCMenuItem* item, va_list args);
    
    
    bool isTouching;
    CCPoint m_touchesStart;
    CCPoint m_touchesEnd;
    
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    
};


#endif /* defined(__bellum__ScrollMenu__) */
