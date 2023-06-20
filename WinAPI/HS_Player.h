#pragma once
#include "GameNode.h"

#define PLAYERWIDTH			40
#define PLAYERHEIGHT		40
#define PLAYER_SPEED		5		

class HS_Player : public GameNode
{
protected:
	POINT position;
	RECT rc;
	int hp;
	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH orangeBrush = CreateSolidBrush(RGB(255, 127, 39));
	HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(int _x, int _y);
	virtual void update();
	void render(HDC hdc);
	void release();
	virtual bool shoot();
	bool getDamaged(POINT _pt, int _r);
	virtual bool useSkill1();
	virtual bool useSkill2();

	POINT getPosition() { return position;}
};

