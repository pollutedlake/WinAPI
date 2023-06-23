#pragma once
#include "GameNode.h"

class CS_Cannon : public GameNode
{
private:
	POINT barrel;
	float angle;
	bool autoMove;
	float dir;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	float getAngle() { return angle; }

	CS_Cannon() {};
	virtual ~CS_Cannon() {};
};

