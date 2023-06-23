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
POINT _ptMouse;

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

BOOL checkCollision(LPRECT moveRT, LPRECT stopRT)
{
    if ((moveRT->left > stopRT->left) && (moveRT->left < stopRT->right))
    {
        if ((moveRT->top > stopRT->top) && (moveRT->top < stopRT->bottom))
        {
           if ((stopRT->right - moveRT->left) >= (stopRT->bottom - moveRT->top))
            {
			   stopRT->top = moveRT->top - stopRT->bottom + stopRT->top;
			   stopRT->bottom = moveRT->top;
            }
			if ((stopRT->right - moveRT->left) <= (stopRT->bottom - moveRT->top))
			{
				stopRT->left = moveRT->left - stopRT->right + stopRT->left;
				stopRT->right = moveRT->left;
			}
            return TRUE;
        }
    }
    if ((moveRT->right > stopRT->left) && (moveRT->right < stopRT->right))
    {
        if ((moveRT->top > stopRT->top) && (moveRT->top < stopRT->bottom))
        {
			if ((moveRT->right - stopRT->left) >= (stopRT->bottom - moveRT->top))
			{
				stopRT->top = moveRT->top - stopRT->bottom + stopRT->top;
				stopRT->bottom = moveRT->top;
			}
			if ((moveRT->right - stopRT->left) <= (stopRT->bottom - moveRT->top))
			{
				stopRT->right = moveRT->right + stopRT->right - stopRT->left;
				stopRT->left = moveRT->right;
			}
            return TRUE;
        }
    }
    if ((moveRT->left > stopRT->left) && (moveRT->left < stopRT->right))
    {
        if ((moveRT->bottom > stopRT->top) && (moveRT->bottom < stopRT->bottom))
        {
			if ((stopRT->right - moveRT->left) >= (moveRT->bottom - stopRT->top))
			{
				stopRT->bottom = moveRT->bottom + stopRT->bottom - stopRT->top;
				stopRT->top = moveRT->bottom;
			}
			if ((stopRT->right - moveRT->left) <= (moveRT->bottom - stopRT->top))
			{
				stopRT->left = moveRT->left - stopRT->right + stopRT->left;
				stopRT->right = moveRT->left;
			}
            return TRUE;
        }
    }
    if ((moveRT->right > stopRT->left) && (moveRT->right < stopRT->right))
    {
        if ((moveRT->bottom > stopRT->top) && (moveRT->bottom < stopRT->bottom))
        {
			if ((moveRT->right - stopRT->left) >= (moveRT->bottom - stopRT->top))
			{
				stopRT->bottom = moveRT->bottom + stopRT->bottom - stopRT->top;
				stopRT->top = moveRT->bottom;
			}
			if ((moveRT->right - stopRT->left) <= (moveRT->bottom - stopRT->top))
			{
				stopRT->right = moveRT->right + stopRT->right - stopRT->left;
				stopRT->left = moveRT->right;
			}
            return TRUE;
        }
    }
    return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    int rtWidth = 50;
    int rtHeight = 50;
    static POINT pt;
    static POINT exPT;
    static BOOL bRT1Move = FALSE;
    static BOOL bRT2Move = FALSE;
    static BOOL bRT3Move = FALSE;
    static BOOL bRT4Move = FALSE;
    static pair<BOOL, RECT> rt[4];
    static RECT rt1 = { 50, 50, 50 + rtWidth, 50 + rtHeight };
    static RECT rt2 = { 600, 50, 600 + rtWidth, 50 + rtHeight };
    static RECT rt3 = { 600, 600, 600 + rtWidth, 600 + rtHeight };
    static RECT rt4 = { 50, 600, 50 + rtWidth, 600 + rtHeight };
    static int moveRT;
    static char str[128];
    static POINT dir[4];
    int count = 0;

    switch (iMessage)
    {
    case WM_CREATE:                 // 생성자
        rt[0] = make_pair(bRT1Move, rt1);
        rt[1] = make_pair(bRT2Move, rt2);
        rt[2] = make_pair(bRT3Move, rt3);
        rt[3] = make_pair(bRT4Move, rt4);
        for (int i = 0; i < 4; i++)
        {
            dir[i].x = 0;
            dir[i].y = 0;
        }
		SetTimer(hWnd, 1, 50, NULL);
		break;
    case WM_PAINT:                  // 출력에 관한 모든 것을 담당한다. (문자, 그림, 도형 등등 화면에 보이는 모든것)
        hdc = BeginPaint(hWnd, &ps);
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
        for (int i = 0; i < 4; i++)
        {   
            if ((i == moveRT) && (rt[moveRT].first == TRUE))
            {
                continue;
            }
            if (dir[i].x > 150)
            {
                dir[i].x = 150;
            }
            if (dir[i].x < -150)
            {
                dir[i].x = -150;
            }
            if (dir[i].y > 150)
            {
                dir[i].y = 150;
            }
            if (dir[i].y < -150)
            {
                dir[i].y = -150;
            }
            if (dir[i].x != 0)
            {
                rt[i].second.left += dir[i].x;
                rt[i].second.right += dir[i].x;
                if (rt[i].second.left < 0)
                {
                    rt[i].second.left = -rt[i].second.left;
                    rt[i].second.right = rt[i].second.left + rtWidth;
                    dir[i].x = -dir[i].x;
                }
                if (rt[i].second.right > 783)
                {
                    rt[i].second.right = 1566 - rt[i].second.right;
                    rt[i].second.left = rt[i].second.right - rtWidth;
                    dir[i].x = -dir[i].x;
                }
                dir[i].x *= 0.9;
            }
            if (dir[i].y != 0)
            {
                rt[i].second.top += dir[i].y;
                rt[i].second.bottom += dir[i].y;
				if (rt[i].second.top < 0)
				{
					rt[i].second.top = -rt[i].second.top;
					rt[i].second.bottom = rt[i].second.top + rtHeight;
					dir[i].y = -dir[i].y;
				}
				if (rt[i].second.bottom > 760)
				{
					rt[i].second.bottom = 1520 - rt[i].second.bottom;
					rt[i].second.top = rt[i].second.bottom - rtHeight;
					dir[i].y = -dir[i].y;
				}
                dir[i].y *= 0.9;
			}
            for(int j = 0; j < 4; j++)
            {
                if (i == j)
                {
                    continue;
                }
                if ((j == moveRT) && (rt[moveRT].first == TRUE))
                {
                    if (checkCollision(&rt[j].second, &rt[i].second))
                    {
                        dir[i].x = 0;
                        dir[i].y = 0;
                        continue;
                    }
                }
			    if (checkCollision(&rt[i].second, &rt[j].second) == TRUE)
			    {
				    dir[j].x += dir[i].x;
				    dir[j].y += dir[i].y;
                    dir[i].x = 0;
                    dir[i].y = 0;
			    }
            }
        }
		InvalidateRect(hWnd, NULL, true);
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
            if (rt[moveRT].second.left < 0)
            {
                rt[moveRT].second.left = 0;
                rt[moveRT].second.right = rtWidth;
            }
            if (rt[moveRT].second.right > 783)
            {
				rt[moveRT].second.right = 783;
				rt[moveRT].second.left = 783 - rtWidth;
            }
            if (rt[moveRT].second.top < 0)
            {
				rt[moveRT].second.top = 0;
				rt[moveRT].second.bottom = rtHeight;
            }
            if (rt[moveRT].second.bottom > 760)
            {
                rt[moveRT].second.bottom = 760;
                rt[moveRT].second.top = 760 - rtHeight;
            }
			for (int i = 0; i < 4; i++)
			{
				if (i == moveRT)
				{
					continue;
				}
				if (checkCollision(&rt[moveRT].second, &rt[i].second) == TRUE)
				{
					dir[i].x += pt.x - exPT.x;
					dir[i].y += pt.y - exPT.y;
				}
			}
            InvalidateRect(hWnd, NULL, true);
			if ((pt.x <= 0) || (pt.x >= 783))
			{
				rt[moveRT].first = FALSE;
                moveRT = NULL;
			}
			if ((pt.y <= 0) || (pt.y >= 760))
			{
                rt[moveRT].first = FALSE;
				moveRT = NULL;
			}
        }
        break;
    case WM_LBUTTONUP:
        rt[moveRT].first = FALSE;
        moveRT = NULL;
        break;
    case WM_DESTROY:                // 소멸자
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}