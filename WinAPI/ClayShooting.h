#pragma once
#include "GameNode.h"
#include "Clay.h"

// 0. 상속을 받은 클래스
// 1. 최상위 관리자 클래스
// 2. 대리자 (오류 맞고 사망하는 클래스)
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


