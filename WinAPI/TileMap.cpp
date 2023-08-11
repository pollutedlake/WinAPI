#include "stdafx.h"
#include "TileMap.h"

HRESULT TileMap::init(void)
{
	for (int i = 0; i < 100; i++)
	{
		bitset<100> rowTiles;
		rowTiles.reset();
		_tileMap.push_back(rowTiles);
	}
	//ZeroMemory(&_tileMap, 10000);
	//scanf_s("%d", &_tileSize);
	_image = IMAGEMANAGER->addImage("╥ндо", "Resources/Images/ShootingGame/Rocket.bmp", 52, 64);
	_tileSize = 20;
	_tileWidth = WINSIZE_X / _tileSize;
	_tileHeight = WINSIZE_Y / _tileSize;
	for(int i = 0; i < 2; i++)
	{
		int x, y;
		do
		{
			x = RND->getInt(_tileSize);
			y = RND->getInt(_tileSize);
		} while(_tileMap[y].test(x));
		_tileMap[y].set(x);
	}
	return S_OK;
}

void TileMap::release(void)
{
}

void TileMap::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_tileMap[_ptMouse.y / _tileHeight].test(_ptMouse.x / _tileWidth))
		{

		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{

	}
}

void TileMap::render(void)
{
	for (int i = 0; i < _tileSize; i++)
	{
		for (int j = 0; j < _tileSize; j++)
		{
			if (_tileMap[i].test(j))
			{
				_image->render(getMemDC(), _tileWidth * j, _tileHeight * i, _tileWidth, _tileHeight, 0, 0, _image->getWidth(), _image->getHeight());
			}
		}
	}
	HPEN myPen = CreatePen(CW_DEFAULT, 1, RGB(255, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	for (int i = 0; i < _tileSize; i++)
	{
		LineMake(getMemDC(), _tileWidth * (i+1), 0, _tileWidth * (i+1), _tileHeight * _tileSize);
	}
	for (int i = 0; i < _tileSize; i++)
	{
		LineMake(getMemDC(), 0, _tileHeight * (i + 1), _tileWidth * _tileSize, _tileHeight * (i + 1));
	}
	SelectObject(getMemDC(), oldPen);
	DeleteObject(myPen);
}
