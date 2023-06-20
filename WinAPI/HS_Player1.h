#pragma once
#include "HS_Player.h"

class HS_Player1 : public HS_Player
{
private:
	int chargeTime = 0;
	bool chargeShot;
	int chargeShotTime = 0;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(int _x, int _y);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void release(void);
	virtual bool shoot();
	virtual bool useSkill1();
	virtual bool useSkill2();
};

