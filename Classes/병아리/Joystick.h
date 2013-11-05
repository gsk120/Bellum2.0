//
//  Joystick.h
//  JoyStickEx
//
//  Created by Jaewhan Lee on 13. 6. 5..
//  Copyright www.cocos2d-x.kr 2013³â. All rights reserved.
//

#ifndef __JoyStickEx__Joystick__
#define __JoyStickEx__Joystick__

#include "cocos2d.h"

using namespace cocos2d;

class Joystick : public CCLayer
{
    
public:
    virtual bool init();
    CREATE_FUNC(Joystick);

    CCPoint getVelocity(){ return velocity; }

private:
    
    CCPoint kCenter;
    CCSprite *thumb;
    bool isPressed;
    
    CCPoint velocity;
    
    void updateVelocity(CCPoint point);
    void resetJoystick();
    bool handleLastTouch();

    void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
};

#endif
