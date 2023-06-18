#include "Stdafx.h"
#include "MoleGame.h"
#include "resource1.h"
#pragma comment(lib, "msimg32.lib")

/*
���� 1. �δ��� ����
- �δ����� ���� �ּ� 8�������� �����Ѵ�.

- ȭ�鿡 ���� ������ ǥ���Ѵ�.

- ����ó�� :
�� �δ����� �ѹ� Ŭ���ϸ� ���� ����
�� ���� �δ����� ����������� ��Ŭ���� �ص� ������ ������ �ȵȴ�.
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
	// ������۸� ����
	/*GetClientRect(_hWnd, &bufferRT);
	backDC = CreateCompatibleDC(hdc);
	backBit = CreateCompatibleBitmap(hdc, bufferRT.right, bufferRT.bottom);
	oldBackBit = (HBITMAP)SelectObject(backDC, backBit);
	PatBlt(backDC, 0, 0, bufferRT.right, bufferRT.bottom, WHITENESS);
	tempDC = hdc;
	hdc = backDC;
	backDC = tempDC;*/

	// �׸���
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

	// ������۸� ��ó��
	/*tempDC = hdc;
	hdc = backDC;
	backDC = tempDC;
	GetClientRect(_hWnd, &bufferRT);
	BitBlt(hdc, 0, 0, bufferRT.right, bufferRT.bottom, backDC, 0, 0, SRCCOPY);
	SelectObject(backDC, oldBackBit);
	DeleteObject(backBit);
	DeleteDC(backDC);*/
}