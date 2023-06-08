/*
과제 1. 구구단

- 예외 처리 필수 : 구구단의 본질(1단 이하 X / 9단 초과 X)

- 마우스 왼쪽 클릭을 했을 시 1단씩 생기고 , 우클릭을 하면 1단씩 지워진다.
ㄴ 3단씩 개행한다.
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

    wndClass.cbClsExtra = 0;                                                    // 클래스 여분 메모리
    wndClass.cbWndExtra = 0;                                                    // 윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);               // 백그라운드
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                             // 마우스 커서
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           // 아이콘
    wndClass.hInstance = hInstance;                                             // 윈도우를 소요한 프로그램의 식별자 정보
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                                    // 윈도우 프로시저
    wndClass.lpszClassName = _lpszClass;                                        // 클래스 이름 (식별자 정보)
    wndClass.lpszMenuName = NULL;                                               // 메뉴 이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                   // 윈도우 스타일 (다시 그리기 정보)

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        _lpszClass,                     // 윈도우 클래스 식별자
        _lpszClass,                     // 윈도우 타이틀 바 이름
        WS_OVERLAPPEDWINDOW,            // 윈도우 스타일
        400,                            // 윈도우 화면 X 좌표
        100,                            // 윈도우 화면 Y 좌표
        800,                            // 윈도우 화면 가로 크기
        800,                            // 윈도우 화면 세로 크기
        NULL,                           // 부모 윈도우 -> GetDsktopWindow
        (HMENU)NULL,                    // 메뉴 핸들
        hInstance,                      // 인스턴스 지정
        NULL                            // 윈도우의 자식 윈도우를 생성하면 지정하고 그렇지 않다면 NULL
                                        // ㄴ 필요에 의해서 사용하기도 하지만 지금은 NULL
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
    HDC hdc;                // 핸들 DC
    PAINTSTRUCT ps;         // 페인트 구조체
    RECT rt ;
    char str[128];
    static int num = 2;

    switch (iMessage)
    {
    case WM_CREATE:                 // 생성자
        break;

    case WM_PAINT:                  // 출력에 관한 모든 것을 담당한다. (문자, 그림, 도형 등등 화면에 보이는 모든것)
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

    case WM_LBUTTONDOWN:        // 마우스 왼쪽 버튼이 눌렸을 때 메세지가 발생한다.
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

    case WM_DESTROY:                // 소멸자
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}