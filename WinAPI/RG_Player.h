#pragma once
#include "GImage.h"
class RG_Player
{
private:
	GImage* _player;
	GImage* _dashBoard;
	RECT _rc;
	int _lane;
	float _speed;
	bool _shield;
	int _frame;
	int _shieldTime;

public:
	HRESULT inint(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	float getSpeed() { return _speed; }
	RECT getRect() { return _rc; }

	RG_Player() {}
	virtual ~RG_Player() {}
};