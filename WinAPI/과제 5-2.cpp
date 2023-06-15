/*
<2�ϵ��� �����ϴ� ����>
���� 2. ������ Ȱ���� �� �� �׷�����

- ������ Ȱ���Ѵ�.
*/

#include "Stdafx.h"
#include "resource1.h"

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
    HDC hdc, memDC;                // �ڵ� DC
    PAINTSTRUCT ps;         // ����Ʈ ����ü
    static HBITMAP myBitMap;
    HBITMAP oldBitMap;

    /*POINT hair[] = {{337, 94}, {356, 91}, {376, 81}, {414, 81}, {452, 84}, {486, 96}, {516, 108}, {542, 126}, {562, 151}, {584, 174},
                    {597, 194}, {609, 215}, {622, 239}, {627, 266}, {629, 297}, {623, 319}, {620, 339}, {613, 362}, {608, 383}, {600, 403},
                    {592, 497}, {583, 439}, {557, 358}, {523, 336}, {493, 330}, {474, 331}, {474, 331}, {444, 332}, {416, 330}, {384, 325},
                    {360, 310}, {338, 295}, {323, 278}, {311, 260}, {300, 238}, {287, 221}, {254, 258}, {235, 297}, {216, 337}, {204, 393},
                    {201, 447}, {155, 312}, {154, 289}, {164, 222}, {174, 205}, };*/

    static RECT rc = { 100, 100, 200, 200 };

    switch (iMessage)
    {
    case WM_CREATE:                 // ������
        myBitMap = LoadBitmap(_hInstance, MAKEINTRESOURCE(IDB_BITMAP3));
        break;
    case WM_PAINT:                  // ��¿� ���� ��� ���� ����Ѵ�. (����, �׸�, ���� ��� ȭ�鿡 ���̴� ����)
        hdc = BeginPaint(hWnd, &ps);
        memDC = CreateCompatibleDC(hdc);
        oldBitMap = (HBITMAP)SelectObject(memDC, myBitMap);
        for (int i = 0; i < 800; i++)
        {
            for (int j = 0; j < 800; j++)
            {
                if (GetPixel(memDC, i, j) == RGB(238, 238, 20))
                {
                    SetPixel(hdc, i, j, RGB(0, 0, 0));
                }
            }
        }
        SelectObject(memDC, oldBitMap);
        DeleteObject(myBitMap);
        DeleteDC(memDC);
        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:                // �Ҹ���
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