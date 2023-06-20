#include "stdafx.h"
#include "Player2.h"

HRESULT Player2::init(void)
{
    Player::init();
    return S_OK;
}

HRESULT Player2::init(int _x, int _y)
{
    Player::init(_x, _y);
    return S_OK;
}

void Player2::update(void)
{
	if (KEYMANAGER->isStayKeyDown('S') && rc.bottom < WINSIZE_Y)
	{
		rc.top += PLAYER_SPEED;
		rc.bottom += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('W') && rc.top > 10)
	{
		rc.top -= PLAYER_SPEED;
		rc.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('D') && rc.right < WINSIZE_X)
	{
		rc.left += PLAYER_SPEED;
		rc.right += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('A') && rc.left > WINSIZE_X / 2)
	{
		rc.left -= PLAYER_SPEED;
		rc.right -= PLAYER_SPEED;
	}
}

void Player2::render(HDC hdc)
{
    Player::render(hdc);
}

void Player2::release(void)
{
}
