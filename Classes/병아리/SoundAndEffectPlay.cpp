//
//  SoundAndEffectPlay.cpp
//  bellum
//
//  Created by LeeBong Kyu on 13. 8. 28..
//
//

#include "SoundAndEffectPlay.h"

//private

bool SoundAndEffectPlay::checkBGMSetting()
{
    bool returnValue = false;
    
    dataContorl = InternalDataControl();
    std::string settingData = dataContorl.getBackgroundSoundOption();
    
    if (settingData.compare("on") == 0) {
        //CCLOG("sound on");
        returnValue = true;
    }
    else
    {
        //CCLOG("sound off");
        returnValue = false;
    }
    
    return returnValue;
}

bool SoundAndEffectPlay::checkEffectSetting()
{
    bool returnValue = false;
    
    dataContorl = InternalDataControl();
    std::string settingData = dataContorl.getEffectSoundOption();
    
    if (settingData.compare("on") == 0) {
        //CCLOG("sound on");
        returnValue = true;
    }
    else
    {
        //CCLOG("sound off");
        returnValue = false;
    }
    
    return returnValue;
    
}

//public

void SoundAndEffectPlay::playMainBGM()
{
    if (this->checkBGMSetting()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("main_bgm.mp3", true);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
}

void SoundAndEffectPlay::playBGMInit()
{
    if (this->checkBGMSetting()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("night-forest.mp3", true);
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
}

void SoundAndEffectPlay::playBGMTick()
{
    if (this->checkBGMSetting()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("cave.mp3");
        CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    }
}


void SoundAndEffectPlay::playEffectExplosion()
{
    if (this->checkEffectSetting()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("explosion.mp3");
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    }
}

void SoundAndEffectPlay::playEffectTiger()
{
    if (this->checkEffectSetting()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("tiger.mp3");
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    }
}

void SoundAndEffectPlay::playEffectFlight()
{
    if (this->checkEffectSetting()) {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("jetsound.mp3");
    }
    else
    {
        CocosDenshion::SimpleAudioEngine::sharedEngine()->stopAllEffects();
    }
}



