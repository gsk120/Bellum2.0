#include "GameOverScene.h"
#include "TestGroundScene.h"

using namespace cocos2d;

bool GameOverScene::init() {
	if (CCScene::init()) {
		this->_layer = GameOverLayer::create();
		this->_layer->retain();
		this->addChild(_layer);

		return true;
	}
	else {
		return false;
	}
}

GameOverScene::~GameOverScene() {
	if(_layer) {
		_layer->release();
		_layer = NULL;
	}
}

bool GameOverLayer::init() {
	if (CCLayerColor::initWithColor(ccc4(255,255,255,255))) {		//게임 오버 배경색
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		this->_label = CCLabelTTF::create("", "Artial", 32);
		_label->retain();
		_label->setColor(ccc3(0,0,0));			//게임오버 폰트 색
		_label->setPosition(ccp(winSize.width/2, winSize.height/2));
		this->addChild(_label);

		this->runAction(CCSequence::create(CCDelayTime::create(3), CCCallFunc::create(this, callfunc_selector(GameOverLayer::gameOverDone)), NULL));
		//3초후 메뉴화면으로 이동

		return true;
	}
	else {
		return false;
	}
}

void GameOverLayer::gameOverDone() {			//게임 오버 후 화면 전환
	CCDirector::sharedDirector()->replaceScene(MainMenuScene::scene());
}

GameOverLayer::~GameOverLayer() {
	if(_label) {
		_label->release();
		_label = NULL;
	}
}