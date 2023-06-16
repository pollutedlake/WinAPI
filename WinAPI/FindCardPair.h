#pragma once
#include "Stdafx.h"
#include "GameNode.h"
#include "Card.h"

// 0. ����� ���� Ŭ����
// 1. �ֻ��� ������ Ŭ����
// 2. �븮�� (���� �°� ����ϴ� Ŭ����)
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

