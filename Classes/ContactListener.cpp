#include "ContactListener.h"

ContactListener::ContactListener() {
	mineCheck = false;
	missileCheck = false;
	flightMissileCheck = false;
	checkLadder=false;
	checkJump=false;
}
ContactListener::~ContactListener() {
}

void ContactListener::BeginContact(b2Contact *contact) {
	
	FixA = contact->GetFixtureA();
	FixB = contact->GetFixtureB();

	if((FixA->GetFilterData().groupIndex == -1 && 0 == FixB->GetFilterData().groupIndex) || (FixA->GetFilterData().groupIndex == 0 && -1 == FixB->GetFilterData().groupIndex) ||
		(FixA->GetFilterData().groupIndex == 3 && 0 == FixB->GetFilterData().groupIndex) || (FixA->GetFilterData().groupIndex == 0 && 3 == FixB->GetFilterData().groupIndex)) {
		mineCheck = true;
		if(FixB->GetFilterData().groupIndex == 0) {
			mineBody = FixB->GetBody();
			contactBody = FixA->GetBody();
		}
		else if(FixA->GetFilterData().groupIndex == 0) {
			mineBody = FixA->GetBody();
			contactBody = FixB->GetBody();
		}
	}
	if((FixA->GetFilterData().groupIndex == 1 && FixB->GetFilterData().groupIndex == -8) ||
		(FixA->GetFilterData().groupIndex == -8 && FixB->GetFilterData().groupIndex == 1))
		missileCheck = true;
	else if((FixA->GetFilterData().groupIndex == 1 && FixB->GetFilterData().groupIndex == 0) ||
		(FixA->GetFilterData().groupIndex == 0 && FixB->GetFilterData().groupIndex == 1))
		missileCheck = true;
	if((FixA->GetFilterData().groupIndex == 4 && FixB->GetFilterData().groupIndex == -8) ||
		(FixA->GetFilterData().groupIndex == -8 && FixB->GetFilterData().groupIndex == 4))
		flightMissileCheck = true;
	else if((FixA->GetFilterData().groupIndex == 4 && FixB->GetFilterData().groupIndex == 0) ||
		(FixA->GetFilterData().groupIndex == 0 && FixB->GetFilterData().groupIndex == 4))
		flightMissileCheck = true;
	if((FixA->GetFilterData().groupIndex==-1 && FixB->GetFilterData().groupIndex==-3) || (FixA->GetFilterData().groupIndex==-3 && FixB->GetFilterData().groupIndex==-1)){
		checkLadder=true;
	}
	if((FixA->GetFilterData().groupIndex==-1 && FixB->GetFilterData().groupIndex==-8) || (FixA->GetFilterData().groupIndex==-8 && FixB->GetFilterData().groupIndex==-1) ||
		(FixA->GetFilterData().groupIndex==-1 && FixB->GetFilterData().groupIndex==-7) || (FixA->GetFilterData().groupIndex==-7 && FixB->GetFilterData().groupIndex==-1) ||
       (FixA->GetFilterData().groupIndex==-1 && FixB->GetFilterData().groupIndex==-6) || (FixA->GetFilterData().groupIndex==-6 && FixB->GetFilterData().groupIndex==-1)){
		checkJump=false;
	}
	
}

void ContactListener::EndContact(b2Contact *contact) {
	b2Fixture *fixA=contact->GetFixtureA();
	b2Fixture *fixB=contact->GetFixtureB();

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();
	if(fixA->GetFilterData().groupIndex==-1 & fixB->GetFilterData().groupIndex==-3){
		checkLadder=false;
	}
	if(fixA->GetFilterData().groupIndex==-1 & fixB->GetFilterData().groupIndex==-8){
		checkJump=true;
	}
}
void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
	
	b2Fixture *fixA=contact->GetFixtureA();
	b2Fixture *fixB=contact->GetFixtureB();

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();
	if(bodyA->GetType()==b2_dynamicBody || bodyB->GetType()==b2_dynamicBody){
	//	bodyB->ApplyForceToCenter(b2Vec2(1000,1));
	}
	if(fixA->GetFilterData().groupIndex==-1 & fixB->GetFilterData().groupIndex==-2){
	//	bodyB->ApplyForceToCenter(b2Vec2(0,10000));
	}
}
void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) {

	b2Fixture *fixA = contact->GetFixtureA();
	b2Fixture *fixB = contact->GetFixtureB();

	b2Body *bodyA = fixA->GetBody();
	b2Body *bodyB = fixB->GetBody();

	if(bodyA->GetType() == b2_dynamicBody || bodyB->GetType() == b2_dynamicBody) {
	}
}