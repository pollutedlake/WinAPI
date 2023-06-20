#pragma once
#include "Player.h"

class Player2 : public Player
{
private:

public:
	virtual HRESULT init(void);
	virtual HRESULT init(int _x, int _y);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void release(void);
};

