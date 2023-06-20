#include "stdafx.h"
#include "HS_Player2.h"

HRESULT HS_Player2::init(void)
{
	HS_Player::init();
    return S_OK;
}

HRESULT HS_Player2::init(int _x, int _y)
{
	HS_Player::init(_x, _y);
	skill1 = false;
	count = 0;
	skill1Time = 5000;
    return S_OK;
}

void HS_Player2::update(void)
{
	
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && rc.bottom < WINSIZE_Y)
	{
		position.y += PLAYER_SPEED;
		rc.top += PLAYER_SPEED;
		rc.bottom += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && rc.top > 10)
	{
		position.y -= PLAYER_SPEED;
		rc.top -= PLAYER_SPEED;
		rc.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && rc.right < WINSIZE_X)
	{
		position.x += PLAYER_SPEED;
		rc.left += PLAYER_SPEED;
		rc.right += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && rc.left > WINSIZE_X / 2)
	{
		position.x -= PLAYER_SPEED;
		rc.left -= PLAYER_SPEED;
		rc.right -= PLAYER_SPEED;
	}
	if (skill1)
	{
		count += 10;
		if (skill1Time < count)
		{
			skill1 = false;
			count = 0;
		}
	}
}

void HS_Player2::render(HDC hdc)
{
	HS_Player::render(hdc);
	if(skill1)
	{
		EllipseMakeCenter(hdc, position.x, position.y + PLAYERHEIGHT * 3 / 4, PLAYERHEIGHT / 2, PLAYERHEIGHT / 2);
		EllipseMakeCenter(hdc, position.x, position.y - PLAYERHEIGHT * 3 / 4, PLAYERHEIGHT / 2, PLAYERHEIGHT / 2);
	}
}

void HS_Player2::release(void)
{
	HS_Player::release();
}

bool HS_Player2::shoot()
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		return true;
	}
	return false;
}

bool HS_Player2::useSkill1()
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		skill1 = true;
		return true;
	}
	return false;
}

bool HS_Player2::useSkill2()
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
	{
		return true;
	}
	return false;
}
