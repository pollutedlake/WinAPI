#pragma once
#include "GImage.h"

struct Enemy
{
	RECT _rc;
	Enemy()
	{
		int _lane = RND->getInt(3);
		_rc = RectMake(WINSIZE_X / 2 - IMAGEMANAGER->findImage("Enemy")->getWidth() / 2 + (_lane - 1) * IMAGEMANAGER->findImage("RG_BackGround")->getWidth(), - IMAGEMANAGER->findImage("Enemy")->getHeight(), IMAGEMANAGER->findImage("Enemy")->getWidth(), IMAGEMANAGER->findImage("Enemy")->getHeight());
	};
};

class RG_Enemy
{
private:
	GImage* _enemyImg;
	RECT _rc;
	vector<Enemy*> _enemyVector;
	int _frame;
	int _spawnTime;

public:
	HRESULT init(void);
	void release(void);
	void update(int speed, RECT playerRC);
	void render(HDC hdc);

	RG_Enemy() {}
	~RG_Enemy() {}
};

