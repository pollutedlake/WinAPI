#include "stdafx.h"
#include "MakeMinimap.h"
/*
과제 2. 미니맵 만들기

- 플레이어의 움직임을 미니맵에서도 확인할 수 있어야 한다.
ㄴ 1. 화면에서 표시되는 작은 GUI 형태의 미니맵
ㄴ 2. 화면위에 그려지는 전체화면 미니맵
*/

HRESULT MakeMinimap::init(void)
{
	GameNode::init();
	_map = new GImage;
	_map->init("Resources/Images/BackGround/Map.bmp", 10666, WINSIZE_Y);
	_playerPos = { 25, WINSIZE_Y - 25 };
	_mapPos = { WINSIZE_X / 2, WINSIZE_Y / 2 };
	_isMinimap = false;
	return S_OK;
}

void MakeMinimap::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_playerPos.y -= 10;
		if (_playerPos.y < 25)
		{
			_playerPos.y = 25;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_playerPos.y += 10;
		if (_playerPos.y > WINSIZE_Y - 25)
		{
			_playerPos.y = WINSIZE_Y - 25;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_playerPos.x -= 10;
		if (_playerPos.x < 25)
		{
			_playerPos.x = 25;
			_mapPos.x -= 10;
			if (_mapPos.x < WINSIZE_X / 2)
			{
				_mapPos.x = WINSIZE_X / 2;
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_playerPos.x += 10;
		if (_playerPos.x > WINSIZE_X - 25)
		{
			_playerPos.x = WINSIZE_X - 25;
			_mapPos.x += 10;
			if (_mapPos.x > 10666 - WINSIZE_X / 2 )
			{
				_mapPos.x = 10666 - WINSIZE_X / 2;
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		_isMinimap = true;
	}
}

void MakeMinimap::release(void)
{
	GameNode::release();
}

void MakeMinimap::render(HDC hdc)
{
    HDC memDC = this->getDoubleBuffer()->getMemDC();
    PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	
	_map->render(memDC, 0, 0, _mapPos.x - WINSIZE_X / 2, _mapPos.y - WINSIZE_Y / 2, WINSIZE_X, WINSIZE_Y);
	DrawRectMake(memDC, RectMakeCenter(_playerPos.x, _playerPos.y, 50, 50));
	if (_isMinimap)
	{
		_map->alphaRender(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, 0, 0, 10666, WINSIZE_Y, 127);
	}

    this->getDoubleBuffer()->render(hdc, 0, 0);
}
