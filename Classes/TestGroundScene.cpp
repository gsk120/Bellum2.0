#include "TestGroundScene.h"
//#include "GB2ShapeCache-x.h"
//#include "Box2D\Dynamics\Joints\b2Joint.h"
#include "GB2ShapeCache-x.h"
#include "b2Joint.h"
#define PTM_RATIO 32
#define IMG_WIDTH 1280
USING_NS_CC;

using namespace std;

string ToString(int n);

static TestGroundScene *layer;
static ClickButton *clickLayer;
static BackGround *backLayer;
int ex=0;
bool ch=true;
int states=0;
int stateTime=0;
int tigerTime = 0;
int i = 0;

CCScene* TestGroundScene::scene()
{
    CCScene *scene = CCScene::create();
    
    layer = TestGroundScene::create();
	clickLayer = ClickButton::create();
	backLayer = BackGround::create();

    // add layer as a child to scene
	scene->addChild(backLayer);
    scene->addChild(layer);
	scene->addChild(clickLayer);

    // return the scene
    return scene;
}

bool BackGround::init() {//////////////////////////////////////////////////배경 설정
    
    if ( !CCLayer::init() )
    {
        return false;
    }
	
    winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *pBackGround = CCSprite::create("background-forest1.png");
	pBackGround->setAnchorPoint(ccp(0,0));/////////////////////////////화면전체가 1칸으로 인식 앞은 -, 뒤는 +

	this->schedule(schedule_selector(BackGround::moveBackGround));
	this->addChild(pBackGround, 0, 0);

	return true;
}

void BackGround::moveBackGround(float f) {
	if((layer->getPlayerSprite()->getPosition().x > (1280*i + winSize.width/2)) &&((layer->getPlayerSprite()->getPosition().x < (1280*i + (winSize.width*2)/3)))) {
		this->createBackGround(i);
		i++;
	}
	else if((layer->getPlayerSprite()->getPosition().x < (1280*i + winSize.width/2)) && ((layer->getPlayerSprite()->getPosition().x > (1280*i + winSize.width/3)))) {
		if(i>1) {
			this->removeBackGround(i);
		}
	}
	CCRect myBoundary = CCRectMake(0, 0, IMG_WIDTH*36, winSize.height);
	this->runAction(CCFollow::create(layer->getPlayerSprite(), myBoundary));
}

void BackGround::createBackGround(int count) {
	if(count < 6) {
		if(count%2 == 0) {
			float fcount = -((float)count+1);
			winSize = CCDirector::sharedDirector()->getWinSize();
			CCSprite* pBackground = CCSprite::create("background-forest2.png");
			pBackground->setAnchorPoint(ccp(fcount,0));
			this->addChild(pBackground, 0, count+1);
		}
		else if(count%2 == 1) {
			float fcount = -((float)count+1);
			winSize = CCDirector::sharedDirector()->getWinSize();
			CCSprite* pBackground = CCSprite::create("background-forest1.png");
			pBackground->setAnchorPoint(ccp(fcount,0));
			this->addChild(pBackground, 0, count+1);
		}
	}
	else if(count >= 6) {
		float fcount = -((float)count+1);
		winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite* pBackground = CCSprite::create("background-cave1.png");
		pBackground->setAnchorPoint(ccp(fcount,0));
		this->addChild(pBackground, 0, count+1);
	}
}

void BackGround::removeBackGround(int count) {
	this->removeChildByTag(count-2);
	//layer->removeGround(count);////////////////땅삭제
}

