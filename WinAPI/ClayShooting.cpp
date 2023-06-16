#include "Stdafx.h"
#include "ClayShooting.h"

/*
과제 2. 클레이 사격

- 좌/우에서 무작위로 출현하는 타겟을 마우스로 제거한다.

- 타겟을 제거하면 점수 획득
ㄴ 제거된 타겟은 그 자리에서 바로 떨어진다.

- 등장하는 타겟의 종류는 무작위 도형 처리

ㄴ 사각형 : 50점, 원 : -100점, 다각형 100점

ㄴ 게임 시간은 60초 한정하고 / 시간이 다 되거나 내 점수가 5천점이 되면 게임 종료

타임 어택. API 프레임 워크

- 가상화를 통해 메인게임 클래스가 만들어지고 키 매니저를 통해 렉트를 움직이는 파트까지

- 실패시 : 깜지 5번
*/

HRESULT ClayShooting::init(void)
{
	GameNode::init();
	point = 0;
	deltaTime = 0;
	return S_OK;
}

void ClayShooting::release(void)
{
	GameNode::release();
}

void ClayShooting::update(void)
{
	GameNode::update();
	deltaTime++;
	if (nextClayTime < deltaTime)
	{
		deltaTime = 0;
		clays.push_back(new Clay());
	}
}

void ClayShooting::render(HDC hdc)
{
	MoveToEx(hdc, 0, 600, NULL);
	LineTo(hdc, 800, 600);
}

LRESULT ClayShooting::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
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
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
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