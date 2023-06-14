/*
���� 1. ���콺�� ������ ���� ���

- ���콺�� Ŭ���� ��ǥ�� ������ ������ ����Ѵ�.

- ������ ũ�� + ������ ��� + ������ �������� ��� ������ ó���Ѵ�.

- ������ ���� : �簢��, ��, �ﰢ�� �� �ٰ���

�� �ﰢ�� + �ٰ��� -> Polygon() + �迭�� �̿��Ѵ�.
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
    HDC hdc;                // �ڵ� DC
    PAINTSTRUCT ps;         // ����Ʈ ����ü
    static POINT pt;
    int type;
    static BOOL bDraw = FALSE;
    POINT apt[256];

    switch (iMessage)
    {
    case WM_CREATE:                 // ������
        break;

    case WM_PAINT:                  // ��¿� ���� ��� ���� ����Ѵ�. (����, �׸�, ���� ��� ȭ�鿡 ���̴� ����)
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

    case WM_LBUTTONDOWN:        // ���콺 ���� ��ư�� ������ �� �޼����� �߻��Ѵ�.
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

    case WM_DESTROY:                // �Ҹ���
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