// on "init" you need to initialize your instance
bool TestGroundScene::init()
{    
//<<<<<<< HEAD
    //CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    /*CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(TestGroundScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);*/
//=======
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//>>>>>>> 493195a83d7719b0b7ab9ec4477faa274433b11f
	
	if ( !CCLayer::init() )
    {
        return false;
    }

	this->setTouchEnabled(true);

    winSize = CCDirector::sharedDirector()->getWinSize();
     
    b2Vec2 gravity = b2Vec2(0.0f, -9.8f);		//생성할 월드의 중력 설정
    this->world_ = new b2World(gravity);		//월드의 생성
    flightCheck = true;
	rockCheck = true;
	collisionCheck = true;
	tigerCheck = true;
	musicCheck = true;

    //스크린 경계선 생성 임시이므로 상하좌우 경계선 밖으로 못넘어가게 하는 부분
    b2BodyDef screen_body_def;
    screen_body_def.position.Set(0.0f, 0.0f);
    
    b2Body *screen_body = world_->CreateBody(&screen_body_def);
     
    b2EdgeShape screen_edge;
    b2FixtureDef screen_fixture_def;
     
    screen_fixture_def.shape = &screen_edge;
	screen_fixture_def.filter.groupIndex = -8;
     
    screen_edge.Set(b2Vec2(0.0f, 0.0f), b2Vec2((IMG_WIDTH*36)/PTM_RATIO, 0));		//아래 변
    screen_body->CreateFixture(&screen_fixture_def);
    screen_edge.Set(b2Vec2(0.0f, 0.0f), b2Vec2(0, winSize.height*20/PTM_RATIO));		//왼쪽 변
    screen_body->CreateFixture(&screen_fixture_def);
    //screen_edge.Set(b2Vec2(0.0f, winSize.height/PTM_RATIO), b2Vec2(IMG_WIDTH/PTM_RATIO, winSize.height/PTM_RATIO));		//윗 변
    //screen_body->CreateFixture(&screen_fixture_def);
    screen_edge.Set(b2Vec2((IMG_WIDTH*36)/PTM_RATIO, winSize.height/PTM_RATIO), b2Vec2((IMG_WIDTH*36)/PTM_RATIO, 0));		//오른쪽 변
    screen_body->CreateFixture(&screen_fixture_def);
	
	myContactListener = new ContactListener();
	world_->SetContactListener((b2ContactListener*) myContactListener);
	
	this->createBackgroundParallax();
	this->createPlayer();
	this->createTrap();
    /*
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/night-forest.mp3", true);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
	*/
    sound.playBGMInit();
	
	//this->createMaterial(&tank, &tankPhysics, "tank.png", "tank", "ground.plist", ccp(winSize.width/8, 500));

	this->schedule(schedule_selector(TestGroundScene::tick));
	//this->schedule(schedule_selector(TestGroundScene::fireFrame), 2.0f);
    return true;
}

void TestGroundScene::createTrap() {
	this->createMaterialStatic(&deadBody, &deadBodyPhysics, "dead-body.png", "dead-body", "ground.plist", ccp(1205, 240));
	this->createMaterialStatic(&boneGrave, &boneGravePhysics, "Bone-grave.png", "Bone-grave", "ground.plist", ccp(IMG_WIDTH*9 + 340, 75));
	this->createMaterial(&rock, &rockPhysics, "rock.png", "rock", "ground.plist", ccp(IMG_WIDTH, 500.0f));
	this->createMaterial(&box1, &boxPhysics1, "box.png", "box", "ground.plist", ccp(300, 400));
	this->createMaterialStatic(&mine1, &minePhysics1, "mine.png", "mine", "ground.plist", ccp(IMG_WIDTH*3+384, 345));
	this->createMaterialStatic(&mine2, &minePhysics2, "mine.png", "mine", "ground.plist", ccp(IMG_WIDTH*3+751, 328));
	this->createMaterialStatic(&mine3, &minePhysics3, "mine.png", "mine", "ground.plist", ccp(IMG_WIDTH*3+868, 328));
    this->createMaterialStatic(&mine5, &minePhysics5, "mine.png", "mine", "ground.plist", ccp(IMG_WIDTH*3+460, 295));
    this->createMaterialStatic(&mine6, &minePhysics6, "mine.png", "mine", "ground.plist", ccp(IMG_WIDTH*3+609, 290));
    this->createMaterialStatic(&mine7, &minePhysics7, "mine.png", "mine", "ground.plist", ccp(IMG_WIDTH*3+1157, 280));

	this->createMaterialStatic(&mine4, &minePhysics4, "mine.png", "mine", "ground.plist", ccp(IMG_WIDTH*9+80, 45));
	this->createMaterialStatic(&box2, &boxPhysics2, "stalactite.png", "stalactite", "ground.plist", ccp(IMG_WIDTH*9+233, 479));
}
 
