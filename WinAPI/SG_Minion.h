#pragma once
#include "SG_Enemy.h"


class SG_Minion : public SG_Enemy
{
private:
	float _angle;
	int _count;
	int _radius;

public:
	HRESULT init(const char* imageName, POINT center, int radius, float angle);
	void move(void);


	SG_Minion();
	~SG_Minion();
};

