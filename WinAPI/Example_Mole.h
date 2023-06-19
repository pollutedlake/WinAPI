#pragma once
#include "GameNode.h"

class Example_Mole : public GameNode
{
private:
	RECT rc;
	POINT pt;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	Example_Mole() {}
	~Example_Mole() {}
};

