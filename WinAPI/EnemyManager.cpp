#include "stdafx.h"
#include "EnemyManager.h"
#include "SG_Minion.h"
#include "SG_Minion2.h"
#include "SG_Minion3.h"
#include "Rocket.h"
// cpp�� ������ �ϰ� �Ѿ��. �������Ϸ��� �����ϰ� �ѱ��. �����ʹ� �ʿ���� �ִ��� ������ �Ǵ��ؾ� �� �� cpp�� �־�� �Ѵ�. ������� include�ϸ� ���縦 �Ѵ�.

HRESULT EnemyManager::init(void)
{
 	IMAGEMANAGER->addFrameImage("���ĸ�", "Resources/Images/ShootingGame/Minion.bmp", 0.0f, 0.0f, 1140, 47, 19, 1, true, RGB(255, 0, 255));
 	IMAGEMANAGER->addImage("�� �̻���", "Resources/Images/ShootingGame/Bullet.bmp", 7 * 2, 7 * 2, true, RGB(255, 0, 255));
	setMinion();

	_bullet = new Bullet;
	_bullet->init("�� �̻���", 30, 1000);
	return S_OK;
}

void EnemyManager::release(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->release();
		SAFE_DELETE(*_viMinion);
	}
	_bullet->release();
	SAFE_DELETE(_bullet);

}

void EnemyManager::update(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
	minionBulletFire();
	_bullet->update();
	collision();
}

void EnemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}
	_bullet->render();
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

void EnemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2, 
						  rc.bottom + (rc.top - rc.bottom) / 2 + 30, 
						  getAngle(rc.left + (rc.right - rc.left) / 2, rc.bottom + (rc.top - rc.bottom) / 2, _rocket->getPosition().x, _rocket->getPosition().y),
						  RND->getFromFloatTo(2.0f, 4.0f));
		}
	}
}

void EnemyManager::collision(void)
{
	for (int i = 0; i < _bullet->getBullet().size(); i++)
	{
		RECT rc;

		if (IntersectRect(&rc, &_bullet->getBullet()[i].rc, &_rocket->getRect()))
		{
			_bullet->removeBullet(i);
			_rocket->hitDamage(2.0f);
		}
	}
}

EnemyManager::EnemyManager()
{
}

EnemyManager::~EnemyManager()
{
}
