#pragma once
#include "GImage.h"

class RG_BackGround
{
private:
	GImage* _backGround;
	int _bgSpeedY;
	int _score;

public:
	HRESULT init(void);
	void release(void);
	void update(int speed);
	void render(HDC hdc);

	RG_BackGround() {}
	virtual ~RG_BackGround() {}
};