void TestGroundScene::doParticles(CCPoint point) {
	CCParticleSystem* particleTest = CCParticleFire::create();
	particleTest->setAutoRemoveOnFinish(true);
	particleTest->retain();
	particleTest->setTexture(CCTextureCache::sharedTextureCache()->addImage("boom9.png"));
	if((particleTest!=NULL)) {
		particleTest->setScale(3.0);
		particleTest->setDuration(0.1f);
		particleTest->setPositionType(kCCPositionTypeRelative);
		particleTest->setPosition(point);
		this->addChild(particleTest);
	}
}

void TestGroundScene::boom(b2Body* b, b2Body* material, bool* check) {
	if(*check == true) {
		if(b == material) {
			CCSprite* sprite = (CCSprite*) b->GetUserData();
			CCPoint point = ccp(material->GetPosition().x*PTM_RATIO, material->GetPosition().y*PTM_RATIO);
			
			if(b == myContactListener->mineBody) {
				if (myContactListener->contactBody == player) {
					player->ApplyLinearImpulse(b2Vec2(0.0f, 200.0f), player->GetPosition());                    
                }
				else if(myContactListener->contactBody == tigerPhysics) {
                    world_->DestroyBody(boxPhysics2);
                    this->removeChild(box2);
					this->createMaterial(&box2, &boxPhysics2, "stalactite.png", "stalactite", "ground.plist", ccp(IMG_WIDTH*9+233, 479));
					tigerCheck = true;
					CCSprite* spriteData = (CCSprite*)tigerPhysics->GetUserData();
					this->removeChild(spriteData, true);
					world_->DestroyBody(tigerPhysics);
				}
			}
			CCFiniteTimeAction* finished = CCCallFuncND::create(this, callfuncND_selector(TestGroundScene::deleteBoom), (void*)b);
            sprite->runAction(CCSequence::create(CCDelayTime::create(0.1), finished, NULL));
            sound.playEffectExplosion();
            this->doParticles(point);/////////불꽃 생성
		}
		*check = false;
	}
}

void TestGroundScene::deleteBoom(CCNode* sender, void* data) {
	CCSprite* sprite = (CCSprite*) sender;
	b2Body* body = (b2Body*) data;
	this->removeChild(sprite, true);
	world_->DestroyBody(body);
}

void TestGroundScene::fire(CCPoint point, CCSprite** sprite, b2Body** body, int caseNum) {						//실제적으로 쏘고 힘가하는 함수
	switch (caseNum) {
	case 1:
		this->createMaterial(sprite, &(*body), "missile.png", "missile", "ground.plist", point);
		(*body)->ApplyForce(b2Vec2(5000.0f, 50.0f), (*body)->GetPosition());
		break;
	case 2:
		this->createMaterial(sprite, &(*body), "missile1.png", "missile1", "ground.plist", point);
		(*body)->ApplyForce(b2Vec2(-1000.0f, 50.0f), (*body)->GetPosition());
		break;
	default:
		break;
	}
}

void TestGroundScene::fireFrame(float dt) {						//발사시 스캐쥴로 지속적으로 호출할때 쓰는 함수
	CCPoint point = ccp(tankPhysics->GetPosition().x*PTM_RATIO, tankPhysics->GetPosition().y*PTM_RATIO);
	this->fire(point, &missile, &missilePhysics, 1);
}

