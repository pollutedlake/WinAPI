/*
과제 3. 사각형 이동

- 방향키를 통해 사각형을 움직인다.

- 예외처리 : 사각형은 화면 밖으로 나갈 수 없다.
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int rt1Width = 50;
	int rt1Height = 50;
	static RECT rt1 = { 50, 50, 50 + rt1Width, 50 + rt1Height };
	RECT startRT1 = { 50, 50, 100, 100 };
	RECT cRT;
	int velocity = 10;
	GetClientRect(hWnd, &cRT);

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, rt1.left, rt1.top, rt1.right, rt1.bottom);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
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
			break;
		case VK_RIGHT:
			if (rt1.right < cRT.right)
			{

				rt1.left += velocity;
				rt1.right += velocity;
				if (rt1.right > cRT.right)
				{
					rt1.right = cRT.right;
					rt1.left = cRT.right - rt1Width;
				}
			}
			break;
		case VK_UP:
			if (rt1.top > cRT.top)
			{
				rt1.top -= velocity;
				rt1.bottom -= velocity;
				if (rt1.top < cRT.top)
				{
					rt1.top = cRT.top;
					rt1.bottom = cRT.top + rt1Height;
				}
			}
			break;
		case VK_DOWN:
			if (rt1.bottom < cRT.bottom)
			{
				rt1.top += velocity;
				rt1.bottom += velocity;
				if (rt1.bottom > cRT.bottom)
				{
					rt1.bottom = cRT.bottom;
					rt1.top = cRT.bottom - rt1Height;
				}
			}
			break;
		case VK_SPACE:
			rt1 = startRT1;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}