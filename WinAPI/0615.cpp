#include "Stdafx.h"

#define MOLEGAME             1
#define CLAYSHOOTING         2
#define FINDCARDPAIR         3
#define MAINGAME             4
#define SHOOTBULLET          5
#define AVOIDPOOP            6
#define CROCODILETEETH       7
#define VERTICALSHOOTING     8
#define HORIZONTALSHOOTING   9
#define FINDWRONGPAINT       10
#define ANALOGCLOCK          11
#define CANNONSHOOT          12
#define ROTATEFIGURE         13
#define SLICEGAME            14
#define MINIMAP              15
#define EARTHWORMGAME        16

#define ASSIGNMENT      EARTHWORMGAME

#if ASSIGNMENT == MOLEGAME

#include "MoleGame.h"
MoleGame* _mg;

#elif ASSIGNMENT == CLAYSHOOTING

#include "ClayShooting.h"
ClayShooting* _mg;

#elif ASSIGNMENT == FINDCARDPAIR

#include "FindCardPair.h"
FindCardPair* _mg;

#elif ASSIGNMENT == MAINGAME
#include "MainGame.h"
MainGame* _mg;

#elif ASSIGNMENT == SHOOTBULLET
#include "ShootBullet.h"
ShootBullet* _mg;

#elif ASSIGNMENT == AVOIDPOOP
#include "AvoidPoop.h"
AvoidPoop* _mg;

#elif ASSIGNMENT == CROCODILETEETH
#include "CrocodileTeeth.h"
CrocodileTeeth* _mg;

#elif ASSIGNMENT == VERTICALSHOOTING
#include "VerticalShooting.h"
VerticalShooting* _mg;

#elif ASSIGNMENT == HORIZONTALSHOOTING
#include "HorizontalShooting.h"
HorizontalShooting* _mg;

#elif ASSIGNMENT == FINDWRONGPAINT
#include "FindWrongPaint.h"
FindWrongPaint* _mg;

#elif ASSIGNMENT == ANALOGCLOCK
#include "AnalogClock.h"
AnalogClock* _mg;

#elif ASSIGNMENT == CANNONSHOOT
#include "CannonShoot.h"
CannonShoot* _mg;

#elif ASSIGNMENT == ROTATEFIGURE
#include "RotateFigure.h"
RotateFigure* _mg;

#elif ASSIGNMENT == SLICEGAME
#include "SliceGame.h"
SliceGame* _mg;

#elif ASSIGNMENT == MINIMAP
#include "MakeMinimap.h"
MakeMinimap* _mg;

#elif ASSIGNMENT == EARTHWORMGAME
#include "EarthWormGame.h"
EarthWormGame* _mg;

#endif

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int, int, int, int);

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpszCmdParam,
    int       nCmdShow)
{

#if ASSIGNMENT == MOLEGAME
    _mg = new MoleGame();
#elif ASSIGNMENT == CLAYSHOOTING
    _mg = new ClayShooting();
#elif ASSIGNMENT == FINDCARDPAIR
    _mg = new FindCardPair();
#elif ASSIGNMENT == MAINGAME
    _mg = new MainGame();
#elif ASSIGNMENT == SHOOTBULLET
    _mg = new ShootBullet();
#elif ASSIGNMENT == AVOIDPOOP
    _mg = new AvoidPoop();
#elif ASSIGNMENT == CROCODILETEETH
    _mg = new CrocodileTeeth();
#elif ASSIGNMENT == VERTICALSHOOTING
    _mg = new VerticalShooting();
#elif ASSIGNMENT == HORIZONTALSHOOTING
    _mg = new HorizontalShooting();
#elif ASSIGNMENT == FINDWRONGPAINT
	_mg = new FindWrongPaint();
#elif ASSIGNMENT == ANALOGCLOCK
    _mg = new AnalogClock();
#elif ASSIGNMENT == CANNONSHOOT
    _mg = new CannonShoot();
#elif ASSIGNMENT == ROTATEFIGURE
	_mg = new RotateFigure();
#elif ASSIGNMENT == SLICEGAME
    _mg = new SliceGame();
#elif ASSIGNMENT == MINIMAP
    _mg = new MakeMinimap();

#elif ASSIGNMENT == EARTHWORMGAME
	_mg = new EarthWormGame();
#endif

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
    if (FAILED(_mg->init()))
    {
        return 0;
    }

    MSG message;

    while (GetMessage(&message, 0, 0, 0))
    {

        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    _mg->release();
    UnregisterClass(WINNAME, hInstance);

    return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    AdjustWindowRect(&rc, WINSTYLE, false);

    SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);
}