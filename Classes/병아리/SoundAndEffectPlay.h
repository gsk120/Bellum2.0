//
//  SoundAndEffectPlay.h
//  bellum
//
//  Created by LeeBong Kyu on 13. 8. 28..
//
//

#ifndef __bellum__SoundAndEffectPlay__
#define __bellum__SoundAndEffectPlay__

#include <iostream>
#include "cocos2d.h"
#include <sqlite3.h>
#include "InternalDataControl.h"
#include "SimpleAudioEngine.h"

class SoundAndEffectPlay
{
public:
    
    SoundAndEffectPlay()
    {
        
    }
    
    void playMainBGM();
    void playBGMInit();
    void playBGMTick();
    
    void playEffectExplosion();
    void playEffectTiger();
    void playEffectFlight();
    
    
private:
    InternalDataControl dataContorl;
    bool checkBGMSetting();
    bool checkEffectSetting();
};

#endif /* defined(__bellum__SoundAndEffectPlay__) */
