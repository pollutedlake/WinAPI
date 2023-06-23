#include "stdafx.h"
#include "CS_Shell.h"

HRESULT CS_Shell::init(void)
{
	active = false;
	gravity = false;
	return S_OK;
}

void CS_Shell::release(void)
{
}

void CS_Shell::update(void)
{
	if (active == true)
	{	
		position.x += speedX;
		position.y += speedY;
		if (position.x - 25 < 0)
		{
			position.x = 25;
			speedX *= -1;
		}
		if (position.x + 25 > WINSIZE_X)
		{
			position.x = WINSIZE_X - 25;
			speedX *= -1;
		}
		if (gravity == true)
		{
			if (position.y - 25 < 0)
			{
				position.y = 25;
				speedY *= -1;
			}
			if (position.y + 25 > WINSIZE_Y)
			{
				active = false;
			}
		}
		else
		{
			if (position.y - 25 < 0)
			{
				position.y = 25;
				speedY *= -1;
			}
			if (position.y + 25 > WINSIZE_Y)
			{
				position.y = WINSIZE_Y - 25;
				speedY *= -1;
			}
		}
		if (gravity == true)
		{
			speedY += 0.1;
		}
	}
}

void CS_Shell::render(HDC hdc)
{
	EllipseMakeCenter(hdc, position.x, position.y, 50, 50);
}

void CS_Shell::fire(LONG _positionX, LONG _positionY, float _speedX, float _speedY)
{
	position.x = _positionX;
	position.y = _positionY;
	speedX = _speedX;
	speedY = _speedY;
	active = true;
}

bool CS_Shell::collisionCheck(POINT _otherPos)
{
	if (pow(position.x - _otherPos.x, 2) + pow(position.y - _otherPos.y, 2) < 625)
	{
		return true;
	}
	return false;
}
