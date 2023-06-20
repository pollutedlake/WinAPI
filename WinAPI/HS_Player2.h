#pragma once
#include "HS_Player.h"

class HS_Player2 : public HS_Player
{
private:
	int skill1Time;
	int count;
	bool skill1;
public:
	virtual HRESULT init(void);
	virtual HRESULT init(int _x, int _y);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void release(void);
	virtual bool shoot();
	virtual bool useSkill1();
	virtual bool useSkill2();

	bool getSkill1() {return skill1;}
};

