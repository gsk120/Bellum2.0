//
//  StageSelectScene.cpp
//  bellum
//
//  Created by Bong Kyu Lee on 13. 8. 5..
//
//

#include "StageSelectScene.h"
#include "ScrollMenu.h"

USING_NS_CC;

CCScene* StageSelectScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StageSelectScene *layer = StageSelectScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StageSelectScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //사이즈 받아오기 (윈도우 사이즈)
    //CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //스크롤 뷰 및 페이지 컨트롤 설정
    
    //스크롤 되는 메뉴 불러오기
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCLayerColor* layer = CCLayerColor::create();
    layer->setPosition(0, 0);
    layer->setContentSize(CCSizeMake(s.width, 210));
    
    for (int i = 0; i < 4; i++)
        {
        std::string str = "CloseNormal.png";
        CCMenuItemImage* item = CCMenuItemImage::create(str.c_str(),
                                                        str.c_str(),
                                                        this,
                                                        menu_selector(StageSelectScene::menuCallbackBuyCharater));
        item->setTag(i);
        ScrollMenu* menu = ScrollMenu::create(item, NULL);
        menu->setPosition(ccp(i * 100, 100));
        layer->addChild(menu);
        }
    
    // Set up scroll view
    cocos2d::extension::CCScrollView *scrollView = cocos2d::extension::CCScrollView::create(s, layer);
    scrollView->setAnchorPoint(ccp(0,0));
    scrollView->setPosition(ccp(0, 465));
    scrollView->setDirection(cocos2d::extension::kCCScrollViewDirectionHorizontal);
    
    this->addChild(scrollView);
    
    
    return true;
}


void StageSelectScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void StageSelectScene::menuCallbackBuyCharater(CCObject* pSender)
{
    
}
