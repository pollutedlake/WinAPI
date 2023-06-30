#include "stdafx.h"
#include "CTW_BackGround.h"

HRESULT CTW_BackGround::init(bool managerInit)
{
	if(managerInit)
	{
		_backGround = IMAGEMANAGER->addImage("BackGround", "Resources/Images/CatchTheWall/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);
		_rc[0] = {0, WINSIZE_Y - 50, WINSIZE_X, WINSIZE_Y};
		_rc[1] = {0, WINSIZE_Y - 300, 200, WINSIZE_Y - 50};
		_rc[2] = {100, WINSIZE_Y - 100, 200, WINSIZE_Y - 50};
		_rc[3] = {WINSIZE_X / 2 - 200, 200, WINSIZE_X / 2 + 200, WINSIZE_Y / 2};
		_rc[4] = {WINSIZE_X - 200, 0, WINSIZE_X, WINSIZE_Y - 50};
		_rc[5] = {-100, 0, 0, WINSIZE_Y};
		_rc[6] = {WINSIZE_X, 0, WINSIZE_X + 100, WINSIZE_Y};
	}
	return S_OK;
}

void CTW_BackGround::release(void)
{
	SAFE_DELETE(_backGround);
}

void CTW_BackGround::update(void)
{
	
}

void CTW_BackGround::render(void)
{
	_backGround->render(getMemDC());
	for (int i = 0; i < 5; i++)
	{
		FillRect(getMemDC(), &_rc[i], (HBRUSH)GetStockObject(BLACK_BRUSH));
	}
}
