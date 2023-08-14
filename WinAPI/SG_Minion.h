#pragma once
#include "SG_Enemy.h"


class SG_Minion : public SG_Enemy
{
private:
	float _angle;
	int _count;
	int _radius;

public:

	void move(void);


	SG_Minion();
	~SG_Minion();
};

