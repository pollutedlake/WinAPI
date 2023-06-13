/*
���� 3. �簢�� 4�� �б�

- �簢���� ������ �� 4��

- ���콺�� ȭ�鿡 �׷��� 4���� �簢�� �� �ƹ��ų� ������ �����Ӱ� �����δ�.

- ���콺�� �����̰� �ִ� �簢���� �ٸ� �簢���� �浹�Ǹ� �浹�� �簢���� "�ڿ�������" �з�����.

�� ���� / �׷��� ���̰�
�� ������Ű

���� ����. ������ ����

- �̱��� + @ 4��
*/

#include "Stdafx.h"
#include <utility>
using namespace std;

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

BOOL checkRectSelect(POINT pt, RECT rt)
{
    if ((pt.x >= rt.left) && (pt.x <= rt.right))
    {
        if ((pt.y >= rt.top) && (pt.y <= rt.bottom))
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL checkCollision(RECT moveRT, RECT stopRT)
{
    if ((moveRT.left >= stopRT.left) && (moveRT.left <= stopRT.right))
    {
        if ((moveRT.top >= stopRT.top) && (moveRT.top <= stopRT.bottom))
        {
            return TRUE;
        }
    }
    if ((moveRT.right >= stopRT.left) && (moveRT.right <= stopRT.right))
    {
        if ((moveRT.top >= stopRT.top) && (moveRT.top <= stopRT.bottom))
        {
            return TRUE;
        }
    }
    if ((moveRT.left >= stopRT.left) && (moveRT.left <= stopRT.right))
    {
        if ((moveRT.bottom >= stopRT.top) && (moveRT.bottom <= stopRT.bottom))
        {
            return TRUE;
        }
    }
    if ((moveRT.right >= stopRT.left) && (moveRT.right <= stopRT.right))
    {
        if ((moveRT.bottom >= stopRT.top) && (moveRT.bottom <= stopRT.bottom))
        {
            return TRUE;
        }
    }
    return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static POINT pt;
    static POINT exPT;
    static BOOL bRT1Move = FALSE;
    static BOOL bRT2Move = FALSE;
    static BOOL bRT3Move = FALSE;
    static BOOL bRT4Move = FALSE;
    static pair<BOOL, RECT> rt[4];
    static RECT rt1 = { 50, 50, 150, 150 };
    static RECT rt2 = { 600, 50, 700, 150 };
    static RECT rt3 = { 600, 600, 700, 700 };
    static RECT rt4 = { 50, 600, 150, 700 };
    static int moveRT;
    static BOOL collRect[4] = { FALSE, FALSE, FALSE, FALSE };
    static char str[128];

    switch (iMessage)
    {
    case WM_CREATE:                 // ������
        rt[0] = make_pair(bRT1Move, rt1);
        rt[1] = make_pair(bRT2Move, rt2);
        rt[2] = make_pair(bRT3Move, rt3);
        rt[3] = make_pair(bRT4Move, rt4);
        break;
    case WM_PAINT:                  // ��¿� ���� ��� ���� ����Ѵ�. (����, �׸�, ���� ��� ȭ�鿡 ���̴� ����)
        hdc = BeginPaint(hWnd, &ps);
        wsprintf(str, "%d %d %d %d", collRect[0], collRect[1], collRect[2], collRect[3]);
        TextOut(hdc, 10, 10, str, 7);
        for (int i = 0; i < 4; i++)
        {
            Rectangle(hdc, rt[i].second.left, rt[i].second.top, rt[i].second.right, rt[i].second.bottom);
        }
        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        for (int i = 0; i < 4; i++)
        {
            rt[i].first = checkRectSelect(pt, rt[i].second);
            if (rt[i].first == TRUE)
            {
                moveRT = i;
                break;
            }
        }
        break;
    case WM_TIMER:

        break;
    case WM_MOUSEMOVE:
        exPT = pt;
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        if (rt[moveRT].first == TRUE)
        {
            rt[moveRT].second.left += pt.x - exPT.x;
            rt[moveRT].second.right += pt.x - exPT.x;
            rt[moveRT].second.top += pt.y - exPT.y;
            rt[moveRT].second.bottom += pt.y - exPT.y;
            InvalidateRect(hWnd, NULL, true);
        }
        for (int i = 0; i < 4; i++)
        {
            if (i == moveRT)
            {
                continue;
            }
            if (checkCollision(rt[moveRT].second, rt[i].second) == TRUE)
            {
                SetTimer(hWnd, 1, 1000, NULL);
                rt[i].second.left += pt.x - exPT.x;
                rt[i].second.right += pt.x - exPT.x;
                rt[i].second.top += pt.y - exPT.y;
                rt[i].second.bottom += pt.y - exPT.y;
                collRect[i] = TRUE;
                InvalidateRect(hWnd, NULL, true);
            }
        }
        break;
    case WM_LBUTTONUP:
        rt[moveRT].first = FALSE;
        break;
    case WM_DESTROY:                // �Ҹ���
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}