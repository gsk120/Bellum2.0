#include "AppDelegate.h"
//#include "TitleScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
	database = NULL;
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
//<<<<<<< HEAD
    pDirector->setDisplayStats(true);
//=======
//<<<<<<< HEAD
    //pDirector->setDisplayStats(true);
    //pDirector->setDisplayStats(false);
    
//=======
    //pDirector->setDisplayStats(true);
//>>>>>>> 8c2819ca82638455976bb82f0321fc0f0fac5685

//>>>>>>> a6d4c945fcea1411ce16407e04194cfa98b90a9e
    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    //DB 만들기
    this->createAndSetDatabase();

    // create a scene. it's an autorelease object
    CCScene *pScene = MainMenuScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::createAndSetDatabase()
{
    //데이터베이스의 파일 경로를 확인하여 DB를 만들고 테이블을 생성합니다.
    //테이블을 생성하는 데 필요한 정보는 정의된 대로 개발합니다.
    
    //데이터베이스로 시용할 변수 선언
    databaseFileName = cocos2d::CCFileUtils::sharedFileUtils()->getWritablePath() + "bellumDB.sqlite";
    char* errormessage;
    int resultCode = 0;
    
    //DB를 연다.
    resultCode = sqlite3_open(databaseFileName.c_str(), &database);
    if(resultCode != SQLITE_OK)
    {
        CCLog("database open error");
        //에러시 처리할 작업을 정의한다.
    }
    
    //테이블을 만들어 준다.
    
    //게임 설정 테이블
    string createConfigTableQuery = "create table IF NOT EXISTS configTable(\
        table_id integer primary key autoincrement,\
        bgmSetting text,\
        bgmValue int, \
        effectSetting text,\
        effectValue int, \
        vibrationSetting text\
    )";
    
    resultCode = sqlite3_exec(database, createConfigTableQuery.c_str(), NULL, NULL, &errormessage);
    if (resultCode != SQLITE_OK) {
        //테이블 생성 에러를 처리한다.
        CCLog("create table error: %s",errormessage);
        
    }
    
    //사용자 테이블
    string createUserTableQuery = "create table IF NOT EXISTS userTable (\
    table_id int,\
    user_id varchar(50) not null,\
    nickname varchar(50),\
    password text not null,\
    email text,\
    primary key(table_id, user_id)\
    )";
    
    resultCode = sqlite3_exec(database, createUserTableQuery.c_str(), NULL, NULL, &errormessage);
    if (resultCode != SQLITE_OK) {
        //테이블 생성 에러를 처리한다.
        CCLog("create table error: %s",errormessage);
        
    }
    
    
    
    
    //기본값 추가하기
    //먼저 셋팅해 둬야 할 값이 있다면 셋팅해 두는 것으로 한다.
    
    string configCountQuery = "select count(*) from configTable";
    int configCount = 0;
    
    sqlite3_stmt *statement;
    if (sqlite3_prepare_v2(database, configCountQuery.c_str(), -1, &statement, NULL) == SQLITE_OK) {
        while (sqlite3_step(statement) == SQLITE_ROW) {
            //컬럼 불러오기
            
            configCount = sqlite3_column_int(statement, 0);
        }
    }
    sqlite3_reset(statement);
    
    if (configCount < 1) {
        //설정값 셋팅하기
        string insertConfigData = "insert or replace into configTable (table_id, bgmSetting, bgmValue, effectSetting, effectValue, vibrationSetting) values(1,'on',50,'on',50,'on')";
        resultCode = sqlite3_exec(database, insertConfigData.c_str(), NULL, NULL, &errormessage);
        if(resultCode != SQLITE_OK)
            {
            CCLog("insert error: %s",errormessage);
            }
        
    }
    
    sqlite3_close(database);
    
    
    
}
