#pragma once
#include "GameNode.h"

class AP_Player : public GameNode
{
private:
	POINT position;
	int speed;
	int dirX;
public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void release(void);

	AP_Player() { }
	virtual ~AP_Player() { }
};

