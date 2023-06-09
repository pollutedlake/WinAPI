/*
과제 2. 애플 로고 출력

- SetPixel을 이용해서 만든다.
*/

#include<Windows.h>
#include<math.h>

#define PI 3.141592

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

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, 100, 100, 700, 700);
		for (int i = 100; i < 700; i += 1)
		{
			for (int j = 100; j < 700; j += 1)
			{
				SetPixel(hdc, i, j, RGB(96, 187, 68));
				SetPixel(hdc, i, j, RGB(252, 184, 39));
				SetPixel(hdc, i, j, RGB(245, 130, 31));
				SetPixel(hdc, i, j, RGB(224, 58, 60));
				SetPixel(hdc, i, j, RGB(149, 61, 148));
				SetPixel(hdc, i, j, RGB(0, 158, 221));
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void DrawCircle(HDC hdc, int x, int y, int radius, double startAngle, double endAngle)
{
	double startX, startY, endX, endY;
	double angle = startAngle;
	startX = x + radius * cos(angle / 180 * PI);
	startY = y + radius * sin(angle / 180 * PI);
	MoveToEx(hdc, startX, startY, NULL);
	for (double angle = startAngle; angle <= endAngle; angle += 0.1)
	{
		LineTo(hdc, x + radius * cos(angle / 180 * PI), y + radius * sin(angle / 180 * PI));
	}
}