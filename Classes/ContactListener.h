#ifndef __CONTACT_LISTENER_H__
#define __CONTACT_LISTENER_H__
#include "cocos2d.h"
//#include "Box2D\Box2D.h"
#include "Box2D\Box2D.h"

using namespace cocos2d;

class ContactListener : public b2ContactListener {
public:
	ContactListener ();
	~ContactListener ();

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
	bool mineCheck;
	bool missileCheck;
	bool flightMissileCheck;
	bool checkLadder;
	bool checkJump;
	b2Fixture* FixA;
	b2Fixture* FixB;
	b2Body* mineBody;
	b2Body* contactBody;
};

#endif