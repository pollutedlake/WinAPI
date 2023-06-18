#pragma once
#include "GameNode.h"
#include "Mole.h"

// 0. ����� ���� Ŭ����
// 1. �ֻ��� ������ Ŭ����
// 2. �븮�� (���� �°� ����ϴ� Ŭ����)
class MoleGame : public GameNode
{
private:
	int score;
	int moleApperTime;
	Mole* moles[9];
	HBITMAP moleBitmap, oldBitmap, blindBitmap, backBit, oldBackBit;
	HDC memDC, tempDC, backDC;
	RECT bufferRT;
	BITMAP bit;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	MoleGame() {}
	~MoleGame() {}
};

