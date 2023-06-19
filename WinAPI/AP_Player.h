#pragma once
#include "GameNode.h"

class AP_Player : public GameNode
{
private:
	POINT position;
	int speed;
	int dirX;
	bool die;
public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void release(void);

	POINT getPosition() {return position;}
	void setDie(bool _die) {die = _die;}
	bool getDie() {return die;}

	AP_Player() { }
	virtual ~AP_Player() { }
};

