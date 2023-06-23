#include "stdafx.h"
#include "CS_Shell.h"

HRESULT CS_Shell::init(void)
{
	active = false;
	gravity = false;
	gravitySpeed = 0.0f;
	return S_OK;
}

void CS_Shell::release(void)
{
}

void CS_Shell::update(void)
{
	speedX = 5 * cos(angle);
	speedY = 5 * sin(angle);
	if (active == true)
	{	
		position.x += speedX;
		position.y += speedY + gravitySpeed;
		if (position.x - 25 < 0)
		{
			position.x = 25;
			angle = PI - angle;
		}
		if (position.x + 25 > WINSIZE_X)
		{
			position.x = WINSIZE_X - 25;
			angle = PI - angle;
		}
		if (position.y - 25 < 0)
		{
			position.y = 25;
			angle = 2* PI - angle;
		}
		if (gravity == true)
		{
			if (position.y + 25 > WINSIZE_Y)
			{
				gravitySpeed = 0.0f;
				active = false;
			}
		}
		else
		{
			if (position.y + 25 > WINSIZE_Y)
			{
				position.y = WINSIZE_Y - 25;
				angle = 2 * PI - angle;
			}
		}
		if (gravity == true)
		{
			gravitySpeed += 0.1;
		}
		else {
			gravitySpeed = 0.0f;
		}
	}
}

void CS_Shell::render(HDC hdc)
{
	EllipseMakeCenter(hdc, position.x, position.y, 50, 50);
}

void CS_Shell::fire(LONG _positionX, LONG _positionY, float _angle)
{
	position.x = _positionX;
	position.y = _positionY;
	angle = _angle / 180.0f * PI;
	active = true;
}

void CS_Shell::move(float _moveX, float _moveY)
{
	position.x += _moveX;
	position.y += _moveY;
}

bool CS_Shell::collisionCheck(POINT _otherPos)
{
	if (pow(position.x - _otherPos.x, 2) + pow(position.y - _otherPos.y, 2) < 2500)
	{
		return true;
	}
	return false;
}
