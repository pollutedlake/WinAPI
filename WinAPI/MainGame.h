#pragma once
#include "GameNode.h"
#include "Card.h"

// 0. ����� ���� Ŭ����
// 1. �ֻ��� ������ Ŭ����
// 2. �븮�� (���� �°� ����ϴ� Ŭ����)
class MainGame : public GameNode
{
private:
	Card* cards[20];
	BOOL bCardPairCheck = FALSE;
	int count = 0;
	HBRUSH oldCardColor;
	int reverseTime  = 2000;
	int deltaTime = 0;
	Card* selectCard[2];


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	MainGame() {}
	~MainGame() {}
};

