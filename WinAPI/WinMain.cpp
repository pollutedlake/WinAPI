// WinMain

#pragma region WinAPI
/*
�� API

- �ü���� ���� ���α׷� ������ ���� �����ϴ� �Լ��� ����

- ��ɾ��� �������� ���ø����̼� ���α׷����� ���۷����� �ý����� �⺻���� ����� ����� �ʿ䰡 ���� ��� API���� ��ɾ� ȣ���� ����ȴ�.

EX)
�ϵ���� --------------- �ü�� (Windows) ---------------------- ���� ���α׷�
( API �Լ� )

�� ����

- �ü���� ������ ���� ����� ������ ����ϱ⿡ Ȯ�强 �� ������, �׸��� ���������鿡�� ���� �����ϴ�. (�������� != ������)

- �ü���� ���ӵǱ� ������ ���� Ȯ������ ���� ����. (����)

�� ����

- �÷����� ����ȭ
    �� C ��� ����

�� API ����

- ũ�� �������� �޼��� ����, Window Procedure�� ������.

*/

#pragma endregion

#include <Windows.h>
#include <tchar.h>

// ���� ����
/*
�ν��Ͻ�
- ������ OS�� ���� ����ǰ� �ִ� ���α׷��� Ȯ���ϱ� ���� ��
- �⺻������ ���� ���α׷��̸� ���� �ν��Ͻ� ���� ������.
- Ŭ������ �޸𸮿� ������ ������ ��ü
�� ����ǰ� �ִ� ������ ���α׷���
*/
HINSTANCE _hInstance;
// ������ �ڵ� (������ â)
HWND _hWnd;
// ������ Ÿ��Ʋ
LPTSTR _lpszClass = TEXT("Windows API");
//TCHAR* pszString = _T("Windwos API");

/*
�� TCHAR

- TCHAR���� ������Ʈ�� ���ڼ� ������ ���� �ڵ������� char �Ǵ� wchar_t�� Type_Casting �Ǵ� �߰� ��ũ�� �ڷ���

- ��Ƽ ����Ʈ�� ���� �ڵ� ȯ�濡�� ������ ���� �۾� ���� ���α׷��� �����ϱ� ���ؼ��� TCHAR������ ���ڿ��� ǥ���� ���� ��õ

- �Ϲ������� ������ ���� ���α׷����� ���ڿ� ����� ���� ���ؼ��� �߰� ������ ���� char* �Ǵ� wchar_t*�� ��ȯ�� �ִ� _T ��ũ�θ� �̿��ؾ� �Ѵ�.

/*
LPSTR       -> Long Pointer string              = char*
LPCSTR      -> Long Pointer Constant string     = const char*
LPCTSTR     -> Long Pointer Constant t_string   = const tchar*
*/


// �ݹ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/*
hInstance : ���α׷� �ν��Ͻ� �ڵ�
hPrevInstance : ������ ����� �ν��Ͻ� �ڵ�
lpszCmdParam : ��������� �Էµ� ���α׷� �μ�
nCmdShow : ���α׷��� ���۵� ���� (�ּ�ȭ / ũ�� ���)
*/

