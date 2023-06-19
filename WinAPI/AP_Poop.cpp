#include "stdafx.h"
#include "AP_Poop.h"

HRESULT AP_Poop::init(void)
{
	position.x = RND->getFromIntTo(10, WINSIZE_X - 10);
	position.y = 0;
	dir = { 0, 1 };
	speed = RND->getFromIntTo(3, 10);
	return S_OK;
	isActive = true;
}

void AP_Poop::update(void)
{
	position.y += dir.y * speed;
	if (position.y > WINSIZE_Y + 10)
	{
		isActive = false;
	}
}

void AP_Poop::render(HDC hdc)
{
	DrawRectMake(hdc, RectMakeCenter(position.x, position.y, 20, 20));
}

void AP_Poop::release(void)
{

}
