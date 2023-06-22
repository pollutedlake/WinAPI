#pragma once
#include "GameNode.h"

// 0. ����� ���� Ŭ����
// 1. �ֻ��� ������ Ŭ����
// 2. �븮�� (���� �°� ����ϴ� Ŭ����)

// ���� ����

class MainGame : public GameNode
{
private:
	GImage* _bgImage;
	GImage* _plImage;
	RECT _rc;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void fireBullet(void);

	MainGame() {}
	~MainGame() {}
};