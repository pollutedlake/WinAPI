/*
과제 4. 사각형 2개 움직이기

- 총 사각형 갯수 : 2개

- 하나는 움직일 수 있는 사각형 / 다른 하나는 움직일 수 없는 사각형

- 움직일 수 없는 사각형을 움직일 수 있는 사각형이 밀어낼 수 있으면 된다.

- 예외처리 : 2개의 사각형은 화면 밖으로 나갈 수 없다.

- 2개의 사각형을 초기 위치로 돌리는 기능도 추가한다.

※ 별다른 언급을 하기 전까지는 충돌 함수 사용 금지
*/

#include<Windows.h>

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
	int rt1Width = 50;
	int rt1Height = 50;
	int rt2Width = 50;
	int rt2Height = 50;
	static RECT rt1 = { 50, 50, 50 + rt1Width, 50 + rt1Height };
	static RECT rt2 = { 200, 200, 200 + rt2Width, 200 + rt2Height };
	RECT invalidateRt1, invalidateRt2;
	RECT startRT1 = { 50, 50, 100, 100 };
	RECT startRT2 = { 200, 200, 250, 250 };
	RECT cRT;
	int velocity = 5;
	bool collision;
	GetClientRect(hWnd, &cRT);

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, rt1.left, rt1.top, rt1.right, rt1.bottom);
		Rectangle(hdc, rt2.left, rt2.top, rt2.right, rt2.bottom);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		collision = collisionCheck(rt1, rt2, velocity, wParam);
		switch (wParam)
		{
		case VK_LEFT:
			if (collision)
			{
				if (rt1.left > cRT.left + rt2Width)
				{
					rt1.left -= velocity;
					rt1.right -= velocity;
					rt2.left -= velocity;
					rt2.right -= velocity;
					if (rt1.left < cRT.left + rt2Width)
					{
						rt2.left = cRT.left;
						rt2.right = cRT.left + rt2Width;
						rt1.left = rt2.right;
						rt1.right = rt1.left + rt1Width;
					}
				}
			}
			else {
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
			break;
		case VK_RIGHT:
			if (collision)
			{
				if (rt1.right < cRT.right - rt2Width)
				{
					rt1.left += velocity;
					rt1.right += velocity;
					rt2.left += velocity;
					rt2.right += velocity;
					if (rt1.right > cRT.right - rt2Width)
					{
						rt2.right = cRT.right;
						rt2.left = rt2.right - rt2Width;
						rt1.right = rt2.left;
						rt1.left = rt1.right - rt1Width;
					}
				}
			}
			else
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
			break;
		case VK_UP:
			if (collision)
			{
				if (rt1.top > cRT.top + rt2Height)
				{
					rt1.top -= velocity;
					rt1.bottom -= velocity;
					rt2.top -= velocity;
					rt2.bottom -= velocity;
					if (rt1.top < cRT.top + rt2Height)
					{
						rt2.top = cRT.top;
						rt2.bottom = rt2.top + rt2Height;
						rt1.top = rt2.bottom;
						rt1.bottom = rt1.top + rt1Height;
					}
				}
			}
			else
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
			break;
		case VK_DOWN:
			if (collision)
			{
				if (rt1.bottom < cRT.bottom - rt2Height)
				{
					rt1.bottom += velocity;
					rt1.top += velocity;
					rt2.bottom += velocity;
					rt2.top += velocity;
					if (rt1.bottom > cRT.bottom - rt2Height)
					{
						rt2.bottom = cRT.bottom;
						rt2.top = rt2.bottom - rt2Height;
						rt1.bottom = rt2.top;
						rt1.top = rt1.bottom - rt1Height;
					}
				}
			}
			else
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
			break;
		case VK_SPACE:
			rt1 = startRT1;
			rt2 = startRT2;
			break;

		}
		invalidateRt1 = { rt1.left - 5, rt1.top - 5, rt1.right + 5, rt1.bottom + 5 }; 
		invalidateRt2 = { rt2.left - 5, rt2.top - 5, rt2.right + 5, rt2.bottom + 5 }; 
		InvalidateRect(hWnd, &invalidateRt1, TRUE);
		InvalidateRect(hWnd, &invalidateRt2, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}