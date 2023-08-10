#pragma once
#include "GameNode.h"

// 모듈화 ( 교체가 가능한 부품?)
// ㄴ 내일

class Flame : public GameNode
{
private:
	GImage* _image;
	int _count;
	int _boosterIndex;
	int _x;
	int _y;
	int width;
	int height;

public:

	HRESULT init(void);
	void release(void);
	void update(RECT rc);
	void render();

	Flame() {}
	~Flame() {}
};