#pragma once
#include "GameNode.h"
#include "FWP_Paint.h"

class FindWrongPaint : public GameNode
{
private:
	FWP_Paint* _stagePaint[2];
	int _stage;
	int _time;
	POINT wongPoint[2][5];
	bool gameEnd = false;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	FindWrongPaint() {};
	virtual ~FindWrongPaint() {};
};

