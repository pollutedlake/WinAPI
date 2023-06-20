#include "stdafx.h"
#include "HS_Player1.h"

HRESULT HS_Player1::init(void)
{
	HS_Player::init();
	return S_OK;
}

HRESULT HS_Player1::init(int _x, int _y)
{
	HS_Player::init(_x, _y);
	chargeShot = false;
	chargeTime = 0;
	chargeShotTime = 0;
	return S_OK;
}

void HS_Player1::update(void)
{
	if (KEYMANAGER->isStayKeyDown('S') && position.y < WINSIZE_Y - 20)
	{
		position.y += PLAYER_SPEED;
		rc.top += PLAYER_SPEED;
		rc.bottom += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('W') && position.y > 30)
	{
		position.y -= PLAYER_SPEED;
		rc.top -= PLAYER_SPEED;
		rc.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('D') && position.x < WINSIZE_X / 2 - 20)
	{
		position.x += PLAYER_SPEED;
		rc.left += PLAYER_SPEED;
		rc.right += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('A') && position.x > 20)
	{
		position.x -= PLAYER_SPEED;
		rc.left -= PLAYER_SPEED;
		rc.right -= PLAYER_SPEED;
	}
	if (chargeShot && chargeTime == 0)
	{
		chargeShotTime += 10;
		if (chargeShotTime > 2000)
		{
			chargeShot = false;
		}
	}
}

void HS_Player1::render(HDC hdc)
{
	HS_Player::render(hdc);
}

void HS_Player1::release(void)
{
	HS_Player::release();
}

bool HS_Player1::shoot()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && !chargeShot)
	{
		return true;
	}
	return false;
}

bool HS_Player1::useSkill1()
{
	if (KEYMANAGER->isOnceKeyDown('Q') && !chargeShot)
	{
		return true;
	}
	return false;
}

bool HS_Player1::useSkill2()
{
	if (KEYMANAGER->isStayKeyDown('E'))
	{
		chargeTime += 10;
		chargeShot = true;
	}
	if (KEYMANAGER->isOnceKeyUp('E'))
	{
		bool returnValue = chargeTime >= 3000;
		chargeTime = 0;
		return returnValue;
	}
	return false;
}
