#include "Stdafx.h"

#define MOLEGAME        1
#define CLAYSHOOTING    2
#define FINDCARDPAIR    3
#define MAINGAME        4
#define SHOOTBULLET     5
#define AVOIDPOOP       6
#define CROCODILETEETH  7

#define ASSIGNMENT      CROCODILETEETH

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

#endif

HINSTANCE _hInstance;
HWND _hWnd;

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
#endif

    _hInstance = hInstance;

    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;                                                    // Ŭ���� ���� �޸�
    wndClass.cbWndExtra = 0;                                                    // ������ ���� �޸�
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);               // ��׶���
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);                             // ���콺 Ŀ��
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           // ������
    wndClass.hInstance = hInstance;                                             // �����츦 �ҿ��� ���α׷��� �ĺ��� ����
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                                    // ������ ���ν���
    wndClass.lpszClassName = WINNAME;                                        // Ŭ���� �̸� (�ĺ��� ����)
    wndClass.lpszMenuName = NULL;                                               // �޴� �̸�
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                   // ������ ��Ÿ�� (�ٽ� �׸��� ����)

    RegisterClass(&wndClass);

    _hWnd = CreateWindow
    (
        WINNAME,                     // ������ Ŭ���� �ĺ���
        WINNAME,                     // ������ Ÿ��Ʋ �� �̸�
        WINSTYLE,            // ������ ��Ÿ��
        WINSTART_X,                            // ������ ȭ�� X ��ǥ
        WINSTART_Y,                            // ������ ȭ�� Y ��ǥ
        WINSIZE_X,                            // ������ ȭ�� ���� ũ��
        WINSIZE_Y,                            // ������ ȭ�� ���� ũ��
        NULL,                           // �θ� ������ -> GetDsktopWindow
        (HMENU)NULL,                    // �޴� �ڵ�
        hInstance,                      // �ν��Ͻ� ����
        NULL                            // �������� �ڽ� �����츦 �����ϸ� �����ϰ� �׷��� �ʴٸ� NULL
                                        // �� �ʿ信 ���ؼ� ����ϱ⵵ ������ ������ NULL
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