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

�̹��� �߰� ����1. �δ��� ����

- ��Ȳ�� �´� �̹��� �ʼ������� �����Ѵ�.

- �δ����� ���� �� / ������ �� / �������� / ��ġ (���, ��������)

�� ���콺 Ŀ���� ShowCursor()�� �̿��Ѵ�.
*/

HRESULT MoleGame::init(void)
{
	GameNode::init();
	score = 0;
	moleApperTime = RND->getFromIntTo(100, 200);
	for (int i = 0; i < 9; i++)
	{
		moles[i] = new Mole();
	}
	_moleImage[0] = new GImage;
	_moleImage[1] = new GImage;
	_moleImage[0]->init("Resources/Images/Object/mole.bmp", 100, 75, true, RGB(255, 0, 255));
	_moleImage[1]->init("Resources/Images/Object/HittedMole.bmp", 100, 75, true, RGB(255, 0, 255));
	_moleIndex = 0;
	_moleReturnTime = 0;

	_hammerImage[0] = new GImage;
	_hammerImage[1] = new GImage;
	_hammerImage[0]->init("Resources/Images/Object/Hammer.bmp", 50, 100, true, RGB(255, 0, 255));
	_hammerImage[1]->init("Resources/Images/Object/HitHammer.bmp", 100, 50, true, RGB(255, 0, 255));
	_hammerIndex = 0;
	_hammerReturnTime = 0;

	_moleScreen = new GImage;
	_moleScreen->init("Resources/Images/BackGround/MoleScreen.bmp", 100, 100, true, RGB(255, 0, 255));
	ShowCursor(false);
	return S_OK;
}

void MoleGame::release(void)
{
	GameNode::release();
	for (int i = 0; i < 9; i++)
	{
		SAFE_DELETE(moles[i]);
	}
	SAFE_DELETE(_moleImage[0]);
	SAFE_DELETE(_moleImage[1]);
	SAFE_DELETE(_hammerImage[0]);
	SAFE_DELETE(_hammerImage[1]);
}

void MoleGame::update(void)
{
	GameNode::update();
	moleApperTime--;
	if (!moleApperTime)
	{
		moleApperTime = RND->getFromIntTo(100, 200);
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
	_hammerReturnTime += 10;
	if (_hammerReturnTime > 20)
	{
		_hammerIndex = 0;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_hammerIndex = 1;
		_hammerReturnTime = 0;
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
	// �׸���
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	SelectObject(memDC, GetStockObject(BLACK_BRUSH));
	for (int i = 0; i < 9; i++)
	{
		EllipseMakeCenter(memDC, 150 + 250 * (i % 3), 150 + 150 * (i / 3), 100, 50);
		_moleImage[moles[i]->getIsRed()]->render(memDC, 100 + 250 * (i % 3), 175 + 150 * (i / 3) - moles[i]->getHeight());
		_moleScreen->render(memDC, 100 + 250 * (i % 3), 150 + 150 * (i / 3));
		if(_hammerIndex == 0)
		{
			_hammerImage[0]->render(memDC, _ptMouse.x - 25, _ptMouse.y - 100);
		}
		else
		{
			_hammerImage[1]->render(memDC, _ptMouse.x - 100, _ptMouse.y - 25);
		}
	}
	MoveToEx(memDC, 0, 600, NULL);
	LineTo(memDC, 800, 600);
	char str[128];
	wsprintf(str, "score : %d", score);
	SetTextAlign(memDC, TA_CENTER);
	TextOut(memDC, WINSIZE_X / 2, 700, str, lstrlen(str));
	this->getDoubleBuffer()->render(hdc, 0, 0);
}