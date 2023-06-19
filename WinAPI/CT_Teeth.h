#pragma once
#include "GameNode.h"

class CT_Teeth : public GameNode
{
private:
	bool isPressDown;
	RECT rc;
	POINT center;

public:
	virtual HRESULT init(void);
	HRESULT init(POINT _center);
	virtual void update(void);
	void update(POINT _pt);
	virtual void release(void);
	virtual void render(HDC hdc);

	void setIsPressDown(bool _isPressDown) { isPressDown = _isPressDown; }
	bool getIsPressDown() { return isPressDown; }

	CT_Teeth() {}
	virtual ~CT_Teeth() {}
};

