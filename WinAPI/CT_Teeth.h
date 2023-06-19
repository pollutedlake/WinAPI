#pragma once
#include "GameNode.h"

class CT_Teeth : public GameNode
{
private:
	bool isPressDown;
	RECT rc;
public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void release(void);
	virtual void render(HDC hdc);

	void setIsPressDown(bool _isPressDown) { isPressDown = _isPressDown; }
	bool getIsPressDown() { return isPressDown; }

	CT_Teeth() {}
	virtual ~CT_Teeth() {}
};

