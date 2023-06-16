#include "Stdafx.h"
#include "MoleGame.h"

/*
과제 1. 두더지 게임
- 두더지의 수는 최소 8마리부터 시작한다.

- 화면에 현재 점수를 표기한다.

- 예외처리 :
ㄴ 두더지를 한번 클릭하면 점수 증가
ㄴ 이후 두더지가 사라질때까지 재클릭을 해도 점수가 오르면 안된다.
*/

HRESULT MoleGame::init(void)
{
	GameNode::init();

	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);

	return S_OK;
}

void MoleGame::release(void)
{
	GameNode::release();
}

void MoleGame::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		rc.top += 3;
		rc.bottom += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		rc.top -= 3;
		rc.bottom -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		rc.left -= 3;
		rc.right -= 3;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		rc.left += 3;
		rc.right += 3;
	}
}

void MoleGame::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
}

LRESULT MoleGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_DESTROY:                // 소멸자
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}