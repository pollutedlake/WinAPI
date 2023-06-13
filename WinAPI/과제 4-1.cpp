/*
과제 1. 사각형 드래그 이동

- 마우스로 사각형을 자유롭게 움직일 수 있으면 된다.

※ T / F
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
    HDC hdc;
    PAINTSTRUCT ps;
    static BOOL bRectMove = FALSE;
    static RECT rt = { 100, 100, 200, 200 };
    static POINT exPT;
    static POINT pt;
    char strPT[128];

    switch (iMessage)
    {
    case WM_CREATE:                 // 생성자
        break;
    case WM_PAINT:                  // 출력에 관한 모든 것을 담당한다. (문자, 그림, 도형 등등 화면에 보이는 모든것)
        hdc = BeginPaint(hWnd, &ps);
        Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
        wsprintf(strPT, "X : %d     Y : %d", pt.x, pt.y);
        TextOut(hdc, 10, 10, strPT, strlen(strPT));
        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        if ((pt.x <= rt.right) && (pt.x >= rt.left))
        {
            if ((pt.y <= rt.bottom) && (pt.y >= rt.top))
            {
                bRectMove = TRUE;
            }
        }
        break;
    case WM_MOUSEMOVE:
        if (bRectMove == TRUE)
        {
            exPT = pt;
            pt.x = LOWORD(lParam);
            pt.y = HIWORD(lParam);
            rt.left += pt.x - exPT.x;
            rt.right += pt.x - exPT.x;
            rt.top += pt.y - exPT.y;
            rt.bottom += pt.y - exPT.y;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_LBUTTONUP:
        bRectMove = FALSE;
        break;
    case WM_DESTROY:                // 소멸자
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}