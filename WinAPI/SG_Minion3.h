#pragma once
#include "SG_Enemy.h"

class SG_Minion3 : public SG_Enemy
{
private:
	int _count;
	int _rndSpeed;

public:

	void move(void);

	SG_Minion3();
	SG_Minion3(int rndSpeed);
	~SG_Minion3();
};

