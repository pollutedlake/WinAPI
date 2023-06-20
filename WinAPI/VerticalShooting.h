#pragma once
#include "GameNode.h"

#define BULLET_MAX 10
#define PLAYER_SPEED 5
// X -> X -> O
#define ENEMY_MAX 80

struct tagBullet
{
	RECT rc;
	bool fire;
};

struct tagEnemy
{
	RECT rc;
	int speed;
	bool die;
};

class VerticalShooting : public GameNode
{
private:
	tagBullet _bullet[BULLET_MAX];
	tagEnemy _enemy[ENEMY_MAX];

	RECT _rc;
	RECT hpRc;
	int hp[3];
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void fireBullet(void);

	VerticalShooting() {}
	~VerticalShooting() {}
};

