#pragma once
#include "Rocket.h"

// ���ȭ ( ��ü�� ������ ��ǰ?)
// �� ����

class Flame : public Rocket
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