#pragma once
#include "SG_Enemy.h"

class SG_Minion2 : public SG_Enemy
{
private:
	float _angle;
	int _count;
	int _maxRadius;
	int _radius;
	//bool _gather;
	//int _radiusSpeed;

public:
	void move(void);

	SG_Minion2();
	~SG_Minion2();
};

