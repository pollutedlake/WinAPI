#pragma once
#include "GameNode.h"

class SB_Player : public GameNode
{
private:
	POINT position;
public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void release(void);

	POINT getPosition() { return position; }

	SB_Player() {}
	virtual ~SB_Player() {}
};