void TestGroundScene::tick(float dt)
{

	// Box2D 물리 작용 스텝
    world_->Step(dt, 10, 10);

	this->movePlayer(dt);
	
	if(tigerCheck == false) {		//호랑이가 생성되 있으면 호랑이 움직임 함수
		this->tigerAttack();
	}

	for(b2Body *b = world_->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
			CCSprite *sprite = (CCSprite *)b->GetUserData();
			sprite->setPosition(ccp(b->GetPosition().x * PTM_RATIO,
				b->GetPosition().y * PTM_RATIO));
			sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
		
		if (b->GetFixtureList()->GetFilterData().groupIndex == 0) {
			if(b == myContactListener->mineBody)
				this->boom(b, myContactListener->mineBody, &(this->myContactListener->mineCheck));
		}
		if((b->GetUserData() == playerSprite) && (playerSprite->getPosition().x > (IMG_WIDTH*6)+(IMG_WIDTH*2)/3)) {			//호랑이 생성 파트
			if((b->GetUserData() == playerSprite) && (playerSprite->getPosition().x < (IMG_WIDTH*6)+(IMG_WIDTH*2)/3 + 10) && (tigerCheck == true)) {
				this->createTiger();
                sound.playEffectTiger();
				tigerCheck = false;
			}
		}
		if((b->GetUserData() == playerSprite) && (playerSprite->getPosition().x > (IMG_WIDTH*7)) && (musicCheck == true)) {
            sound.playBGMTick();
			musicCheck = false;
		}
		
		else if(b->GetFixtureList()->GetFilterData().groupIndex == 4) {
			if(b->GetUserData() == flightMissilePhysics->GetUserData())
				this->boom(b, flightMissilePhysics, &(this->myContactListener->flightMissileCheck));
		}
        
		if((b->GetUserData() == playerSprite) && (playerSprite->getPosition().x > IMG_WIDTH*5 && playerSprite->getPosition().x < IMG_WIDTH*5 + 20) && flightCheck==true) {
			this->createMovingSprite(2.0f, &flightCheck);
            sound.playEffectFlight();
		}

		if((b->GetUserData() == playerSprite) && (playerSprite->getPosition().x > IMG_WIDTH*5 && playerSprite->getPosition().x < IMG_WIDTH*5+20) && rockCheck==true) {
			this->createMaterial(&rock2, &rockPhysics2, "rock.png", "rock", "ground.plist", ccp(IMG_WIDTH*5+869, 650));
			rockCheck = false;
		}/*
		if((b->GetUserData() == playerSprite) && (playerSprite->getPosition().x > 5500 && playerSprite->getPosition().x < 5510) && collisionCheck == true) {
			world_->DestroyJoint(weldJoint1);
			weldJoint1=NULL;
			world_->DestroyJoint(weldJoint2);
			weldJoint2=NULL;
			world_->DestroyJoint(weldJoint3);
			weldJoint3=NULL;
			collisionCheck = false;
			doParticles(ccp(6080.0f,200.0f));
		}*/
	}
}

