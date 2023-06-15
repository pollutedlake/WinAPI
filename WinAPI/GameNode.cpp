#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	// 타이머 초기화
	SetTimer(_hWnd, 1, 1, NULL);

	// 함수가 성공적으로 실행 되었음을 알린다.
	return S_OK;
}

void GameNode::release(void)
{
	// 동적할당과 같이 삭제하지 않고 종료하면 메모리 줄줄줄...
	KillTimer(_hWnd, 1);
}

void GameNode::update(void)
{
	InvalidateRect(_hWnd, NULL, true);
}

void GameNode::render(HDC hdc)
{
	//! Do Nothing
}

// 메인 프로시저
LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;               
    PAINTSTRUCT ps;
    _hWNd = hWnd;
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
        pt.x = LOWORD(lParam);
        pt.y = HIWORD(lParam);
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
        break;
    case WM_DESTROY:                // 소멸자
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
