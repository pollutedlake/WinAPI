#pragma once
#include "GameNode.h"

class AnalogClock : public GameNode
{
private:
	int _hour, _minute, _second;
	SYSTEMTIME _st;

public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void release();

	AnalogClock() {};
	virtual ~AnalogClock() {};
};

