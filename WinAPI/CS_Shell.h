#pragma once
#include "GameNode.h"

class CS_Shell : public GameNode
{
private:
	POINT position;
	float speedX, speedY;
	bool active;
	bool gravity;

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
	void setSpeedX(float _speedX) { speedX = _speedX; }
	void setSpeedY(float _speedY) { speedY = _speedY; }

	void fire(LONG _positionX, LONG _positionY, float _speedX, float _speedY);
	bool collisionCheck(POINT _otherPos);

	CS_Shell() {}
	virtual ~CS_Shell() {};
};

