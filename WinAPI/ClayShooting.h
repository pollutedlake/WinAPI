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
	int point;
	int deltaTime;
	int nextClayTime;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	virtual LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	ClayShooting() {}
	~ClayShooting() {}
};


