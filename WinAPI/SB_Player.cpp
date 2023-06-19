#include "stdafx.h"
#include "SB_Player.h"
#include "SB_Bullet.h"

HRESULT SB_Player::init(void)
{
	position.y = WINSIZE_Y;
	position.x = WINSIZE_X / 2;
	return S_OK;
}

void SB_Player::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		position.x -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		position.x += 3;
	}
}

void SB_Player::render(HDC hdc)
{
	MoveToEx(hdc, position.x - 25, position.y, NULL);
	LineTo(hdc, position.x, position.y - 25);
	LineTo(hdc, position.x + 25, position.y);
	MoveToEx(hdc, position.x, position.y - 25, NULL);
	LineTo(hdc, position.x, position.y - 75);
	MoveToEx(hdc, position.x, position.y - 50, NULL);
	LineTo(hdc, position.x - 25, position.y - 75);
	MoveToEx(hdc, position.x, position.y - 50, NULL);
	LineTo(hdc, position.x + 25, position.y - 75);
	EllipseMakeCenter(hdc, position.x, position.y - 100, 50, 50);
}

void SB_Player::release(void)
{

}
