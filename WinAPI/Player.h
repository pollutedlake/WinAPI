#pragma once
#include "GameNode.h"

#define WIDTH			40
#define HEIGHT			40
#define PLAYER_SPEED	5		

class Player : public GameNode
{
public:
	POINT position;
	RECT rc;

	virtual HRESULT init(void);
	virtual HRESULT init(int _x, int _y);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void release();
};