void TestGroundScene::createMovingSprite(float f, bool *check) {
	CCSprite* flight = CCSprite::create("flight.png");
	flight->setPosition(ccp(IMG_WIDTH*5+winSize.width/2, (winSize.height*6)/7));
	CCAction * actionMove = CCMoveTo::create(f, ccp(0 - flight->getContentSize().width/2, flight->getPositionY()));
	this->addChild(flight);
	flight->runAction(actionMove);
	this->fire(flight->getPosition(), &flightMissile, &flightMissilePhysics, 2);
	*check = false;
}
//// plist, 이미지, 모양, 보이드노드, 
void TestGroundScene::createBackgroundParallax() {
//<<<<<<< HEAD
	this->addBodyToNode("stage1_android-1.plist", "stage1_01.png", "stage1_01", 0);
	this->addBodyToNode("stage1_android-1.plist", "stage1_02.png", "stage1_02", -1);
	this->addBodyToNode("stage1_android-1.plist", "stage1_03.png", "stage1_03", -2);
	this->addBodyToNode("stage1_android-1.plist", "stage1_04.png", "stage1_04", -3);
	this->addBodyToNode("stage1_android-1.plist", "stage1_05.png", "stage1_05", -4);
	this->addBodyToNode("stage1_android-1.plist", "stage1_06.png", "stage1_06", -5);
	this->addBodyToNode("stage1_android-1.plist", "stage1_07.png", "stage1_07", -6);
	this->addBodyToNode("stage1_android-1.plist", "stage1_08.png", "stage1_08", -7);
	this->addBodyToNode("stage1_android-1.plist", "stage1_09.png", "stage1_09", -8);
	this->addBodyToNode("stage1_android-1.plist", "stage1_10.png", "stage1_10", -9);
	/*this->addBodyToNode("stage1_android-2.plist", "stage1_11.png", "stage1_11", -10);
	this->addBodyToNode("stage1_android-2.plist", "stage1_12.png", "stage1_12", -11);
	this->addBodyToNode("stage1_android-2.plist", "stage1_13.png", "stage1_13", -12);
	this->addBodyToNode("stage1_android-2.plist", "stage1_14.png", "stage1_14", -13);
	this->addBodyToNode("stage1_android-2.plist", "stage1_15.png", "stage1_15", -14);
	this->addBodyToNode("stage1_android-2.plist", "stage1_16.png", "stage1_16", -15);
	this->addBodyToNode("stage1_android-2.plist", "stage1_17.png", "stage1_17", -16);
	this->addBodyToNode("stage1_android-2.plist", "stage1_18.png", "stage1_18", -17);
	this->addBodyToNode("stage1_android-2.plist", "stage1_19.png", "stage1_19", -18);
	this->addBodyToNode("stage1_android-2.plist", "stage1_20.png", "stage1_20", -19);
	this->addBodyToNode("stage1_android-3.plist", "stage1_21.png", "stage1_21", -20);
	this->addBodyToNode("stage1_android-3.plist", "stage1_22.png", "stage1_22", -21);
	this->addBodyToNode("stage1_android-3.plist", "stage1_23.png", "stage1_23", -22);
	this->addBodyToNode("stage1_android-3.plist", "stage1_24.png", "stage1_24", -23);
	this->addBodyToNode("stage1_android-3.plist", "stage1_25.png", "stage1_25", -24);
	this->addBodyToNode("stage1_android-3.plist", "stage1_26.png", "stage1_26", -25);
	this->addBodyToNode("stage1_android-3.plist", "stage1_27.png", "stage1_27", -26);
	this->addBodyToNode("stage1_android-3.plist", "stage1_28.png", "stage1_28", -27);
	this->addBodyToNode("stage1_android-3.plist", "stage1_29.png", "stage1_29", -28);
	this->addBodyToNode("stage1_android-3.plist", "stage1_30.png", "stage1_30", -29);
	this->addBodyToNode("stage1_android-4.plist", "stage1_31.png", "stage1_31", -30);
	this->addBodyToNode("stage1_android-4.plist", "stage1_32.png", "stage1_32", -31);
	this->addBodyToNode("stage1_android-4.plist", "stage1_33.png", "stage1_33", -32);
	this->addBodyToNode("stage1_android-4.plist", "stage1_34.png", "stage1_34", -33);
	this->addBodyToNode("stage1_android-4.plist", "stage1_35.png", "stage1_35", -34);
	this->addBodyToNode("stage1_android-4.plist", "stage1_36.png", "stage1_36", -35);

	*/
}

//<<<<<<< HEAD
void TestGroundScene::menuCloseCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void TestGroundScene::createMaterial(CCSprite** material, b2Body** materialPhysics, char* image, string shape, string plist, CCPoint point) {
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile(plist);
	*material = CCSprite::create(image);
	(*material)->setAnchorPoint(point);

	b2BodyDef bodyDef;				//스프라이트 물리 몸체 생성
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(point.x/PTM_RATIO, point.y/PTM_RATIO);	//물리 몸체의 위치 세팅
	bodyDef.userData = *material;		//물리 몸체에 스프라이트 씌우기
	
	b2Body* body = world_->CreateBody(&bodyDef);	
	(*materialPhysics) = body;

	GB2ShapeCache* sc = GB2ShapeCache::sharedGB2ShapeCache();
	
	sc->addFixturesToBody(body, shape);
	(*material)->setAnchorPoint(sc->anchorPointForShape(shape));
	this->addChild(*material);
}

void TestGroundScene::createMaterialStatic(CCSprite** material, b2Body** materialPhysics, char* image, string shape, string plist, CCPoint point) {
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile(plist);
	(*material) = CCSprite::create(image);
	(*material)->setAnchorPoint(point);

	b2BodyDef bodyDef;				//스프라이트 물리 몸체 생성
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(point.x/PTM_RATIO, point.y/PTM_RATIO);	//물리 몸체의 위치 세팅
	bodyDef.userData = (*material);		//물리 몸체에 스프라이트 씌우기
	
	b2Body* body = world_->CreateBody(&bodyDef);	
	(*materialPhysics) = body;

	GB2ShapeCache* sc = GB2ShapeCache::sharedGB2ShapeCache();
	
	sc->addFixturesToBody(body, shape);
	(*material)->setAnchorPoint(sc->anchorPointForShape(shape));
	this->addChild(*material);
}

