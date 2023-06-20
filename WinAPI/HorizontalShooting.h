#pragma once
#include "GameNode.h"
#include "Player1.h"
#include "Player2.h"

#define BULLET_MAX 10
#define PLAYER_SPEED 5

struct tagBullet
{
	RECT rc;
	bool fire;
};

class HorizontalShooting : public GameNode
{
private:
	tagBullet _bullet1[BULLET_MAX];
	tagBullet _bullet2[BULLET_MAX];

	RECT playerRC1;
	RECT playerRC2;
	RECT hpRC1;
	RECT hpRC2;
	int hp1[3];
	int hp2[3];
	Player* player1;
	Player* player2;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void fireBullet(int player);
	void useSkill(int player, int skill);

	HorizontalShooting() {}
	~HorizontalShooting() {}
};
