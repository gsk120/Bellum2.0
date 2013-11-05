//
//  InternalDataControl.cpp
//  bellum
//
//  Created by Bong Kyu Lee on 13. 8. 7..
//
//

#include "InternalDataControl.h"

std::string InternalDataControl::getBackgroundSoundOption()
{
    std::string returnValue;
    
    dbResult = sqlite3_open(dbFileName.c_str(), &database);
    if (dbResult != SQLITE_OK) {
        CCLOG("db file opne error");
    }
    
    std::string query = "select bgmSetting from configTable where table_id = 1";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            //컬럼 불러오기
            char* result = (char*)sqlite3_column_text(statement, 0);
            
            //CCLOG("result: %s",result);
            returnValue = result;
        }
    }
    
    sqlite3_close(database);
    
    return returnValue;
}

std::string InternalDataControl::getEffectSoundOption()
{
    std::string returnValue;
    
    dbResult = sqlite3_open(dbFileName.c_str(), &database);
    if (dbResult != SQLITE_OK) {
        CCLOG("db file opne error");
    }
    
    std::string query = "select effectSetting from configTable where table_id = 1";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            //컬럼 불러오기
            char* result = (char*)sqlite3_column_text(statement, 0);
            
            //CCLOG("result: %s",result);
            returnValue = result;
        }
    }
    
    sqlite3_close(database);

    
    return returnValue;
}

std::string InternalDataControl::getVibrationOption()
{
    std::string returnValue;
    
    dbResult = sqlite3_open(dbFileName.c_str(), &database);
    if (dbResult != SQLITE_OK) {
        CCLOG("db file opne error");
    }
    
    std::string query = "select vibrationSetting from configTable where table_id = 1";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            //컬럼 불러오기
            char* result = (char*)sqlite3_column_text(statement, 0);
            
            //CCLOG("result: %s",result);
            returnValue = result;
        }
    }
    
    sqlite3_close(database);

    
    return returnValue;
}

float InternalDataControl::getBackgroundSoundValue()
{
    float returnValue = 0;
    
    dbResult = sqlite3_open(dbFileName.c_str(), &database);
    if (dbResult != SQLITE_OK) {
        CCLOG("db file opne error");
    }
    
    std::string query = "select bgmValue from configTable where table_id = 1";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            //컬럼 불러오기
            
            
            //CCLOG("result: %s",result);
            returnValue = sqlite3_column_int(statement, 0);
            
        }
    }
    
    sqlite3_close(database);
    
    //CCLOG("%f",returnValue);
    
    return returnValue/100;
}

float InternalDataControl::getEffectSoundValue()
{
    float returnValue = 0;
    
    dbResult = sqlite3_open(dbFileName.c_str(), &database);
    if (dbResult != SQLITE_OK) {
        CCLOG("db file opne error");
    }
    
    std::string query = "select effectValue from configTable where table_id = 1";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            //컬럼 불러오기
            
            
            //CCLOG("result: %s",result);
            returnValue = sqlite3_column_int(statement, 0);
            
        }
    }
    
    sqlite3_close(database);
    
    //CCLOG("%f",returnValue);
    
    return returnValue/100;

}

int InternalDataControl::getBackgroundSoundValueUsingOption()
{
    int returnValue = 0;
    
    dbResult = sqlite3_open(dbFileName.c_str(), &database);
    if (dbResult != SQLITE_OK) {
        CCLOG("db file opne error");
    }
    
    std::string query = "select bgmValue from configTable where table_id = 1";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            //컬럼 불러오기
                        
            
            //CCLOG("result: %s",result);
            returnValue = sqlite3_column_int(statement, 0);

        }
    }
    
    sqlite3_close(database);

    
    return returnValue;
}

int InternalDataControl::getEffectSoundValueUsingOption()
{
    int returnValue = 0;
    
    dbResult = sqlite3_open(dbFileName.c_str(), &database);
    if (dbResult != SQLITE_OK) {
        CCLOG("db file opne error");
    }
    
    std::string query = "select effectValue from configTable where table_id = 1";
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(database, query.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            //컬럼 불러오기
            
            
            //CCLOG("result: %s",result);
            returnValue = sqlite3_column_int(statement, 0);
            ;
        }
    }
    
    sqlite3_close(database);
    
    
    return returnValue;
}

void InternalDataControl::setBackgroundSoundOption(std::string onValue, int volValue)
{
    //CCLOG("input data: %s",value);
    //cout<<"input data: "<<value<<endl;
    
    dbResult = sqlite3_open(dbFileName.c_str(), &database);
    if (dbResult != SQLITE_OK)
    {
    CCLOG("db file open error");
    }
    
    std::string query = "update configTable set bgmSetting = '"+onValue+"' where table_id = 1 ";
    cout<<"query: "<<query<<endl;
    dbResult = sqlite3_exec(database, query.c_str(), NULL, NULL, &errorMessage);
    if (dbResult != SQLITE_OK) {
        CCLOG("update error: %s",errorMessage);
    }
    
    sqlite3_close(database);
    
}

void InternalDataControl::setEffectSoundOption(std::string onValue, int volValue)
{
    //CCLOG("input data: %s",value);
    
    dbResult = sqlite3_open(dbFileName.c_str(), &database);
    if (dbResult != SQLITE_OK)
        {
        CCLOG("db file open error");
        }
    
    std::string query = "update configTable set effectSetting = '"+onValue+"' where table_id = 1 ";
    cout<<"query: "<<query<<endl;
    
    dbResult = sqlite3_exec(database, query.c_str(), NULL, NULL, &errorMessage);
    if (dbResult != SQLITE_OK) {
        CCLOG("update error: %s",errorMessage);
    }
    
    sqlite3_close(database);

}

void InternalDataControl::setVibrationOption(std::string value)
{
    //CCLOG("input data: %s",value);
    
    dbResult = sqlite3_open(dbFileName.c_str(), &database);
    if (dbResult != SQLITE_OK)
        {
        CCLOG("db file open error");
        }
    
    std::string query = "update configTable set vibrationSetting = '"+value+"' where table_id = 1 ";
    cout<<"query: "<<query<<endl;
    dbResult = sqlite3_exec(database, query.c_str(), NULL, NULL, &errorMessage);
    if (dbResult != SQLITE_OK) {
        CCLOG("update error: %s",errorMessage);
    }
    
    sqlite3_close(database);

}




