#include "Stdafx.h"
#include "GameNode.h"

// ��ü���� ���α׷��� -> ������ ����� ȿ������ ����а� ���� �ǰ�

//POINT _ptMouse;

HRESULT GameNode::init(void)
{
	// Ÿ�̸� �ʱ�ȭ
	SetTimer(_hWnd, 1, 10, NULL);

    RND->init();
    KEYMANAGER->init();

    this->setDoubleBuffer();
	// �Լ��� ���������� ���� �Ǿ����� �˸���.
	return S_OK;
}

void GameNode::setDoubleBuffer(void)
{
    _doubleBuffer = new GImage;
    _doubleBuffer->init(WINSIZE_X, WINSIZE_Y);
}

void GameNode::release(void)
{
	// �����Ҵ�� ���� �������� �ʰ� �����ϸ� �޸� ������...
	KillTimer(_hWnd, 1);

    RND->releaseSingleton();
    KEYMANAGER->releaseSingleton();

    SAFE_DELETE(_doubleBuffer);
}

void GameNode::update(void)
{
	InvalidateRect(_hWnd, NULL, true);
}

void GameNode::render(HDC hdc)
{
	//! Do Nothing
}

// ���� ���ν���
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;               
    PAINTSTRUCT ps;
    switch (iMessage)
    {
    case WM_TIMER:
        this->update();
        break;
    case WM_PAINT:                  
        hdc = BeginPaint(hWnd, &ps);
        this->render(hdc);
        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:
        _ptMouse.x = LOWORD(lParam);
        _ptMouse.y = HIWORD(lParam);
        break;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
           PostMessage(hWnd, WM_DESTROY, 0, 0);
            break;
        }
        break;
    case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
        break;
    case WM_DESTROY:                // �Ҹ���
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
