#pragma once
#include "Stdafx.h"
#include "GameNode.h"
#include "Card.h"

// 0. 상속을 받은 클래스
// 1. 최상위 관리자 클래스
// 2. 대리자 (오류 맞고 사망하는 클래스)
class FindCardPair : public GameNode
{
private:
	Card* cards[20];
	BOOL bCardPairCheck = FALSE;
	int count = 0;
	HBRUSH oldCardColor;
	int reverseTime = 20;
	int deltaTime = 0;

	Card* selectCard[2];
	vector<Card*> openCards;

	POINT pt;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void cheat1();
	void cheat2();

	virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	FindCardPair() {}
	~FindCardPair() {}
};

