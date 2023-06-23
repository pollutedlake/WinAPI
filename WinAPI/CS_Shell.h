#pragma once
#include "GameNode.h"

class CS_Shell : public GameNode
{
private:
	POINT position;
	float speedX, speedY;
	bool active;
	bool gravity;
	float gravitySpeed;
	float angle;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void setActive(bool _active) { active = _active; }
	void toggleGravity() { gravity = !gravity; }
	bool getActive() { return active; }
	POINT getPosition() { return position; }
	float getSpeedX() { return speedX; }
	float getSpeedY() { return speedY; }
	float getAngle() {return angle;}
	void setSpeedX(float _speedX) { speedX = _speedX; }
	void setSpeedY(float _speedY) { speedY = _speedY; }
	void setAngle(float _angle) {angle = _angle;}

	void fire(LONG _positionX, LONG _positionY, float _angle);
	void move(float _moveX, float _moveY);
	bool collisionCheck(POINT _otherPos);

	CS_Shell() {}
	virtual ~CS_Shell() {};
};

