#include "stdafx.h"
#include "AP_Player.h"

HRESULT AP_Player::init(void)
{
	position.x = WINSIZE_X / 2;
	position.y = WINSIZE_Y;
	dirX = 0;
	speed = 3;
	return S_OK;
}

void AP_Player::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		dirX = -1;
		position.x += dirX * speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		dirX = 1;
		position.x += dirX * speed;
	}
}

void AP_Player::render(HDC hdc)
{
	MoveToEx(hdc, position.x - 25, position.y, NULL);
	LineTo(hdc, position.x, position.y - 25);
	LineTo(hdc, position.x + 25, position.y);
	MoveToEx(hdc, position.x, position.y - 25, NULL);
	LineTo(hdc, position.x, position.y - 75);
	if (dirX > 0)
	{
		MoveToEx(hdc, position.x, position.y - 50, NULL);
		LineTo(hdc, position.x - 25, position.y - 25);
		MoveToEx(hdc, position.x, position.y - 50, NULL);
		LineTo(hdc, position.x + 25, position.y - 75);
	}
	else if (dirX < 0)
	{
		MoveToEx(hdc, position.x, position.y - 50, NULL);
		LineTo(hdc, position.x - 25, position.y - 75);
		MoveToEx(hdc, position.x, position.y - 50, NULL);
		LineTo(hdc, position.x + 25, position.y - 25);
	}
	else
	{
		MoveToEx(hdc, position.x, position.y - 50, NULL);
		LineTo(hdc, position.x - 25, position.y - 75);
		MoveToEx(hdc, position.x, position.y - 50, NULL);
		LineTo(hdc, position.x + 25, position.y - 75);
	}
	EllipseMakeCenter(hdc, position.x, position.y - 100, 50, 50);
}

void AP_Player::release(void)
{

}
