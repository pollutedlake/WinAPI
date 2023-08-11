#pragma once
#include "GameNode.h"

// 모듈화 ( 교체가 가능한 부품?)
// ㄴ 내일

#define FLAME_COUNT 4.0f

// 추상
class Flame : public GameNode
{
private:
	GImage* _image;
	RECT _rc;

	float _flameTick;
	float* _x;
	float* _y;
	float _offsetY;

public:

	HRESULT init(const char* imageName, float* x, float* y, float offsetY);
	void release(void);
	void update();
	void render();

	Flame() {}
	~Flame() {}
};