#pragma once
#include "GameNode.h"
class SB_Bullet : public GameNode
{
private:
	POINT position;
	POINT dir;
	int velocity;
	bool isActive;
public:
	virtual HRESULT init(void);
	HRESULT init(int playerPosX);
	virtual void update(void);
	virtual void release(void);
	virtual void render(HDC hdc);

	bool getIsActive() { return isActive; }

	SB_Bullet();
	virtual ~SB_Bullet() {};
};

