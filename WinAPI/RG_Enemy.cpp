#include "stdafx.h"
#include "RG_Enemy.h"

HRESULT RG_Enemy::init(void)
{
	_enemyImg = IMAGEMANAGER->addImage("Enemy", "Resources/Images/RacingGame/Enemy_Car.bmp", 84, 234, true, RGB(255, 0, 255));
	_spawnTime = RND->getFromIntTo(50, 100);
	_frame = 0;
	return S_OK;
}

void RG_Enemy::release(void)
{
	for (auto it = _enemyVector.begin(); it != _enemyVector.end();)
	{
		SAFE_DELETE(*it);
		it = _enemyVector.erase(it);
	}
	_enemyVector.clear();
}

void RG_Enemy::update(int speed, RECT playerRC)
{
	_frame++;
	if (_frame > _spawnTime)
	{
		_frame = 0;
		_spawnTime = RND->getFromIntTo(50, 100);
		_enemyVector.push_back(new Enemy);
	}
	for (auto it = _enemyVector.begin(); it != _enemyVector.end();)
	{
		if ((*it)->_rc.top > WINSIZE_Y)
		{
			SAFE_DELETE(*it);
			it = _enemyVector.erase(it);
			continue;
		}
		RECT temp;
		if (IntersectRect(&temp, &((*it)->_rc), &playerRC))
		{
			SAFE_DELETE(*it);
			it = _enemyVector.erase(it);
			continue;
		}
		(*it)->_rc.top += speed;
		(*it)->_rc.bottom += speed;
		++it;
	}
}

void RG_Enemy::render(HDC hdc)
{
	for (auto it = _enemyVector.begin(); it != _enemyVector.end(); ++it)
	{
		_enemyImg->render(hdc, (*it)->_rc.left, (*it)->_rc.top);
	}
}
