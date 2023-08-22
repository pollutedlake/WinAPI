#pragma once
#include "GameNode.h"
#include "SG_Enemy.h"

//struct tagEffect
//{
//	GImage* img;
//	RECT rc;
//	float x, y;
//	int count;
//};

class EnemyManager : public GameNode
{
private:
	typedef vector<SG_Enemy*> vEnemy;
	typedef vector<SG_Enemy*>::iterator viEnemy;
	//typedef vector<tagEffect>

private:
	vEnemy _vMinion;
	viEnemy _viMinion;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMinion(void);
	void removeMinion(int arrNum);

	vector<SG_Enemy*> getMinions(void) {return _vMinion;}

	EnemyManager();
	~EnemyManager();
};

