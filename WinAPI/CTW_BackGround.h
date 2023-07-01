#pragma once
#include "GameNode.h"

class CTW_BackGround : public GameNode
{
private:
	GImage* _backGround;
	RECT _rc[7];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	RECT* getRect() {return _rc; }

	CTW_BackGround() {}
	~CTW_BackGround() {}
};

