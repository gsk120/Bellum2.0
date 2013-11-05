#ifndef __TEST_GROUND_SCENE_H__
#define __TEST_GROUND_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"
#include "ContactListener.h"
#include "Joystick.h"
#include <sstream>
#include <queue>
#include <vector>
#include "Box2D\Dynamics\Joints\b2Joint.h"
//#include "SimpleAudioEngine.h"
#include "SoundAndEffectPlay.h"

using namespace cocos2d;

//<<<<<<< HEAD
class TestGroundScene : public cocos2d::CCLayer {
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();

	b2World* getWorld() { return world_; }
	CCSprite* getPlayerSprite() { return playerSprite; }

	void createBackgroundParallax();
	void createMaterial(CCSprite**, b2Body** ,char*, string, string, CCPoint);
	void createMaterialStatic(CCSprite**, b2Body**, char*, string, string, CCPoint);
	void createMovingSprite(float f, bool *check);
	void movePlayer(float f);
	void boom(b2Body* b, b2Body* material, bool* check);
	void fire(CCPoint point, CCSprite** sprite, b2Body** body, int caseNum);
	void deleteBoom(CCNode* sender, void* data);
	void doParticles(CCPoint point);
	void menuCloseCallback(CCObject* pSender);
	void addBodyToNode(string plistName, char*imgName, string shapeName, int order);
	void createTrap();
	void removeGround(int count);
	void createTiger();
	void tigerForward();
	void tigerAttack();

	CCPoint getSavePoint();  
	
	Joystick *joystick;

	CCSize winSize;
	//vector<CCSprite*> mineVector;
	CCSprite* mine1;
	CCSprite* mine2;
	CCSprite* mine3;
	CCSprite* mine4;
    CCSprite* mine5;
    CCSprite* mine6;
    CCSprite* mine7;
	CCSprite* tank;
	CCSprite* missile;
	CCSprite* flightMissile;
	CCSprite* flight;
	CCSprite* rock;
    CCSprite* rock2;
	CCSprite* box1;
	CCSprite* box2;
	CCSprite* deadBody;
	CCSprite* boneGrave;
	CCSprite* tiger;
	b2Body * minePhysics1;
	b2Body * minePhysics2;
	b2Body * minePhysics3;
	b2Body * minePhysics4;
    b2Body * minePhysics5;
    b2Body * minePhysics6;
    b2Body * minePhysics7;
	b2Body * tankPhysics;
	b2Body * missilePhysics;
	b2Body * flightMissilePhysics;
	b2Body * rockPhysics;
    b2Body * rockPhysics2;
	b2Body * boxPhysics1;
	b2Body * boxPhysics2;
	b2Body * deadBodyPhysics;
	b2Body * boneGravePhysics;
	b2Body * tigerPhysics;
	b2WeldJoint* weldJoint1;
	b2WeldJoint* weldJoint2;
	b2WeldJoint* weldJoint3;

	bool flightCheck;////////////////////////비행기 한번만 나오게하기
	bool rockCheck;/////////////////바위 한번
	bool collisionCheck;
	bool tigerCheck;
	bool musicCheck;
	ContactListener* myContactListener;

	void tick(float dt);
	void fireFrame(float dt);

	void createPlayer();
	void headingForward();
	void headingBackward();
	void jumpingForward();
	void jumpingBackward();
	void deadMotion();
	void Jump();
	b2Body* addPlayerShape(CCPoint point,const char* spriteName);

    //set sound setting
    SoundAndEffectPlay sound = SoundAndEffectPlay();
    
    // a selector callback
    
    // implement the "static node()" method manually
    CREATE_FUNC(TestGroundScene);
private:
	b2World *world_;
	CCSprite* playerSprite;
	b2Body *player;

	queue<b2Body*> bodyQueue;

};

class ClickButton : public cocos2d::CCLayer {
public:

	virtual bool init();

	CCSprite* getControlButton() { return controlButton; }
	bool getIsControlPressed() { return isControlPressed; }
	void setIsControlPressed(bool val) { isControlPressed = val; }
	void setControlButton(char* str) { controlButton = CCSprite::create(str); }
	void createControlButton();
	virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	bool isTouchInside(CCSprite* sprite, CCTouch* touch);


	Joystick* getJoystick() { return joystick; }

	CREATE_FUNC(ClickButton);

private:
	Joystick* joystick;
	CCSprite* controlButton;
	bool isControlPressed;
};

class BackGround : public cocos2d::CCLayer {
public:
	virtual bool init();
	void moveBackGround(float f);
	void createBackGround(int count);
	void removeBackGround(int count);

	CCSize winSize;
	CREATE_FUNC(BackGround);
};

#endif // __HELLOWORLD_SCENE_H__
