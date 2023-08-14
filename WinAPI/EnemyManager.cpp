#include "stdafx.h"
#include "EnemyManager.h"
#include "SG_Minion.h"
#include "SG_Minion2.h"
#include "SG_Minion3.h"
// cpp는 참조를 하고 넘어간다. 디컴파일러로 참조하고 넘긴다. 데이터는 필요없고 있는지 유무만 판단해야 할 때 cpp에 있어야 한다. 헤더에서 include하면 복사를 한다.

HRESULT EnemyManager::init(void)
{
 	IMAGEMANAGER->addFrameImage("해파리", "Resources/Images/ShootingGame/Minion.bmp", 0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));
	setMinion();
	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}
}

void EnemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
}

void EnemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
}

void EnemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			SG_Enemy* jellyFish;
			jellyFish = new SG_Minion(0, 50);
			jellyFish->init("해파리", PointMake(250 + j * 200, 100 + i * 100));
			_vMinion.push_back(jellyFish);
		}
	}
	for (int i = 0; i < 20; i++)
	{
		SG_Enemy* jellyFish;
		jellyFish = new SG_Minion2(18 * i , 200, 2);
		jellyFish->init("해파리", PointMake(WINSIZE_X / 2, WINSIZE_Y / 2 - 100));
		_vMinion.push_back(jellyFish);
	}
	for (int i = 0; i < 20; i++)
	{
		SG_Enemy* jellyFish;
		jellyFish = new SG_Minion3(5);
		jellyFish->init("해파리", PointMake(RND->getFromIntTo(50, WINSIZE_X - 50), RND->getFromIntTo(50, WINSIZE_Y - 50)));
		_vMinion.push_back(jellyFish);
	}
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}
