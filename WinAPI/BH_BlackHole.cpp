#include "stdafx.h"
#include "BH_BlackHole.h"

HRESULT BH_BlackHole::init(void)
{
	_posX = WINSIZE_X / 2;
	_posY = WINSIZE_Y / 2;
	_radius = 100;
	return S_OK;
}

void BH_BlackHole::release(void)
{
}

bool BH_BlackHole::update(void)
{
	float exPosX = _posX;
	float exPosY = _posY;
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_posY -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_posY += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_posX += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_posX -= 3;
	}
	if (exPosX != _posX)
	{
		return true;
	}
	else {
		if (exPosY != _posY)
		{
			return true;
		}
	}
	return false;
}

void BH_BlackHole::render(HDC hdc)
{
	EllipseMakeCenter(hdc, _posX, _posY, _radius, _radius);
}
