//
//  InternalDataControl.h
//  bellum
//
//  Created by Bong Kyu Lee on 13. 8. 7..
//
//

#ifndef __bellum__InternalDataControl__
#define __bellum__InternalDataControl__

#include <iostream>
#include "cocos2d.h"
#include "sqlite3.h"

using namespace std;

class InternalDataControl
{
public:
    
    InternalDataControl()
    {
        dbFileName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath() + "bellumDB.sqlite";
		database = NULL;
		dbResult = 0;

    }
    
    std::string getBackgroundSoundOption();
    std::string getEffectSoundOption();
    std::string getVibrationOption();
    int getBackgroundSoundValueUsingOption();
    int getEffectSoundValueUsingOption();
    float getBackgroundSoundValue();
    float getEffectSoundValue();
    
    void setBackgroundSoundOption(std::string onValue, int volValue);
    void setEffectSoundOption(std::string onValue, int volValue);
    void setVibrationOption(std::string value);
    
    
    
    //game database control check - sqlite check
    
    //sqlite control
    sqlite3 *database;
    char* errorMessage;
    int dbResult;
    std::string dbFileName;
    
};

#endif /* defined(__bellum__InternalDataControl__) */
