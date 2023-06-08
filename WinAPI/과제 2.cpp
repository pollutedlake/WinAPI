/*
과제 2. WinAPI 출력

- MoveToEx() + LineTo()를 이용한다.

★ 도형 관련 함수 사용 금지

- 1. 자기 이름 출력 (한글)

2. Unreal Engine (영문)

- 마우스 왼쪽을 누르면 한글자씩 출력이 되며 우 클릭을 하면 한글자씩 지워진다.

- 현재 창 크기 기준 절반 이상의 사이즈로 해온다.

한줄 조사
- SetTimer

- KillTimer

- InvalidateRect
*/

#include <Windows.h>
#include<math.h>

#define PI      3.141592

HINSTANCE _hInstance;
HWND _hWnd;
LPTSTR _lpszClass = TEXT("Windows API");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void DrawCircle(HDC, int, int, int, double, double);

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
    RECT rt = { 10, 10, 700, 700 };
    static int letterN = 1;

    switch (iMessage)
    {
    case WM_CREATE:                 // 생성자
        break;

    case WM_PAINT:                  // 출력에 관한 모든 것을 담당한다. (문자, 그림, 도형 등등 화면에 보이는 모든것)
        hdc = BeginPaint(hWnd, &ps);
        MoveToEx(hdc, 10, 10, NULL);
        LineTo(hdc, 10, 60);
        LineTo(hdc, 60, 60);
        LineTo(hdc, 60, 10);
        MoveToEx(hdc, 10, 35, NULL);
        LineTo(hdc, 60, 35);
        MoveToEx(hdc, 80, 10, NULL);
        LineTo(hdc, 80, 80);
        MoveToEx(hdc, 80, 45, NULL);
        LineTo(hdc, 100, 45);
        MoveToEx(hdc, 10, 80, NULL);
        LineTo(hdc, 60, 80);
        LineTo(hdc, 60, 120);

        if (letterN >= 2)
        {
            MoveToEx(hdc, 150, 10, NULL);
            LineTo(hdc, 120, 60);
            MoveToEx(hdc, 135, 35, NULL);
            LineTo(hdc, 150, 60);
            MoveToEx(hdc, 170, 10, NULL);
            LineTo(hdc, 170, 80);
            MoveToEx(hdc, 170, 45, NULL);
            LineTo(hdc, 190, 45);
            DrawCircle(hdc, 140, 90, 15, 0, 360);
        }

        if (letterN >= 3)
        {
            MoveToEx(hdc, 220, 10, NULL);
            LineTo(hdc, 230, 20);
            MoveToEx(hdc, 200, 30, NULL);
            LineTo(hdc, 260, 30);
            DrawCircle(hdc, 230, 55, 15, 0, 360);
            MoveToEx(hdc, 250, 45, NULL);
            LineTo(hdc, 270, 45);
            MoveToEx(hdc, 250, 65, NULL);
            LineTo(hdc, 270, 65);
            MoveToEx(hdc, 270, 20, NULL);
            LineTo(hdc, 270, 90);
            MoveToEx(hdc, 215, 80, NULL);
            LineTo(hdc, 215, 100);
            LineTo(hdc, 260, 100);
        }

        if (letterN >= 4)        // u
        {
            MoveToEx(hdc, 50, 140, NULL);
            LineTo(hdc, 50, 190);
            DrawCircle(hdc, 30, 190, 20, 0, 180);
            LineTo(hdc, 10, 140);
            
        }

        if (letterN >= 5)        // n
        {
            MoveToEx(hdc, 70, 140, NULL);
            LineTo(hdc, 70, 210);
            DrawCircle(hdc, 90, 160, 20, -180, 0);
            LineTo(hdc, 110, 210);
        }

        if (letterN >= 6)        // r
        {
            MoveToEx(hdc, 130, 140, NULL);
            LineTo(hdc, 130, 210);
            DrawCircle(hdc, 150, 170, 20, -180, -45);
        }

        if (letterN >= 7)        // e
        {
            MoveToEx(hdc, 190, 175, NULL);
            LineTo(hdc, 230, 175);
            DrawCircle(hdc, 210, 175, 20, -315, 0);
        }

        if (letterN >= 8)        // a
        {
            MoveToEx(hdc, 275, 140, NULL);
            LineTo(hdc, 275, 210);
            DrawCircle(hdc, 260, 160, 20, -180, -40);
            DrawCircle(hdc, 260, 190, 20, -320, -40);
        }

        if (letterN >= 9)        // l
        {
            MoveToEx(hdc, 310, 140, NULL);
            LineTo(hdc, 310, 210);
        }

        if (letterN >= 10)       // e
        {
			MoveToEx(hdc, 10, 260, NULL);
			LineTo(hdc, 50, 260);
			DrawCircle(hdc, 30, 260, 20, -315, 0);
        }

        if (letterN >= 11)       // n
        {
			MoveToEx(hdc, 70, 240, NULL);
			LineTo(hdc, 70, 310);
			DrawCircle(hdc, 90, 260, 20, -180, 0);
			LineTo(hdc, 110, 310);
        }

        if (letterN >= 12)       // g
        {
            DrawCircle(hdc, 150, 260, 20, 0, 360);
            MoveToEx(hdc, 170, 240, NULL);
            LineTo(hdc, 170, 310);
            DrawCircle(hdc, 170, 295, 15, -270, 0);
        }

        if (letterN >= 13)       // i
        {
            MoveToEx(hdc, 200, 240, NULL);
            LineTo(hdc, 200, 250);
            MoveToEx(hdc, 200, 255, NULL);
            LineTo(hdc, 200, 310);
        }

        if (letterN >= 14)       // n
        {
			MoveToEx(hdc, 220, 240, NULL);
			LineTo(hdc, 220, 310);
			DrawCircle(hdc, 240, 260, 20, -180, 0);
			LineTo(hdc, 260, 310);
        }

        if (letterN >= 15)      // e
        {
			MoveToEx(hdc, 280, 260, NULL);
			LineTo(hdc, 320, 260);
			DrawCircle(hdc, 300, 260, 20, -315, 0);
        }
        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:        // 마우스 왼쪽 버튼이 눌렸을 때 메세지가 발생한다.
        if (letterN < 15)
        {
            letterN++;
            InvalidateRect(hWnd, NULL, false);
        }
        break;

    case WM_RBUTTONDOWN:
        if (letterN > 1)
        {
            letterN--;
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

void DrawCircle(HDC hdc, int x, int y, int radius, double startAngle, double endAngle)
{
    double startX, startY, endX, endY;
    double angle = startAngle;
    startX = x + radius * cos(angle / 180 * PI);
    startY = y + radius * sin(angle / 180 * PI);
    MoveToEx(hdc, startX, startY, NULL);
    for (double angle = startAngle; angle <= endAngle; angle += 0.1)
    {
        LineTo(hdc, x + radius * cos(angle / 180 * PI), y + radius * sin(angle / 180 * PI));
    }
}