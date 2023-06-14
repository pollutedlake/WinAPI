/*
과제 3. 공 튕기기
- 큰 사각형 안에 작은 공이 있다.

- 작은 공은 큰 사각형 안에서 사용자의 별다른 입력이 없어도 사각형 면에 튕기면서 지속적으로 움직인다.

- 큰 사각형은 키보드 입력을 받으며 크기를 줄일 수 있다.

- 크기가 늘어나거나 줄어들면 당연히 안쪽에 있는 공도 영향을 받는다.
ㄴ 마우스 왼 클릭시 : 공 속도 증가
ㄴ 마우스 우 클릭시 : 공 속도 감소

한줄 조사
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
    static int speed = 1;
    static int dirX = 1;
    static int dirY = 1;
    static RECT rt = { 100, 100, 700, 700 };
    static RECT circleRT = { 350, 350, 380, 380 };

    switch (iMessage)
    {
    case WM_CREATE:                 // 생성자
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
    case WM_PAINT:                  // 출력에 관한 모든 것을 담당한다. (문자, 그림, 도형 등등 화면에 보이는 모든것)
        hdc = BeginPaint(hWnd, &ps);
        Rectangle(hdc, rt.left, rt.top, rt.right, rt.bottom);
        Ellipse(hdc, circleRT.left, circleRT.top, circleRT.right, circleRT.bottom);
        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:        // 마우스 왼쪽 버튼이 눌렸을 때 메세지가 발생한다.
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

    case WM_DESTROY:                // 소멸자
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