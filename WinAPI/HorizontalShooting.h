#pragma once
#include "GameNode.h"
#include "HS_Player1.h"
#include "HS_Player2.h"
#include "HS_Bullet.h"

#define BULLET_MAX	90
#define PLAYER_SPEED 5

struct tagBullet
{
	RECT rc;
	bool fire;
};

class HorizontalShooting : public GameNode
{
private:
	HS_Bullet bullets[BULLET_MAX];
	HS_Player1* player1;
	HS_Player2* player2;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void fireBullet(int player, BulletType type, HS_Bullet* sprinkler);
	void collisionCheck(HS_Bullet* bullet);
	void useSkill(int player, int skillN);

	HorizontalShooting() {}
	~HorizontalShooting() {}
};
