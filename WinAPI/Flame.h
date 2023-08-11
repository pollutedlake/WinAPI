#pragma once
#include "GameNode.h"

// ���ȭ ( ��ü�� ������ ��ǰ?)
// �� ����

#define FLAME_COUNT 4.0f

// �߻�
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