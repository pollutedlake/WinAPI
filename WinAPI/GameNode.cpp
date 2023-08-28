#include "Stdafx.h"
#include "GameNode.h"

// ��ü���� ���α׷��� -> ������ ����� ȿ������ ����а� ���� �ǰ�

//POINT _ptMouse;

HRESULT GameNode::init(void)
{
	// Ÿ�̸� �ʱ�ȭ
	// �Լ��� ���������� ���� �Ǿ����� �˸���.
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
    _hdc = GetDC(_hWnd);
    _managerInit = managerInit;

    if (managerInit)
    {
        // ������ ����
        // �� ���α׷��� ��ɾ �������� ���� �־��� �ִ� ��� ���߿� � ����� ���� ����� �������� ���� ����
        setlocale(LC_ALL, "korean");
        SetTimer(_hWnd, 1, 10, NULL);

        RND->init();
        KEYMANAGER->init();
        TIMEMANAGER->init();
        IMAGEMANAGER->init();
        TEMPSOUNDMANAGER->init();
        SCENEMANAGER->init();
    }
    return S_OK;
}

void GameNode::release(void)
{
	// �����Ҵ�� ���� �������� �ʰ� �����ϸ� �޸� ������...
    if(_managerInit)
    {
	    KillTimer(_hWnd, 1);
        RND->releaseSingleton();
        KEYMANAGER->releaseSingleton();
        IMAGEMANAGER->releaseSingleton();
        EVENTMANAGER->releaseSingleton();
        TIMEMANAGER->releaseSingleton();
        TEMPSOUNDMANAGER->releaseSingleton();
        SCENEMANAGER->releaseSingleton();
    }
    ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	//InvalidateRect(_hWnd, NULL, false);
}

void GameNode::render()
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
        this->render();
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
