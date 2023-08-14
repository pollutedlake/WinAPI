#pragma once
#include "GameNode.h"
#include "SG_Enemy.h"

class EnemyManager : public GameNode
{
private:
	typedef vector<SG_Enemy*> vEnemy;
	typedef vector<SG_Enemy*>::iterator viEnemy;

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);

	EnemyManager();
	~EnemyManager();
};

