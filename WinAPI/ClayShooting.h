#pragma once
#include "GameNode.h"
#include "Clay.h"

// 0. ����� ���� Ŭ����
// 1. �ֻ��� ������ Ŭ����
// 2. �븮�� (���� �°� ����ϴ� Ŭ����)
class ClayShooting : public GameNode
{
private:
	POINT pt;
	vector<Clay*> clays;
	int score;
	int deltaTime;
	int nextClayTime;
	int gameTime;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void Shoot(POINT _pt);

	virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	ClayShooting() {}
	~ClayShooting() {}
};


