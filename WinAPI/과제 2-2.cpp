/*
과제 2. 애플 로고 출력

- SetPixel을 이용해서 만든다.
*/

#include<Windows.h>
#include"resource1.h"

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

void DrawBitmap(HDC hdc, int x, int y, int width, int height, HBITMAP hBit)
{
    HDC MemDC;
    HBITMAP OldBitmap;
    int bx, by;
    BITMAP bit;

    MemDC = CreateCompatibleDC(hdc);
    OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

    GetObject(hBit, sizeof(BITMAP), &bit);
    bx = bit.bmWidth;
    by = bit.bmHeight;
    StretchBlt(hdc, x, y, width, height, MemDC, 0, 0, bx, by,SRCCOPY);

    SelectObject(MemDC, OldBitmap);
    DeleteDC(MemDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rt = { 0, 0, 256, 128 };
    static HBITMAP MyBitmap;
    static bool isDraw = true;

    switch (iMessage)
    {
    case WM_CREATE:                 // 생성자
        MyBitmap = LoadBitmap(_hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
        break;

    case WM_PAINT:                  // 출력에 관한 모든 것을 담당한다. (문자, 그림, 도형 등등 화면에 보이는 모든것)
        if (isDraw)
        {
            hdc = BeginPaint(hWnd, &ps);
            DrawBitmap(hdc, rt.left, rt.top, rt.right, rt.bottom, MyBitmap);
            for (int i = rt.left; i < rt.right; i++)
            {
                for (int j = rt.top; j < rt.bottom; j++)
                {
                    SetPixel(hdc, i + 300, j, GetPixel(hdc, i, j));
                }
            }
            isDraw = false;
            InvalidateRect(hWnd, &rt, TRUE);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:                // 소멸자
        DeleteObject(MyBitmap);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}