/*
���� 2. �簢�� ũ�� ����

- ���콺�� �簢���� ũ�⸦ �����Ӱ� ������ �� ������ �ȴ�.

- ����ȭ�鿡�� �巡�� �غ��鼭 �Ȱ��� ����� OK
*/

#include "Stdafx.h"

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _lpszClass = TEXT("Windows API");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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
    HDC hdc;
    PAINTSTRUCT ps;
    static RECT rt = { 100, 100, 200, 200 };
    static BOOL bRectLeftResize = FALSE;
    static BOOL bRectRightResize = FALSE;
    static BOOL bRectTopResize = FALSE;
    static BOOL bRectBottomResize = FALSE;
    static POINT pt;

    switch (iMessage)
    {
    case WM_CREATE:                 // ������
        break;
    case WM_PAINT:                  // ��¿� ���� ��� ���� ����Ѵ�. (����, �׸�, ���� ��� ȭ�鿡 ���̴� ����)
        hdc = BeginPaint(hWnd, &ps);
        Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        if ((pt.x >= rt.left - 5) && (pt.x <= rt.left + 5))
        {
            bRectLeftResize = TRUE;
        }
        if ((pt.x >= rt.right - 5) && (pt.x <= rt.right + 5))
        {
            bRectRightResize = TRUE;
        }
        if ((pt.y >= rt.top - 5) && (pt.y <= rt.top + 5))
        {
            bRectTopResize = TRUE;
        }
        if ((pt.y >= rt.bottom - 5) && (pt.y <= rt.bottom + 5))
        {
            bRectBottomResize = TRUE;
        }
        break;
    case WM_MOUSEMOVE:
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        if (bRectLeftResize == TRUE)
        {
            rt.left = pt.x;
            InvalidateRect(hWnd, NULL, true);
        }
        if (bRectRightResize == TRUE)
        {
            rt.right = pt.x;
            InvalidateRect(hWnd, NULL, true);
        }
        if (bRectTopResize == TRUE)
        {
            rt.top = pt.y;
            InvalidateRect(hWnd, NULL, true);
        }
        if (bRectBottomResize == TRUE)
        {
            rt.bottom = pt.y;
            InvalidateRect(hWnd, NULL, true);
        }
		if ((pt.x <= 0) || (pt.x >= 783))
		{
            bRectLeftResize = FALSE;
            bRectRightResize = FALSE;
            bRectTopResize = FALSE;
            bRectBottomResize = FALSE;
		}
		if ((pt.y <= 0) || (pt.y >= 760))
		{
			bRectLeftResize = FALSE;
			bRectRightResize = FALSE;
			bRectTopResize = FALSE;
			bRectBottomResize = FALSE;
		}
        break;
    case WM_LBUTTONUP:
        bRectLeftResize = FALSE;
        bRectRightResize = FALSE;
        bRectTopResize = FALSE;
        bRectBottomResize = FALSE;
        break;
    case WM_DESTROY:                // �Ҹ���
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}