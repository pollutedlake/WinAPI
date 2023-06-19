#pragma once
#include "GameNode.h"
#include "Card.h"
#include "Example_Mole.h"

// 0. ����� ���� Ŭ����
// 1. �ֻ��� ������ Ŭ����
// 2. �븮�� (���� �°� ����ϴ� Ŭ����)

/*
������ �δ���.......
1. �δ��� + ��
�� Ŭ���� ����..?
	�� ��� ? / Ŭ���� ����? STL?
�� ���� �����ӿ�ũ�� ���ذ� ��

2. ü�� (���� / Ŭ���� / ����ü)

3. ��üȭ
	�� PCH / �Լ� -> ���� ����
*/

enum CURRENT_RECT
{
	CURRENTRECT_A, CURRENTRECT_B,
	CURRENTRECT_C, CURRENTRECT_D,
	CURRENTRECT_E, CURRENTRECT_F,
	CURRENTRECT_G, CURRENTRECT_H,
	CURRENTRECT_NULL
};

class MainGame : public GameNode
{
private:
	Example_Mole* _mole;

	CURRENT_RECT _currentRect;
	RECT _rc[8];
	int _index;					// �δ��� �ε��� (8��)
	int _count;					// Ÿ�̸ӿ� ī��Ʈ
	int _time;					// �����ð� ����
	int _score;					// ����

	bool _bIsSelected;			// 
	bool _bIsOnceCheck;			// 

	POINT pt;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	MainGame() {}
	~MainGame() {}
};

