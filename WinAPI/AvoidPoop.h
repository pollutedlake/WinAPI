#pragma once
#include "GameNode.h"
#include "AP_Player.h"
#include "AP_Poop.h"

class AvoidPoop : public GameNode
{
private:
	AP_Player* player;
	vector<AP_Poop*> poops;
	int deltaTime;
	int dropTime;
	int scene;
	int score;
	int scoreTime;

public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void release(void);
	virtual void render(HDC hdc);

	AvoidPoop() {}
	virtual ~AvoidPoop() {}
};

