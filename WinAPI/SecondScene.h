#pragma once
#include "GameNode.h"
class SecondScene : public GameNode
{
private:
	int _offsetX, _offsetY;
	int _bgSpeed;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};