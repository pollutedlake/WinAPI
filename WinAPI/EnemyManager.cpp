#include "stdafx.h"
#include "EnemyManager.h"
#include "SG_Minion.h"
#include "SG_Minion2.h"
#include "SG_Minion3.h"
// cpp�� ������ �ϰ� �Ѿ��. �������Ϸ��� �����ϰ� �ѱ��. �����ʹ� �ʿ���� �ִ��� ������ �Ǵ��ؾ� �� �� cpp�� �־�� �Ѵ�. ������� include�ϸ� ���縦 �Ѵ�.

HRESULT EnemyManager::init(void)
{
 	IMAGEMANAGER->addFrameImage("���ĸ�", "Resources/Images/ShootingGame/Minion.bmp", 0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));
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
			jellyFish = new SG_Minion;
			jellyFish->init("���ĸ�", PointMake(250 + j * 200, 100 + i * 100), 50, 0);
			_vMinion.push_back(jellyFish);
		}
	}
	for (int i = 0; i < 20; i++)
	{
		SG_Enemy* jellyFish;
		jellyFish = new SG_Minion;
		jellyFish->init("���ĸ�", PointMake(WINSIZE_X / 2, WINSIZE_Y / 2 - 100), 200, 2 * PI / 20.f * i);
		_vMinion.push_back(jellyFish);
	}
	for (int i = 0; i < 20; i++)
	{
		SG_Enemy* jellyFish;
		jellyFish = new SG_Minion3;
		jellyFish->init("���ĸ�", PointMake(RND->getFromIntTo(50, WINSIZE_X - 50), RND->getFromIntTo(50, WINSIZE_Y - 50)), 5);
		_vMinion.push_back(jellyFish);
	}
}

void EnemyManager::removeMinion(int arrNum)
{
	
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}
