/*
���� 2. WinAPI ���

- MoveToEx() + LineTo()�� �̿��Ѵ�.

�� ���� ���� �Լ� ��� ����

- 1. �ڱ� �̸� ��� (�ѱ�)

2. Unreal Engine (����)

- ���콺 ������ ������ �ѱ��ھ� ����� �Ǹ� �� Ŭ���� �ϸ� �ѱ��ھ� ��������.

- ���� â ũ�� ���� ���� �̻��� ������� �ؿ´�.

���� ����
- SetTimer

- KillTimer

- InvalidateRect
*/

#include <Windows.h>
#include<math.h>

#define PI      3.141592

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _lpszClass = TEXT("Windows API");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void DrawCircle(HDC, int, int, int, double, double);

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpszCmdParam,
    int       nCmdShow)
{
    _hInstance = hInstance;

    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;                                                    // Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0;                                                    // ������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);               // ��׶���
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                             // ���콺 Ŀ��
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           // ������
    wndClass.hInstance = hInstance;                                             // �����츦 �ҿ��� ���α׷��� �ĺ��� ����
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                                    // ������ ���ν���
    wndClass.lpszClassName = _lpszClass;                                        // Ŭ���� �̸� (�ĺ��� ����)
    wndClass.lpszMenuName = NULL;                                               // �޴� �̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                   // ������ ��Ÿ�� (�ٽ� �׸��� ����)

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        _lpszClass,                     // ������ Ŭ���� �ĺ���
        _lpszClass,                     // ������ Ÿ��Ʋ �� �̸�
        WS_OVERLAPPEDWINDOW,            // ������ ��Ÿ��
        400,                            // ������ ȭ�� X ��ǥ
        100,                            // ������ ȭ�� Y ��ǥ
        800,                            // ������ ȭ�� ���� ũ��
        800,                            // ������ ȭ�� ���� ũ��
        NULL,                           // �θ� ������ -> GetDsktopWindow
        (HMENU)NULL,                    // �޴� �ڵ�
        hInstance,                      // �ν��Ͻ� ����
        NULL                            // �������� �ڽ� �����츦 �����ϸ� �����ϰ� �׷��� �ʴٸ� NULL
                                        // �� �ʿ信 ���ؼ� ����ϱ⵵ ������ ������ NULL
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
    HDC hdc;                // �ڵ� DC
    PAINTSTRUCT ps;         // ����Ʈ ����ü
    RECT rt = { 10, 10, 700, 700 };
    static int letterN = 1;

    switch (iMessage)
    {
    case WM_CREATE:                 // ������
        break;

    case WM_PAINT:                  // ��¿� ���� ��� ���� ����Ѵ�. (����, �׸�, ���� ��� ȭ�鿡 ���̴� ����)
        hdc = BeginPaint(hWnd, &ps);
        MoveToEx(hdc, 10, 10, NULL);
        LineTo(hdc, 10, 60);
        LineTo(hdc, 60, 60);
        LineTo(hdc, 60, 10);
        MoveToEx(hdc, 10, 35, NULL);
        LineTo(hdc, 60, 35);
        MoveToEx(hdc, 80, 10, NULL);
        LineTo(hdc, 80, 80);
        MoveToEx(hdc, 80, 45, NULL);
        LineTo(hdc, 100, 45);
        MoveToEx(hdc, 10, 80, NULL);
        LineTo(hdc, 60, 80);
        LineTo(hdc, 60, 120);

        if (letterN >= 2)
        {
            MoveToEx(hdc, 150, 10, NULL);
            LineTo(hdc, 120, 60);
            MoveToEx(hdc, 135, 35, NULL);
            LineTo(hdc, 150, 60);
            MoveToEx(hdc, 170, 10, NULL);
            LineTo(hdc, 170, 80);
            MoveToEx(hdc, 170, 45, NULL);
            LineTo(hdc, 190, 45);
            DrawCircle(hdc, 140, 90, 15, 0, 360);
        }

        if (letterN >= 3)
        {
            MoveToEx(hdc, 220, 10, NULL);
            LineTo(hdc, 230, 20);
            MoveToEx(hdc, 200, 30, NULL);
            LineTo(hdc, 260, 30);
            DrawCircle(hdc, 230, 55, 15, 0, 360);
            MoveToEx(hdc, 250, 45, NULL);
            LineTo(hdc, 270, 45);
            MoveToEx(hdc, 250, 65, NULL);
            LineTo(hdc, 270, 65);
            MoveToEx(hdc, 270, 20, NULL);
            LineTo(hdc, 270, 90);
            MoveToEx(hdc, 215, 80, NULL);
            LineTo(hdc, 215, 100);
            LineTo(hdc, 260, 100);
        }

        if (letterN >= 4)        // u
        {
            MoveToEx(hdc, 50, 140, NULL);
            LineTo(hdc, 50, 190);
            DrawCircle(hdc, 30, 190, 20, 0, 180);
            LineTo(hdc, 10, 140);
            
        }

        if (letterN >= 5)        // n
        {
            MoveToEx(hdc, 70, 140, NULL);
            LineTo(hdc, 70, 210);
            DrawCircle(hdc, 90, 160, 20, -180, 0);
            LineTo(hdc, 110, 210);
        }

        if (letterN >= 6)        // r
        {
            MoveToEx(hdc, 130, 140, NULL);
            LineTo(hdc, 130, 210);
            DrawCircle(hdc, 150, 170, 20, -180, -45);
        }

        if (letterN >= 7)        // e
        {
            MoveToEx(hdc, 190, 175, NULL);
            LineTo(hdc, 230, 175);
            DrawCircle(hdc, 210, 175, 20, -315, 0);
        }

        if (letterN >= 8)        // a
        {
            MoveToEx(hdc, 275, 140, NULL);
            LineTo(hdc, 275, 210);
            DrawCircle(hdc, 260, 160, 20, -180, -40);
            DrawCircle(hdc, 260, 190, 20, -320, -40);
        }

        if (letterN >= 9)        // l
        {
            MoveToEx(hdc, 310, 140, NULL);
            LineTo(hdc, 310, 210);
        }

        if (letterN >= 10)       // e
        {
			MoveToEx(hdc, 10, 260, NULL);
			LineTo(hdc, 50, 260);
			DrawCircle(hdc, 30, 260, 20, -315, 0);
        }

        if (letterN >= 11)       // n
        {
			MoveToEx(hdc, 70, 240, NULL);
			LineTo(hdc, 70, 310);
			DrawCircle(hdc, 90, 260, 20, -180, 0);
			LineTo(hdc, 110, 310);
        }

        if (letterN >= 12)       // g
        {
            DrawCircle(hdc, 150, 260, 20, 0, 360);
            MoveToEx(hdc, 170, 240, NULL);
            LineTo(hdc, 170, 310);
            DrawCircle(hdc, 170, 295, 15, -270, 0);
        }

        if (letterN >= 13)       // i
        {
            MoveToEx(hdc, 200, 240, NULL);
            LineTo(hdc, 200, 250);
            MoveToEx(hdc, 200, 255, NULL);
            LineTo(hdc, 200, 310);
        }

        if (letterN >= 14)       // n
        {
			MoveToEx(hdc, 220, 240, NULL);
			LineTo(hdc, 220, 310);
			DrawCircle(hdc, 240, 260, 20, -180, 0);
			LineTo(hdc, 260, 310);
        }

        if (letterN >= 15)      // e
        {
			MoveToEx(hdc, 280, 260, NULL);
			LineTo(hdc, 320, 260);
			DrawCircle(hdc, 300, 260, 20, -315, 0);
        }
        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:        // ���콺 ���� ��ư�� ������ �� �޼����� �߻��Ѵ�.
        if (letterN < 15)
        {
            letterN++;
            InvalidateRect(hWnd, NULL, false);
        }
        break;

    case WM_RBUTTONDOWN:
        if (letterN > 1)
        {
            letterN--;
            InvalidateRect(hWnd, NULL, true);
        }
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_LEFT:
            break;
        case VK_RIGHT:
            break;
        case VK_ESCAPE:
            PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }

    case WM_DESTROY:                // �Ҹ���
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