void TestGroundScene::movePlayer(float f) {
	//states 0:정지 1:앞 2:뒤 3:점프 4:데드

	if(states!=4){

		if(myContactListener->checkJump==false){
			if(clickLayer->getJoystick()->getVelocity().x > 0) {
				if(states!=1){
					stateTime=0;
				}
				b2Vec2 force = player->GetLinearVelocity();
				force.x = 5.0f;
				player->SetLinearVelocity(force);

				this->headingForward();

				states=1;
				stateTime++;
			}

			else if(clickLayer->getJoystick()->getVelocity().x < 0) {
				if(states!=2){
					stateTime=0;
				}
				b2Vec2 force = player->GetLinearVelocity();
				force.x = -5.0f;
				player->SetLinearVelocity(force);

				this->headingBackward();
				states=2;
				stateTime++;
			}
			else if(clickLayer->getJoystick()->getVelocity().x == 0) {

				if(states==1){
					CCSprite *spriteData =(CCSprite *)player->GetUserData();
					this->removeChild(spriteData,true);
					CCSprite *sprite =CCSprite::create("stand-android.png");	
					sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
					this->addChild(sprite);
					player->SetUserData(sprite);
				}
				else if(states==2){
					CCSprite *spriteData =(CCSprite *)player->GetUserData();
					this->removeChild(spriteData,true);
					CCSprite *sprite =CCSprite::create("stand-android.png");	
					sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
					sprite->setFlipX(true);
					this->addChild(sprite);
					player->SetUserData(sprite);
				}
				b2Vec2 force = player->GetLinearVelocity();
				force.x = 0.0f;
				player->SetLinearVelocity(force);

				states=0;
			}

			if (clickLayer->getJoystick()->getVelocity().y > 0.4) {
				Jump();
			}
		}
		else{
			states=3;

			if(clickLayer->getJoystick()->getVelocity().x >= 0){
				if(states!=3){
					stateTime=0;
				}
				this->jumpingForward();
			}
			else{
				if(states!=3){
					stateTime=0;
				}
				this->jumpingBackward();
			}
		}
	}
	if(states==4){
		//dead Motion
		deadMotion();
	}

	playerSprite = (CCSprite*) player->GetUserData();
	CCRect myBoundary = CCRectMake(0, 0, IMG_WIDTH*36, winSize.height);
	this->runAction(CCFollow::create(playerSprite, myBoundary));
}

void TestGroundScene::createPlayer() {
	player=addPlayerShape(ccp(winSize.width/2,584),"stand-android");
	player->SetFixedRotation(true);
}

b2Body* TestGroundScene::addPlayerShape(CCPoint point,const char* spriteName){
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("playershapefs.plist");

	string name=spriteName;
	char img_name[20]={0};
	sprintf(img_name,"%s.png",name.c_str());

	CCSprite *pHead = CCSprite::create(img_name);
	pHead->setPosition(point);

	this->addChild(pHead);
	
	b2BodyDef headDef;
	headDef.type=b2_dynamicBody;

	headDef.position.Set(point.x/PTM_RATIO,point.y/PTM_RATIO);
	headDef.userData=pHead;
	b2Body* body=this->getWorld()->CreateBody(&headDef);
	GB2ShapeCache *sc =GB2ShapeCache::sharedGB2ShapeCache();
	sc->addFixturesToBody(body,name);
	pHead->setAnchorPoint(sc->anchorPointForShape(name));

	return body;
}

void TestGroundScene::headingForward(){

	if(stateTime==0){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("run1-android.png");	
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==10){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("run2-android.png");	
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==20){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("run3-android.png");	
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==30){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("run4-android.png");	
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==40){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("run5-android.png");	
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==49){
		stateTime=0;
	}
}

