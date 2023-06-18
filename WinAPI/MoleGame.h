#pragma once
#include "GameNode.h"
#include "Mole.h"

// 0. 상속을 받은 클래스
// 1. 최상위 관리자 클래스
// 2. 대리자 (오류 맞고 사망하는 클래스)
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

