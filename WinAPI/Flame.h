#pragma once
#include "GameNode.h"

// ���ȭ ( ��ü�� ������ ��ǰ?)
// �� ����

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