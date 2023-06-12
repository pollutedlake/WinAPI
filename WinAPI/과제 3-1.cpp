/*
���� 1. �簢�� ��ȥ �о�ֱ�

- ������ ū �簢�� 2���� ���� �簢�� 1��

- ���� ������ �� �ִ� �簢�� �ȿ��� ���� �簢���� ��� �ִ�.

- �簢���� �����̸� ���� �簢�� ���� �����̴� ���� 1�� / �������� �ʴ� ���� 1��
�� �� 2���� ����
�� ����ó�� : ���� �簢���� ū �簢���� ��� �� ����.

- ū �簢������ �浹�� �Ǹ� ���� �簢���� �浹�� �� �ݴ��� �簢������ �̵��Ѵ�.

�� �ٽ��� ������ �� �ִ� �ֵ����� ���� �簢���� ������ �ִ� "ū �簢��"

����ó�� : ū �簢�������� �𼭸��� ���� ���е��� ó���Ѵ�.
*/

#include "Stdafx.h"

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _lpszClass = TEXT("test");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = _lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow
	(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW,
		400,
		100,
		800,
		800,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	ShowWindow(_hWnd, nCmdShow);

	MSG message;

	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam;
}

BOOL collisionCheck(RECT move, RECT stop, int velocity, WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		if ((move.left - velocity < stop.right) && (move.left >= stop.right))
		{
			if ((move.bottom > stop.top) && (move.top < stop.bottom))
			{
				return true;
			}
		}
		break;
	case VK_RIGHT:
		if ((move.right + velocity > stop.left) && (move.right <= stop.left))
		{
			if ((move.bottom > stop.top) && (move.top < stop.bottom))
			{
				return true;
			}
		}
		break;
	case VK_UP:
		if ((move.top - velocity < stop.bottom) && (move.top >= stop.bottom))
		{
			if ((move.left < stop.right) && (move.right > stop.left))
			{
				return true;
			}
		}
		break;
	case VK_DOWN:
		if ((move.bottom + velocity > stop.top) && (move.bottom <= stop.top))
		{
			if ((move.left < stop.right) && (move.right > stop.left))
			{
				return true;
			}
		}
		break;
	}
	return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int rt1Width = 100;
	int rt1Height = 100;
	int rt2Width = 100;
	int rt2Height = 100;
	int smallRTWidth = 50;
	int smallRTHeight = 50;
	static RECT rt1 = { 50, 50, 50 + rt1Width, 50 + rt1Height };
	static RECT rt2 = { 200, 200, 200 + rt2Width, 200 + rt2Height };
	static RECT smallRT = { 75, 75, 75 + smallRTWidth, 75 + smallRTHeight };
	RECT invalidateRt1, invalidateRt2;
	RECT startRT1 = { 50, 50, 50 + rt1Width, 50 + rt1Height };
	RECT startRT2 = { 200, 200, 200 + rt2Width, 200 + rt2Height };
	RECT cRT;
	int velocity = 5;
	bool collision;
	static bool version = true;
	GetClientRect(hWnd, &cRT);

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, rt1.left, rt1.top, rt1.right, rt1.bottom);
		Rectangle(hdc, smallRT.left, smallRT.top, smallRT.right, smallRT.bottom);
		Rectangle(hdc, rt2.left, rt2.top, rt2.right, rt2.bottom);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		collision = collisionCheck(rt1, rt2, velocity, wParam);
		switch (wParam)
		{
		case VK_LEFT:
			if(!collision)
			{
				if (rt1.left > cRT.left)
				{
					rt1.left -= velocity;
					rt1.right -= velocity;
					if (rt1.left < cRT.left)
					{
						rt1.left = cRT.left;
						rt1.right = rt1.left + rt1Width;
					}
				}
			}
			if (smallRT.right > rt1.right)
			{
				smallRT.right = rt1.right;
				smallRT.left = smallRT.right - smallRTWidth;
			}
			break;
		case VK_RIGHT:
			if (!collision)
			{
				if (rt1.right < cRT.right)
				{
					rt1.left += velocity;
					rt1.right += velocity;
					if (rt1.right > cRT.right)
					{
						rt1.right = cRT.right;
						rt1.left = rt1.right - rt1Width;
					}
				}
			}
			if (smallRT.left < rt1.left)
			{
				smallRT.left = rt1.left;
				smallRT.right = smallRT.left + smallRTWidth;
			}
			break;
		case VK_UP:
			if (!collision)
			{
				if (rt1.top > cRT.top)
				{
					rt1.top -= velocity;
					rt1.bottom -= velocity;
					if (rt1.top < cRT.top)
					{
						rt1.top = cRT.top;
						rt1.bottom = rt1.top + rt1Height;
					}
				}
			}
			if (smallRT.bottom > rt1.bottom)
			{
				smallRT.bottom = rt1.bottom;
				smallRT.top = smallRT.bottom - smallRTHeight;
			}
			break;
		case VK_DOWN:
			if (!collision)
			{
				if (rt1.bottom < cRT.bottom)
				{
					rt1.top += velocity;
					rt1.bottom += velocity;
					if (rt1.bottom > cRT.bottom)
					{
						rt1.bottom = cRT.bottom;
						rt1.top = rt1.bottom - rt1Height;
					}
				}
			}
			if (smallRT.top < rt1.top)
			{
				smallRT.top = rt1.top;
				smallRT.bottom = smallRT.top + smallRTWidth;
			}
			break;
		case VK_SPACE:
			rt1 = startRT1;
			rt2 = startRT2;
			break;
		}
		if (collision)
		{
			RECT temp = rt1;
			rt1 = rt2;
			rt2 = temp;
			smallRT = RectMakeCenter(rt1.left + rt1Width / 2, rt1.top + rt1Height / 2, smallRTWidth, smallRTHeight);
		}
		if (version)
		{
			smallRT = RectMakeCenter(rt1.left + rt1Width / 2, rt1.top + rt1Height / 2, smallRTWidth, smallRTHeight);
		}
		invalidateRt1 = { rt1.left - 100, rt1.top - 100, rt1.right + 100, rt1.bottom + 100 };
		invalidateRt2 = { rt2.left - 100, rt2.top - 100, rt2.right + 100, rt2.bottom + 100 };
		InvalidateRect(hWnd, &invalidateRt1, TRUE);
		InvalidateRect(hWnd, &invalidateRt2, TRUE);
		break;
	case WM_LBUTTONDOWN:
		version = !version;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}