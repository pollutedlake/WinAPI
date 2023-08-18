#pragma once

class EventListener
{
protected:
	RECT* _colliderRC;
	void(EventListener::*_collisionPtr)();
public:
	virtual void collision() {cout << "¾ÈµÅ" << endl; }
	void (EventListener::*getCollisionPtr())() {return _collisionPtr;}
	void setRect(RECT* rc) {_colliderRC = rc;}
	RECT* getRect() {return _colliderRC;}
};