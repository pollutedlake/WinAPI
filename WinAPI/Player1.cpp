#include "stdafx.h"
#include "Player1.h"

HRESULT Player1::init(void)
{
	Player::init();
	return S_OK;
}

HRESULT Player1::init(int _x, int _y)
{
	Player::init(_x, _y);
	return S_OK;
}

void Player1::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && rc.bottom < WINSIZE_Y)
	{
		rc.top += PLAYER_SPEED;
		rc.bottom += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && rc.top > 10)
	{
		rc.top -= PLAYER_SPEED;
		rc.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && rc.right < WINSIZE_X / 2)
	{
		rc.left += PLAYER_SPEED;
		rc.right += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && rc.left > 0)
	{
		rc.left -= PLAYER_SPEED;
		rc.right -= PLAYER_SPEED;
	}
}

void Player1::render(HDC hdc)
{
	Player::render(hdc);
}

void Player1::release(void)
{
}