/*
// ���ڼ�
int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    TCHAR*    lpszCmdParam,
    int       nCmdShow)
*/

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpszCmdParam,
                     int       nCmdShow)
{
    // �ν��Ͻ��� ���� ������ ��´�.
    _hInstance = hInstance;

    /*
    - WinMain�� ����

    1. ������ â�� ���� �� ȭ�鿡 ����
        �� ȭ�鿡 â�� ���� ���ؼ��� 4������ ��� ó���ؾ� �Ѵ�.

    2. �޼��� ����
    */

    // 1-1. ������â ����ü ���� �� �ʱ�ȭ
    // WNDCLASS: �� ����ü�� �������� �ü������ ������ ������ ����ϱ� ���ؼ� Ŀ������ �����츦 �ĺ��� �� �ִ� ���� ���� ����ϴ� ������ �����Ѵ�.
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

    // 1-2. ������ Ŭ���� ���
    RegisterClass(&wndClass);

    // 1-3. ȭ�鿡 ������ ������ â ����
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

    // 1-4. ȭ�鿡 ������â �����ֱ�
    ShowWindow(_hWnd, nCmdShow);

    // ���� ������Ʈ (�ܱ� / ����)������Ʈ ó�� �ؾ� �Ѵ�.
    //UpdateWindow(_hWnd);

    // 2. �޼��� ����
    // MSG : �ü������ �߻��ϴ� �޼��� ������ �������� ���� ����ü
    MSG message;
    // ZeroMemory(&message, sizeof(message));      UpdateWindoe ���� ��Ʈ�� ����Ѵ�. 

    /*
    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
    */

    /*
    �ڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡڡ�
    �� �޼��� ���� ����
    1. GetMessage
    �� �޼����� ������ �� ���������� �����ִ� �Լ� (���)
    �� GetMessage�� �޼��� ť�κ��� �ϳ��� �޼����� �������� ������ �����Ѵ�.
    �� ��, �޼��� ť�� ��� ���� ��� �޼�����(�߻��� �޼��� x) ���ö����� ����Ѵ�.
    
    2. PeekMessage
    �� �޼����� ������ ��ȯ �Ǵ� �Լ�
    */

    // �⺻ �޼��� �����Դϴ�.
    while (GetMessage(&message, 0, 0, 0))
    {

        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    /*
    TranslateMessage
    �� Ű������ �Է� �޼��� ó�� ���
    �� �Էµ� Ű�� ����Ű���� Ȯ�� �� �빮�� Ȥ�� �ҹ���, �ѱ� / ���������� ����
       WM_CHAR �޼����� �߻� ��Ų��.

    DispatchMessage:
    �� ������ ���ν������� ���޵� �޼����� ���� ������� ������ �ش�.
    */

    return message.wParam;
}

/*
hWnd : ��� �����쿡�� �߻��� �޼������� ����
iMessage : �޼��� ���� ��ȣ
wParam : unsigned int -> ���콺 ��ư�� ����, Ű���� ���� Ű�� ���¸� ����
lParam : unsinged long -> ���콺 Ŭ�� ��ǥ�� ����
*/

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    /*
    �� Window Procedure
    �� �޼����� �ü���� ���� -> ������ �ü���� ȣ��ǰ� ���ش�.
    �� WinMain()�� �ƴ� �ü���� ���� ȣ���� �Ǵ� �ݹ�(Callback) �Լ�
    �� �����츦 ������ �� �ݵ�� ������ ����� �Ѵ�.

    - ����ؾ� �Ұ� ������ ���ν��� ���ο����� �����쿡�� �߻��� ��� �޼����� ó���ϴ� ���� �ƴ϶� Ư�� �޼������� ó���ϰ� ������ �޼����� DefWindowProc �Լ��� ó���ϵ��� ������ �����ϴ°� �Ϲ����̴�.

    �� �� ������ �ݵ�� ����� ��
    */

    HDC hdc;                // �ڵ� DC
    PAINTSTRUCT ps;         // ����Ʈ ����ü

    char str[] = "�׷�";

    /*
    char[]: ���� ����
    char*: ���� �Ұ�
    */

    switch (iMessage)
    {
    case WM_CREATE:                 // ������
        break;

    case WM_PAINT:                  // ��¿� ���� ��� ���� ����Ѵ�. (����, �׸�, ���� ��� ȭ�鿡 ���̴� ����)
        hdc = BeginPaint(hWnd, &ps);

        /*
        strcpy(x, y) : y�� x�� ����
        strcat(x, y) : x ���ڿ� + y ���ڿ�
        strlen(x) : ���ڿ� ����
        strcmp(x, y) : �� ���ڿ��� ������ Ȯ��
        �� x, y ����       =>      0 ����
        �� x < y           =>      -1 ����
        �� x > y           =>       1 ����

        strcpy      ->      wcscpy      ->      _tcscpy
        strcat      ->      wcscat      ->      _tcscat
        strlen      ->      wcslen      ->      _tcslen
        strcmp      ->      wcslen      ->      _tcscmp
        strtok                                  ���ڿ� �ڸ���
        strchr                                  ���� ã��
        strstr                                  ���ڿ� ã��
        */

        // ��ī��Ʈ ��ǥ(�ǻ�Ȱ ��ǥ��) != ������ ��ǥ��

        // TextOut(): ���� ���(hdc, x, y, ���ڿ�, ���ڿ� ����)
        TextOut(hdc, 300, 300, "������ �ʹ� ��մ�^^", strlen("������ �ʹ� ��մ�^^"));
        // �� strlen�� �Ҵ���� �޸𸮿� ���ε� �� ���ڿ����� NULL���� ������ ���ڿ� ����

        // ���ڿ� ���ڻ� ����
        SetTextColor(hdc, RGB(255, 0, 0));
        TextOut(hdc, 300, 400, "���� �� �� ���ּ���.", strlen("���� �� �� ���ּ���."));
        
        MoveToEx(hdc, 400, 400, NULL);
        LineTo(hdc, 200, 400);

        MoveToEx(hdc, 400, 400, NULL);
        LineTo(hdc, 200, 200);

        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:        // ���콺 ���� ��ư�� ������ �� �޼����� �߻��Ѵ�.
        hdc = GetDC(hWnd);

        SetTextColor(hdc, RGB(0, 0, 255));
        TextOut(hdc, 350, 500, str, strlen(str));

        ReleaseDC(hWnd, hdc);

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
        // PostQuitMessage() : �� �Լ��� �޼��� ť�� Quit �޼����� ������ ������ �Ѵ�.
        // ��, Quit �޼����� �����ϴ� ���� GetMessage �Լ��� FALSE�� ��ȯ������ �޼��� ������ ����ȴ�.
        PostQuitMessage(0);
        return 0;
    }

    // ������ ���ν������� ó������ ���� ������ �޼����� ó���� �ش�.
    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

/*
����1. ������ â �����

- �ð��� 10��

- ���н� ���� 7��

���� ����. ��Ʈ�� ������ ���´�.

- Callback Function, DC, GetDC / Release DC, BeginPaint / EndPaint
  WM_Paint, PAINTSTRUCT
*/