#pragma once
#include "GameNode.h"
class AP_Poop : public GameNode
{
private:
	POINT position;
	int speed;
	POINT dir;
	bool isActive;

public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void release(void);

	bool getIsActive() { return isActive; }
	POINT getPosition() {return position;}

	AP_Poop() { }
	virtual ~AP_Poop() { }
};

