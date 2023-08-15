#pragma once
#include "SG_Enemy.h"

class SG_Minion3 : public SG_Enemy
{
private:
	int _count;
	int _rndSpeed;

public:
	virtual HRESULT init(const char* imageName, POINT position, int rndSpeed);

	void move(void);

	SG_Minion3();
	~SG_Minion3();
};

