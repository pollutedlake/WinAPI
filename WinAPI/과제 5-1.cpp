/*
과제 1. 마우스로 무작위 도형 출력

- 마우스로 클릭한 좌표에 무작위 도형을 출력한다.

- 도형의 크기 + 도형의 모양 + 도형의 종류까지 모두 무작위 처리한다.

- 도형의 종류 : 사각형, 원, 삼각형 및 다각형

※ 삼각형 + 다각형 -> Polygon() + 배열을 이용한다.
*/
#include "Stdafx.h"
#define PI 3.141592

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
    static POINT pt;
    int type;
    static BOOL bDraw = FALSE;
    POINT apt[256];

    switch (iMessage)
    {
    case WM_CREATE:                 // 생성자
        break;

    case WM_PAINT:                  // 출력에 관한 모든 것을 담당한다. (문자, 그림, 도형 등등 화면에 보이는 모든것)
        hdc = BeginPaint(hWnd, &ps);
        if (bDraw == TRUE)
        {
            type = RND->getFromIntTo(0, 1);
            switch (type)
            {
            case 0:
                EllipseMakeCenter(hdc, pt.x, pt.y, RND->getFromIntTo(1, 400), RND->getFromIntTo(1, 400));
                break;
            case 1:
                int num = RND->getFromIntTo(3, 8);
                int xSum = 0;
                int ySum = 0;
                float lastAngle;
                float firstAngle = RND->getFromFloatTo(0.f, 360.f);
                lastAngle = firstAngle;
                float r = RND->getFromFloatTo(1, 400);
                apt[0].x = pt.x + r * cos(firstAngle / (float)180 * PI);
                apt[0].y = pt.y + r * sin(firstAngle / (float)180 * PI);
                xSum += apt[0].x;
                ySum += apt[0].y;
                for (int i = 1; i < num; i++)
                {
                    r = RND->getFromFloatTo(1, 400);
                    float angle = RND->getFromFloatTo(lastAngle, firstAngle + 360.f);
                    lastAngle = angle;
                    apt[i].x = pt.x + r * cos(angle / (float)180 * PI);
                    apt[i].y = pt.y + r * sin(angle / (float)180 * PI);
                    xSum += apt[i].x;
                    ySum += apt[i].y;
                }
                for (int i = 0; i < num; i++)
                {
                    apt[i].x += pt.x - xSum / num;
                    apt[i].y += pt.y - ySum / num;
                }
                for (int i = 0; i < num - 1; i++)
                {
                    for (int j = i + 1; j < num; j++)
                    {
                        if (apt[i].y < apt[j].y)
                        {
                            POINT temp = apt[i];
                            apt[i] = apt[j];
                            apt[j] = temp;
                        }
                        else if (apt[i].y == apt[j].y)
                        {
                            if (apt[i].x < apt[j].x)
                            {
                                POINT temp = apt[i];
                                apt[i] = apt[j];
                                apt[j] = temp;
                            }
                        }
                    }
                }
                for (int i = 1; i < num - 1; i++)
                {
                    for (int j = i + 1; j < num; j++)
                    {
                        double inclinationI = ((double)(apt[i].y - apt[0].y) / (double)(apt[i].x - apt[0].x));
                        double inclinationJ = ((double)(apt[j].y - apt[0].y) / (double)(apt[j].x - apt[0].x));
                        if (inclinationI > 0 && inclinationJ > 0)
                        {
                            if (inclinationI > inclinationJ)
                            {
								POINT temp = apt[i];
								apt[i] = apt[j];
								apt[j] = temp;
                            }
                        }
                        else if (inclinationI < 0 && inclinationJ > 0)
                        {
							POINT temp = apt[i];
							apt[i] = apt[j];
							apt[j] = temp;
                        }
                        else if (inclinationI < 0 && inclinationJ < 0)
                        {
                            if (inclinationI > inclinationJ)
                            {
								POINT temp = apt[i];
								apt[i] = apt[j];
								apt[j] = temp;
                            }
                        }
                    }
                }
                Polygon(hdc, apt, num);
                break;
            }
        }
        EndPaint(hWnd, &ps);
        break;

    case WM_LBUTTONDOWN:        // 마우스 왼쪽 버튼이 눌렸을 때 메세지가 발생한다.
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
        bDraw = TRUE;
        InvalidateRect(hWnd, NULL, true);
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