void TestGroundScene::headingBackward(){

	
	if(stateTime==0){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("run1-android.png");
		sprite->setFlipX(true);
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==10){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("run2-android.png");	
		sprite->setFlipX(true);
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==20){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("run3-android.png");	
		sprite->setFlipX(true);
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==30){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("run4-android.png");	
		sprite->setFlipX(true);
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==40){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("run5-android.png");	
		sprite->setFlipX(true);
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==49){
		stateTime=0;
	}
}
void TestGroundScene::jumpingForward(){

	
	if(stateTime==0){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("jump1-android.png");	
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==10){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("jump2-android.png");	
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==20){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("jump3-android.png");	
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==30){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("jump4-android.png");	
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==40){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("jump5-android.png");	
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==49){
		stateTime=0;
	}
	stateTime++;
}

void TestGroundScene::jumpingBackward(){

	
	if(stateTime==0){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("jump1-android.png");
		sprite->setFlipX(true);
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==10){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("jump2-android.png");	
		sprite->setFlipX(true);
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==20){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("jump3-android.png");	
		sprite->setFlipX(true);
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==30){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("jump4-android.png");	
		sprite->setFlipX(true);
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==40){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("jump5-android.png");	
		sprite->setFlipX(true);
		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==49){
		stateTime=0;
	}
	stateTime++;
}
void TestGroundScene::deadMotion(){

	
	if(stateTime==0){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("die1-android.png");

		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==10){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("die2-android.png");	

		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==20){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("die3-android.png");	

		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==30){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("die4-android.png");	

		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}
	else if(stateTime==40){
		CCSprite *spriteData =(CCSprite *)player->GetUserData();
		this->removeChild(spriteData,true);
		CCSprite *sprite =CCSprite::create("die5-android.png");	

		sprite->setPosition(ccp(player->GetPosition().x/PTM_RATIO,player->GetPosition().y/PTM_RATIO));
		this->addChild(sprite);
		player->SetUserData(sprite);
	}

	stateTime++;
}


void TestGroundScene::Jump(){
	if(myContactListener->checkJump==false){
		if(clickLayer->getJoystick()->getVelocity().x > 0.3) {	///대각선 앞으로 누를때
			b2Vec2 force = player->GetLinearVelocity();
			force.y = 7.0f;
			force.x -= 1.0f;
			player->SetLinearVelocity(force);
			myContactListener->checkJump = true;

		}
		else if(clickLayer->getJoystick()->getVelocity().x < -0.3) {		//대각선 뒤로 누를때
			b2Vec2 force = player->GetLinearVelocity();
			force.y = 7.0f;
			force.x += 1.0f;
			player->SetLinearVelocity(force);
			myContactListener->checkJump = true;
		}
		else {															//제자리 점프
			b2Vec2 force = player->GetLinearVelocity();
			force.y = 7.0f;
			force.x = 0.0f;
			player->SetLinearVelocity(force);
			myContactListener->checkJump = true;
		}
	}
}

void TestGroundScene::addBodyToNode(string plistName, char* imgName, string shapeName, int order) {
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile(plistName);
	CCSprite *pBackGround = CCSprite::create(imgName);
	pBackGround->setAnchorPoint(ccp(order,0));

	b2BodyDef bodyDef;				//스프라이트 물리 몸체 생성
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set((IMG_WIDTH*(-order))/PTM_RATIO, 0.0f);	//물리 몸체의 위치 세팅
	bodyDef.userData = pBackGround;		//물리 몸체에 스프라이트 씌우기
		
	b2Body* body = world_->CreateBody(&bodyDef);
	this->bodyQueue.push(body);
	
	GB2ShapeCache* sc = GB2ShapeCache::sharedGB2ShapeCache();
		
	sc->addFixturesToBody(body, shapeName);
	pBackGround->setAnchorPoint(sc->anchorPointForShape(shapeName));
	
	this->addChild(pBackGround, 0, (-order)+1);
}

void TestGroundScene::createTiger() {
	this->createMaterial(&tiger, &tigerPhysics, "tiger-run1.png", "tiger-run1", "ground.plist", ccp(IMG_WIDTH*6+87, 515));
	tiger->setFlipX(true);
    
}

void TestGroundScene::tigerAttack() {
	this->tigerForward();
	tigerTime++;
	b2Vec2 force = tigerPhysics->GetLinearVelocity();
	force.x = 5.9f;
	tigerPhysics->SetLinearVelocity(force);
}

