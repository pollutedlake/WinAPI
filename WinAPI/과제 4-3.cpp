/*
과제 3. 사각형 4단 밀기

- 사각형의 갯수는 총 4개

- 마우스로 화면에 그려진 4개의 사각형 중 아무거나 선택해 자유롭게 움직인다.

- 마우스로 움직이고 있는 사각형이 다른 사각형과 충돌되면 충돌된 사각형은 "자연스럽게" 밀려난다.

※ 관성 / 그럴싸 보이게
ㄴ 에어하키

한줄 조사. 디자인 패턴

- 싱글톤 + @ 4개
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
    case WM_CREATE:                 // 생성자
        rt[0] = make_pair(bRT1Move, rt1);
        rt[1] = make_pair(bRT2Move, rt2);
        rt[2] = make_pair(bRT3Move, rt3);
        rt[3] = make_pair(bRT4Move, rt4);
        break;
    case WM_PAINT:                  // 출력에 관한 모든 것을 담당한다. (문자, 그림, 도형 등등 화면에 보이는 모든것)
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
    case WM_DESTROY:                // 소멸자
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}