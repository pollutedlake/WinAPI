#include "stdafx.h"
#include "EWG_EarthWorm.h"

HRESULT EWG_EarthWorm::init(void)
{
	_speed = 5.0f;

	int sector = RND->getInt(4);
	_circles[0]._positionX = RND->getFromIntTo(25, WINSIZE_X - 25);
	_circles[0]._positionY = RND->getFromIntTo(25, WINSIZE_Y - 25);
	if (_circles[0]._positionX < WINSIZE_X / 2)
	{
		_circles[0]._positionX -= WINSIZE_X / 2;
	}
	else
	{
		_circles[0]._positionX += WINSIZE_X / 2;
	}
	if (_circles[0]._positionY < WINSIZE_Y / 2)
	{
		_circles[0]._positionY -= WINSIZE_Y / 2;
	}
	else
	{
		_circles[0]._positionY += WINSIZE_Y / 2;
	}
	_angle = atan((float)(WINSIZE_Y / 2 - _circles[0]._positionY) / (float)(WINSIZE_X / 2 - _circles[0]._positionX));
	if (_angle < 0 && _circles[0]._positionY < 0)
	{
		_angle += PI;
	}
	else if (_angle > 0 && _circles[0]._positionY > WINSIZE_Y)
	{
		_angle += PI;
	}
	_angle = _angle / M_PI * 180.0f;
	for (int i = 0; i < 50; i++)
	{
		_circles[i]._dirX = _speed * cos(_angle / 180.0f * M_PI);
		_circles[i]._dirY = _speed * sin(_angle / 180.0f * M_PI);
		_circles[i]._positionX = _circles[0]._positionX - 50.0f * cos(_angle / 180.0f * M_PI) * (float)i;
		_circles[i]._positionY = _circles[0]._positionY - 50.0f * sin(_angle / 180.0f * M_PI) * (float)i;
		_circles[i]._exit = true;
		_circles[i]._size = 50;
	}
	return S_OK;
}

void EWG_EarthWorm::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_angle -= 3.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_angle += 3.0f;
	}
	if(!_circles[0]._exit)
	{
		if (_circles[0]._positionX < 25)
		{
			_angle = 180.0f - _angle;
			_circles[0]._positionX = 25;
		}
		if (_circles[0]._positionX > WINSIZE_X - 25)
		{
			_angle = 180.0f - _angle;
			_circles[0]._positionX = WINSIZE_X - 25;
		}
		if (_circles[0]._positionY < 25)
		{
			_angle = 360.0f - _angle;
			_circles[0]._positionY = 25;
		}
		if (_circles[0]._positionY > WINSIZE_Y - 25)
		{
			_angle = 360.0f - _angle;
			_circles[0]._positionY = WINSIZE_Y - 25;
		}
	}
	else
	{
		if (_circles[0]._positionX > 25 && _circles[0]._positionX < WINSIZE_X - 25)
		{
			if (_circles[0]._positionY > 25 && _circles[0]._positionY < WINSIZE_Y - 25)
			{
				_circles[0]._exit = false;
			}
		}
	}
	_circles[0]._dirX = _speed * cos(_angle / 180.0f * PI);
	_circles[0]._dirY = _speed * sin(_angle / 180.0f * PI);
	for (int i = 1; i < 50; i++)
	{
		_circles[i]._turn.push_back(make_pair(make_pair(_circles[0]._positionX, _circles[0]._positionY), make_pair(_circles[0]._dirX, _circles[0]._dirY)));
	}
	_circles[0]._positionX += _circles[0]._dirX;
	_circles[0]._positionY += _circles[0]._dirY;
	int dist;
	for (int i = 1; i < 50; i++)
	{
		if(_circles[i]._turn.size() != 0)
		{
			dist = pow(_circles[i]._turn[0].first.first - _circles[i]._positionX, 2) + pow(_circles[i]._turn[0].first.second - _circles[i]._positionY, 2);
			if (dist == 0)
			{
				_circles[i]._dirX = _circles[i]._turn[0].second.first;
				_circles[i]._dirY = _circles[i]._turn[0].second.second;
				_circles[i]._turn.erase(_circles[i]._turn.begin());
			}
		}
		_circles[i]._positionX += _circles[i]._dirX;
		_circles[i]._positionY += _circles[i]._dirY;
		if(!_circles[i]._exit)
		{
			if (_circles[i]._positionX < 25)
			{
				_circles[i]._positionX = 25;
			}
			if (_circles[i]._positionX > WINSIZE_X - 25)
			{
				_circles[i]._positionX = WINSIZE_X - 25;
			}
			if (_circles[i]._positionY < 25)
			{
				_circles[i]._positionY = 25;
			}
			if (_circles[i]._positionY > WINSIZE_Y - 25)
			{
				_circles[i]._positionY = WINSIZE_Y - 25;
			}
		}
		else
		{
			if (_circles[i]._positionX > 25 && _circles[i]._positionX < WINSIZE_X - 25)
			{
				if (_circles[i]._positionY > 25 && _circles[i]._positionY < WINSIZE_Y - 25)
				{
					_circles[i]._exit = false;
				}
			}
		}
	}
}

void EWG_EarthWorm::render(HDC hdc)
{
	char str[10];
	for(int i = 0; i < 50; i++)
	{
		EllipseMakeCenter(hdc, _circles[i]._positionX, _circles[i]._positionY, _circles[i]._size, _circles[i]._size);
		wsprintf(str, "%d", i + 1);
		TextOut(hdc, _circles[i]._positionX, _circles[i]._positionY, str, lstrlen(str));
	}
}

void EWG_EarthWorm::release(void)
{
	
}

void EWG_EarthWorm::eatItem(int index)
{
	_circles[index]._size *= 2;
}
