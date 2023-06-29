#pragma once
#include "GameNode.h"

class ZeroCombo : public GameNode
{
private:
	GImage* _zero;
	int _count;
	int _index;
	bool _attack;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	ZeroCombo() {}
	~ZeroCombo() {}
};

