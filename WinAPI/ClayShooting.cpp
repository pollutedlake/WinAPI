#include "Stdafx.h"
#include "ClayShooting.h"

/*
���� 2. Ŭ���� ���

- ��/�쿡�� �������� �����ϴ� Ÿ���� ���콺�� �����Ѵ�.

- Ÿ���� �����ϸ� ���� ȹ��
�� ���ŵ� Ÿ���� �� �ڸ����� �ٷ� ��������.

- �����ϴ� Ÿ���� ������ ������ ���� ó��

�� �簢�� : 50��, �� : -100��, �ٰ��� 100��

�� ���� �ð��� 60�� �����ϰ� / �ð��� �� �ǰų� �� ������ 5õ���� �Ǹ� ���� ����

Ÿ�� ����. API ������ ��ũ

- ����ȭ�� ���� ���ΰ��� Ŭ������ ��������� Ű �Ŵ����� ���� ��Ʈ�� �����̴� ��Ʈ����

- ���н� : ���� 5��
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
	case WM_DESTROY:                // �Ҹ���
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}