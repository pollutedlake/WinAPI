#pragma once
#include "GameNode.h"
#include "SG_Enemy.h"
#include "Bullets.h"

class Rocket;

class EnemyManager : public GameNode
{
private:
	typedef vector<SG_Enemy*> vEnemy;
	typedef vector<SG_Enemy*>::iterator viEnemy;
	//typedef vector<tagEffect>

private:
	vEnemy _vMinion;
	viEnemy _viMinion;
	Bullet* _bullet;
	Rocket* _rocket;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void removeMinion(int arrNum);

	void minionBulletFire(void);
	void collision(void);

	vector<SG_Enemy*> getMinions(void) {return _vMinion;}
	Bullet* getBullet(void) {return _bullet;}
	void setRocketMemoryAddress(Rocket* rk) {_rocket = rk;}

	EnemyManager();
	~EnemyManager();
};

