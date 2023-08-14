#include "stdafx.h"
#include "TileMap.h"

HRESULT TileMap::init(void)
{
	for (int i = 0; i < 100; i++)
	{
		bitset<100> rowTiles;
		_tileMap.push_back(rowTiles);
		ZeroMemory(&_tileMap[i], sizeof(bitset<100>));
	}
	_image = IMAGEMANAGER->addImage("╥ндо", "Resources/Images/ShootingGame/Rocket.bmp", 52, 64);
	_index = 0;
	_input = true;
	_click = false;
	return S_OK;
}

void TileMap::release(void)
{
}

void TileMap::update(void)
{
	if(!_input)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_tileMap[_ptMouse.y / _tileHeight].test(_ptMouse.x / _tileWidth))
			{
				_tileMap[_ptMouse.y / _tileHeight].set((_ptMouse.x / _tileWidth), 0);
				_offset.x = _ptMouse.x - (int)(_ptMouse.x / _tileWidth) * _tileWidth;
				_offset.y = _ptMouse.y - (int)(_ptMouse.y / _tileHeight) * _tileHeight;
				_click = true;
			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (!_tileMap[_ptMouse.y / _tileHeight].test(_ptMouse.x / _tileWidth) && _click)
			{
				_tileMap[_ptMouse.y / _tileHeight].set((_ptMouse.x / _tileWidth), 1);
				_click = false;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_input = true;
		}
	}
	else
	{
		for (int i = 48; i < 58; i++)
		{
			if (KEYMANAGER->isOnceKeyDown(i))
			{
				_tileSizeChar[_index] = i;
				_index++;
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_tileSizeChar[_index] = '\0';
			int count = 0;
			_tileSize = 0;
			for (int i = strlen(_tileSizeChar) - 1; i >= 0; i--)
			{
				_tileSize += pow(10, count) * ((int)_tileSizeChar[i] - 48);
				count++;
			}
			_tileWidth = (float)WINSIZE_X / (float)_tileSize;
			_tileHeight = (float)WINSIZE_Y / (float)_tileSize;
			_index = 0;
			memset(_tileSizeChar, '\0', sizeof(char) * 20);
			for (int i = 0; i < 100; i++)
			{
				_tileMap[i].reset();
			}
			for (int i = 0; i < 2; i++)
			{
				int x, y;
				do
				{
					x = RND->getInt(_tileSize);
					y = RND->getInt(_tileSize);
				} while (_tileMap[y].test(x));
				_tileMap[y].set(x);
			}
			_input = false;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_input = false;
		}
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
				//FillRect(getMemDC(), &RectMakeCenter(_tileWidth * j + _tileWidth / 2, _tileHeight * i + _tileHeight / 2, _tileWidth, _tileHeight), WHITE_BRUSH);
				_image->render(getMemDC(), _tileWidth * j, _tileHeight * i, _tileWidth, _tileHeight, 0, 0, _image->getWidth(), _image->getHeight());
			}
		}
	}
	HPEN myPen = CreatePen(CW_DEFAULT, 1, RGB(255, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	for (int i = 0; i < _tileSize; i++)
	{
		LineMake(getMemDC(), _tileWidth * (i + 1), 0, _tileWidth * (i + 1), _tileHeight * _tileSize);
	}
	for (int i = 0; i < _tileSize; i++)
	{
		LineMake(getMemDC(), 0, _tileHeight * (i + 1), _tileWidth * _tileSize, _tileHeight * (i + 1));
	}
	SelectObject(getMemDC(), oldPen);
	DeleteObject(myPen);
	if (_input)
	{
		HBRUSH inputBrush = CreateSolidBrush(RGB(255, 0, 255));
		FillRect(getMemDC(), &RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 400, 200), inputBrush);
		FillRect(getMemDC(), &RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 200, 50), WHITE_BRUSH);
		TextOut(getMemDC(), WINSIZE_X / 2 - 100, WINSIZE_Y / 2, _tileSizeChar, strlen(_tileSizeChar));
	}
	else
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _click)
		{
			_image->render(getMemDC(), _ptMouse.x - _offset.x, _ptMouse.y - _offset.y, _tileWidth, _tileHeight, 0, 0, _image->getWidth(), _image->getHeight());
		}
	}
}
