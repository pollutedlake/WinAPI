/*
과제 1. 사각형 영혼 밀어넣기

- 시작은 큰 사각형 2개와 작은 사각형 1개

- 내가 움직일 수 있는 사각형 안에는 작은 사각형이 들어 있다.

- 사각형을 움직이면 작은 사각형 역시 움직이는 버전 1개 / 움직이지 않는 버전 1개
ㄴ 총 2가지 버전
ㄴ 예외처리 : 작은 사각형은 큰 사각형을 벗어날 수 없다.

- 큰 사각형끼리 충돌이 되면 작은 사각형은 충돌이 된 반대편 사각형으로 이동한다.

※ 핵심은 움직일 수 있는 주도권은 작은 사각형을 가지고 있는 "큰 사각형"

예외처리 : 큰 사각형끼리의 모서리에 대한 정밀도를 처리한다.
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