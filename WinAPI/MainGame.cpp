/*
과제1.카드 짝 맞추기

- 사이즈 : 5 x 4

- 카드 짝을 맞추면 맞춘 카드는 계속 오픈되어야 한다.

- 치트 필수
ㄴ 1. 전부 오픈 후 일정 시간 후 다시 감추기
ㄴ 2. 1쌍을 제외하고 나머지는 전부 오픈되고 유저가 1쌍을 맞추면서 종료

※ HBRUSH
*/

#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		rc.top += 3;
		rc.bottom += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		rc.top -= 3;
		rc.bottom -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		rc.left -= 3;
		rc.right -= 3;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		rc.left += 3;
		rc.right += 3;
	}
}

void MainGame::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
}