void TestGroundScene::tigerForward() {
	if(tigerTime == 1){
		CCSprite* spriteData1 = (CCSprite*)tigerPhysics->GetUserData();
		CCSprite* spriteData2 = CCSprite::create("tiger-run1.png");
		spriteData2->setPosition(ccp(tigerPhysics->GetPosition().x/PTM_RATIO,tigerPhysics->GetPosition().y/PTM_RATIO));
		tigerPhysics->SetUserData(spriteData2);
		this->addChild(spriteData2);
		this->removeChild(spriteData1,true);
	}
	else if(tigerTime == 11){
		CCSprite* spriteData1 = (CCSprite*)tigerPhysics->GetUserData();
		CCSprite* spriteData2 = CCSprite::create("tiger-run2.png");
		spriteData2->setPosition(ccp(tigerPhysics->GetPosition().x/PTM_RATIO,tigerPhysics->GetPosition().y/PTM_RATIO));
		tigerPhysics->SetUserData(spriteData2);
		this->addChild(spriteData2);
		this->removeChild(spriteData1,true);
	}
	else if(tigerTime == 21){
		CCSprite* spriteData1 = (CCSprite*)tigerPhysics->GetUserData();
		CCSprite* spriteData2 = CCSprite::create("tiger-run3.png");
		spriteData2->setPosition(ccp(tigerPhysics->GetPosition().x/PTM_RATIO,tigerPhysics->GetPosition().y/PTM_RATIO));
		tigerPhysics->SetUserData(spriteData2);
		this->addChild(spriteData2);
		this->removeChild(spriteData1,true);
	}
	else if(tigerTime == 31){
		CCSprite* spriteData1 = (CCSprite*)tigerPhysics->GetUserData();
		CCSprite* spriteData2 = CCSprite::create("tiger-run4.png");
		spriteData2->setPosition(ccp(tigerPhysics->GetPosition().x/PTM_RATIO,tigerPhysics->GetPosition().y/PTM_RATIO));
		tigerPhysics->SetUserData(spriteData2);
		this->addChild(spriteData2);
		this->removeChild(spriteData1,true);
	}
	else if(tigerTime == 40){
		tigerTime=0;
	}
}

void TestGroundScene::removeGround(int count) {//////////////땅삭제
	//this->removeChildByTag(count-2);
	//b2Body* body = this->bodyQueue.front();
	//this->world_->DestroyBody(body);
}

CCPoint TestGroundScene::getSavePoint() {
	CCPoint point = playerSprite->getPosition();
	CCLog("position : (%f, %f)", &point.x, point.y);
	return point;
}

bool ClickButton::init() {
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	joystick = NULL;

	joystick = Joystick::create();////////////조이스틱 생성
    this->addChild(joystick,2);
	this->setTouchEnabled(true);
	this->createControlButton();
	
	return true;
}

void ClickButton::createControlButton() {
	this->setControlButton("CloseNormal.png");
	this->getControlButton()->setPosition(ccp(IMG_WIDTH-(this->getControlButton()->getContentSize().width/2), this->getControlButton()->getContentSize().height/2));
	this->addChild(this->getControlButton());
}

void ClickButton::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event) {
	CCSetIterator it = touches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	this->setIsControlPressed(false);

	if(this->isTouchInside(this->getControlButton(), touch) == true) {			//스프라이트 내부에 터치가 있으면 안눌린 화살표 이미지를 안보이게하고 눌렷다고 표시
		this->getControlButton()->setVisible(false);
		this->setIsControlPressed(true);
	}
}

void ClickButton::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	if(this->getIsControlPressed() == true) {		//눌림이 끝나면 멈추면서 화살표 정상
		this->getControlButton()->setVisible(true);
		this->setIsControlPressed(false);
	}
}

bool ClickButton::isTouchInside(CCSprite* sprite, CCTouch* touch) {
	CCPoint touchPoint = touch->getLocation();

	CCRect rect = sprite->boundingBox();
	if(rect.containsPoint(touchPoint))	///////누르는 점이 스프라이트 내부이면
		return true;
	else
		return false;
}
