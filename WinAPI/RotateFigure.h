#pragma once
#include "GameNode.h"

class RotateFigure : public GameNode
{
private:
	POINT rectCenter;
	XFORM xForm;
	float angle;
public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void release(void);
	virtual void render(HDC hdc);

	RotateFigure () {};
	virtual ~RotateFigure() {};
};

