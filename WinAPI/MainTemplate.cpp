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

    wndClass.cbClsExtra = 0;                                                    // 클래스 여분 메모리
    wndClass.cbWndExtra = 0;                                                    // 윈도우 여분 메모리
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);               // 백그라운드
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                             // 마우스 커서
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           // 아이콘
    wndClass.hInstance = hInstance;                                             // 윈도우를 소요한 프로그램의 식별자 정보
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                                    // 윈도우 프로시저
    wndClass.lpszClassName = WINNAME;                                        // 클래스 이름 (식별자 정보)
    wndClass.lpszMenuName = NULL;                                               // 메뉴 이름
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                   // 윈도우 스타일 (다시 그리기 정보)

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WINNAME,                     // 윈도우 클래스 식별자
        WINNAME,                     // 윈도우 타이틀 바 이름
        WINSTYLE,            // 윈도우 스타일
        WINSTART_X,                            // 윈도우 화면 X 좌표
        WINSTART_Y,                            // 윈도우 화면 Y 좌표
        WINSIZE_X,                            // 윈도우 화면 가로 크기
        WINSIZE_Y,                            // 윈도우 화면 세로 크기
        NULL,                           // 부모 윈도우 -> GetDsktopWindow
        (HMENU)NULL,                    // 메뉴 핸들
        hInstance,                      // 인스턴스 지정
        NULL                            // 윈도우의 자식 윈도우를 생성하면 지정하고 그렇지 않다면 NULL
                                        // ㄴ 필요에 의해서 사용하기도 하지만 지금은 NULL
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
    HDC hdc;                // 핸들 DC
    PAINTSTRUCT ps;         // 페인트 구조체

    switch (iMessage)
    {
    case WM_CREATE:                 // 생성자
        break;

    case WM_PAINT:                  // 출력에 관한 모든 것을 담당한다. (문자, 그림, 도형 등등 화면에 보이는 모든것)
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:        // 마우스 왼쪽 버튼이 눌렸을 때 메세지가 발생한다.
        break;

    case WM_KEYDOWN:
        break;

    case WM_RBUTTONDOWN:
        break;

    case WM_MOUSEMOVE:
        break;

    case WM_DESTROY:                // 소멸자
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