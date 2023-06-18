#include "Stdafx.h"
#include "MoleGame.h"
#include "resource1.h"
#pragma comment(lib, "msimg32.lib")

/*
과제 1. 두더지 게임
- 두더지의 수는 최소 8마리부터 시작한다.

- 화면에 현재 점수를 표기한다.

- 예외처리 :
ㄴ 두더지를 한번 클릭하면 점수 증가
ㄴ 이후 두더지가 사라질때까지 재클릭을 해도 점수가 오르면 안된다.
*/

HRESULT MoleGame::init(void)
{
	GameNode::init();
	score = 0;
	moleApperTime = RND->getFromIntTo(20, 40);
	for (int i = 0; i < 9; i++)
	{
		moles[i] = new Mole();
	}
	moleBitmap = LoadBitmap(_hInstance, MAKEINTRESOURCE(IDB_BITMAP4));
	blindBitmap = LoadBitmap(_hInstance, MAKEINTRESOURCE(IDB_BITMAP5));
	return S_OK;
}

void MoleGame::release(void)
{
	GameNode::release();
	for (int i = 0; i < 9; i++)
	{
		delete moles[i];
	}
	DeleteObject(moleBitmap);
}

void MoleGame::update(void)
{
	moleApperTime--;
	if (!moleApperTime)
	{
		moleApperTime = RND->getFromIntTo(20, 40);
		int activeN = 0;
		for (int i = 0; i < 9; i++)
		{
			if (!moles[i]->getActive() && moles[i]->getHeight() == 0)
			{
				int active = RND->getFromIntTo(0, 2);
				if (active == 0)
				{
					moles[i]->setActive(TRUE);
				}
			}
		}
	}
	for (int i = 0; i < 9; i++)
	{
		moles[i]->update();
	}
	GameNode::update();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		for (int i = 0; i < 9; i++)
		{
			if (moles[i]->checkHit(_ptMouse, i) == TRUE)
			{
				score++;
			}
		}
	}
}

void MoleGame::render(HDC hdc)
{
	// 더블버퍼링 시작
	/*GetClientRect(_hWnd, &bufferRT);
	backDC = CreateCompatibleDC(hdc);
	backBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
	oldBackBit = (HBITMAP)SelectObject(backDC, backBit);
	PatBlt(backDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
	tempDC = hdc;
	hdc = backDC;
	backDC = tempDC;*/

	// 그리기
	memDC = CreateCompatibleDC(hdc);
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	for (int i = 0; i < 9; i++)
	{
		EllipseMakeCenter(hdc, 150 + 250 * (i % 3), 150 + 150 * (i / 3), 100, 50);
		oldBitmap = (HBITMAP)SelectObject(memDC, moleBitmap);
		TransparentBlt(hdc, 100 + 250 * (i % 3), 175 + 150 * (i / 3) - moles[i]->getHeight(), 100, 75, memDC, 125, 62, 265, 392, RGB(255, 174, 201));
		SelectObject(memDC, oldBitmap);
		oldBitmap = (HBITMAP)SelectObject(memDC, blindBitmap);
		TransparentBlt(hdc, 100 + 250 * (i % 3), 150 + 150 * (i / 3), 100, 100, memDC, 0, 0, 100, 75, RGB(255, 0, 255));
	}
	SelectObject(memDC, oldBitmap);
	DeleteDC(memDC);
	MoveToEx(hdc, 0, 600, NULL);
	LineTo(hdc, 800, 600);
	char str[128];
	wsprintf(str, "score : %d", score);
	SetTextAlign(hdc, TA_CENTER);
	TextOut(hdc, WINSIZE_X / 2, 700, str, lstrlen(str));

	// 더블버퍼링 끝처리
	/*tempDC = hdc;
	hdc = backDC;
	backDC = tempDC;
	GetClientRect(_hWnd, &bufferRT);
	BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, backDC, 0, 0, SRCCOPY);
	SelectObject(backDC, oldBackBit);
	DeleteObject(backBit);
	DeleteDC(backDC);*/
}