/*
���� 3. �� ƨ���
- ū �簢�� �ȿ� ���� ���� �ִ�.

- ���� ���� ū �簢�� �ȿ��� ������� ���ٸ� �Է��� ��� �簢�� �鿡 ƨ��鼭 ���������� �����δ�.

- ū �簢���� Ű���� �Է��� ������ ũ�⸦ ���� �� �ִ�.

- ũ�Ⱑ �þ�ų� �پ��� �翬�� ���ʿ� �ִ� ���� ������ �޴´�.
�� ���콺 �� Ŭ���� : �� �ӵ� ����
�� ���콺 �� Ŭ���� : �� �ӵ� ����

���� ����
- GetAsyncKeyState
*/
#include "Stdafx.h"

HINSTANCE _hInstance;
HWND _hWnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int, int, int, int);


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
    wndClass.lpszClassName = WINNAME;                                        // Ŭ���� �̸� (�ĺ��� ����)
    wndClass.lpszMenuName = NULL;                                               // �޴� �̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                   // ������ ��Ÿ�� (�ٽ� �׸��� ����)

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WINNAME,                     // ������ Ŭ���� �ĺ���
        WINNAME,                     // ������ Ÿ��Ʋ �� �̸�
        WINSTYLE,            // ������ ��Ÿ��
        WINSTART_X,                            // ������ ȭ�� X ��ǥ
        WINSTART_Y,                            // ������ ȭ�� Y ��ǥ
        WINSIZE_X,                            // ������ ȭ�� ���� ũ��
        WINSIZE_Y,                            // ������ ȭ�� ���� ũ��
        NULL,                           // �θ� ������ -> GetDsktopWindow
        (HMENU)NULL,                    // �޴� �ڵ�
        hInstance,                      // �ν��Ͻ� ����
        NULL                            // �������� �ڽ� �����츦 �����ϸ� �����ϰ� �׷��� �ʴٸ� NULL
                                        // �� �ʿ信 ���ؼ� ����ϱ⵵ ������ ������ NULL
    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

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
    static int speed = 1;
    static int dirX = 1;
    static int dirY = 1;
    static RECT rt = { 100, 100, 700, 700 };
    static RECT circleRT = { 350, 350, 380, 380 };

    switch (iMessage)
    {
    case WM_CREATE:                 // ������
        SetTimer(hWnd, 1, 50, NULL);
        break;
    case WM_TIMER:
        circleRT.left += dirX * speed;
        circleRT.right += dirX * speed;
        circleRT.top += dirY * speed;
        circleRT.bottom += dirY * speed;
        if (circleRT.left< rt.left)
        {
            dirX *= -1;
            circleRT.left = rt.left;
            circleRT.right = circleRT.left + 30;
        }
        if (circleRT.right > rt.right)
        {
            dirX *= -1;
            circleRT.right = rt.right;
            circleRT.left = circleRT.right - 30;
        }
        if (circleRT.top < rt.top)
        {
            dirY *= -1;
            circleRT.top = rt.top;
            circleRT.bottom = circleRT.top + 30;
        }
        if (circleRT.bottom > rt.bottom)
        {
            dirY *= -1;
            circleRT.bottom = rt.bottom;
            circleRT.top = circleRT.bottom - 30;
        }
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_PAINT:                  // ��¿� ���� ��� ���� ����Ѵ�. (����, �׸�, ���� ��� ȭ�鿡 ���̴� ����)
        hdc = BeginPaint(hWnd, &ps);
        Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
        Ellipse(hdc, circleRT.left, circleRT.top, circleRT.right, circleRT.bottom);
        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:        // ���콺 ���� ��ư�� ������ �� �޼����� �߻��Ѵ�.
        speed++;
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_UP:
            if (rt.bottom - rt.top > 30)
            {
                rt.bottom -= 1;
            }
            break;
        case VK_DOWN:
            if (rt.bottom < 800)
            {
                rt.bottom += 1;
            }
            break;
        case VK_RIGHT:
            if (rt.right < 800)
            {
                rt.right += 1;
            }
            break;
        case VK_LEFT:
            if (rt.right - rt.left > 30)
            {
                rt.right -= 1;
            }
            break;
        }
        break;

    case WM_RBUTTONDOWN:
        speed--;
        break;

    case WM_DESTROY:                // �Ҹ���
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    AdjustWindowRect(&rc, WINSTYLE, false);

    SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}