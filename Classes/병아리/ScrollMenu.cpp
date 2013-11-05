//
//  ScrollMenu.cpp
//  bellum
//
//  Created by Bong Kyu Lee on 13. 8. 14..
//
//

#include "ScrollMenu.h"

ScrollMenu* ScrollMenu::create(CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    ScrollMenu *pRet = ScrollMenu::createWithItems(item, args);
    
    va_end(args);
    
    return pRet;
}

ScrollMenu* ScrollMenu::createWithArray(CCArray* pArrayOfItems)
{
    ScrollMenu *pRet = new ScrollMenu();
    if (pRet && pRet->initWithArray(pArrayOfItems))
        {
        pRet->autorelease();
        }
    else
        {
        CC_SAFE_DELETE(pRet);
        }
    
    return pRet;
}

ScrollMenu* ScrollMenu::createWithItems(CCMenuItem* item, va_list args)
{
    CCArray* pArray = NULL;
    if( item )
        {
        pArray = CCArray::create(item, NULL);
        CCMenuItem *i = va_arg(args, CCMenuItem*);
        while(i)
            {
            pArray->addObject(i);
            i = va_arg(args, CCMenuItem*);
            }
        }
    
    return ScrollMenu::createWithArray(pArray);
}

ScrollMenu::ScrollMenu()
{
}

ScrollMenu::~ScrollMenu()
{
}

void ScrollMenu::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool ScrollMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    m_touchesStart = touch->getStartLocation();
    
    return CCMenu::ccTouchBegan(touch, event);
    
}

void ScrollMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    
    CCMenu::ccTouchMoved(touch, event);
    
}

void ScrollMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
    m_touchesEnd = touch->getLocation();
    
    CCPoint difference = ccpSub(m_touchesEnd, m_touchesStart);
    
    if (difference.x > 5.0f || difference.y > 5.0f )
        {
        CCMenu::ccTouchCancelled(touch, event);
        }
    else if (difference.x < -5.0f || difference.y < -5.0f)
        {
        CCMenu::ccTouchCancelled(touch, event);
        }
    else
        {
        CCMenu::ccTouchEnded(touch, event);
        }
}