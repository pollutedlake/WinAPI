/*
���� 1. ������

- ���� ó�� �ʼ� : �������� ����(1�� ���� X / 9�� �ʰ� X)

- ���콺 ���� Ŭ���� ���� �� 1�ܾ� ����� , ��Ŭ���� �ϸ� 1�ܾ� ��������.
�� 3�ܾ� �����Ѵ�.
*/

#include <Windows.h>

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
    HDC hdc;                // �ڵ� DC
    PAINTSTRUCT ps;         // ����Ʈ ����ü
    RECT rt ;
    char str[128];
    static int num = 2;

    switch (iMessage)
    {
    case WM_CREATE:                 // ������
        break;

    case WM_PAINT:                  // ��¿� ���� ��� ���� ����Ѵ�. (����, �׸�, ���� ��� ȭ�鿡 ���̴� ����)
        hdc = BeginPaint(hWnd, &ps);
        for (int i = 2; i <= num; i++)
        {
            for (int j = 1; j < 10; j++)
            {
                wsprintf(str, TEXT("%d X %d = %d"), i, j, i * j);
                TextOut(hdc, 100 + 100 * ((i - 2) % 3), 100 + 20 * (j - 1) + 180 * ((i - 2) / 3), str, strlen(str));
            }
        }
        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:        // ���콺 ���� ��ư�� ������ �� �޼����� �߻��Ѵ�.
        if (num < 9)
        {
            num += 1;
            InvalidateRect(hWnd, NULL, true);
        }
        break;

    case WM_RBUTTONDOWN:
        if (num > 2)
        {
            num--;
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