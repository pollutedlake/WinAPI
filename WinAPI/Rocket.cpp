#include "Stdafx.h"
#include "Rocket.h"

HRESULT Rocket::init(void)
{
	_image = IMAGEMANAGER->addImage("로켓", "Resources/Images/ShootingGame/Rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_flame = new Flame;
	_flame->init("Flame.bmp", &_x, &_y, 180);
	_missileM1 = new MissileM1;
	_missileM1->init(MAX_BULLET, WINSIZE_Y);

	_beam = new Beam;
	_beam->init(1, 0.5);
	_beamIrradiation = false;

	_currentHp = 10;
	_maxHp = 10;

	_hpBar = new ProgressBar;

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y / 2;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	_hpBar->init(_x, _y, 52, 4);
	//spRocket.push_back(std::shared_ptr<Rocket>(new Rocket));

	return S_OK;
}

void Rocket::release(void)
{
	_flame->release();
	SAFE_DELETE(_flame);

	_missileM1->release();
	SAFE_DELETE(_missileM1);

	_beam->release();
	SAFE_DELETE(_beam);

	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void Rocket::update(void)
{
	if(KEYMANAGER->isOnceKeyDown('1')) hitDamage(1.0f);
	if(KEYMANAGER->isOnceKeyDown('1')) hitDamage(1.0f);

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X && _beamIrradiation == false)
	{
		_x += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0 && _beamIrradiation == false)
	{
		_x -= ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_y -= ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZE_Y)
	{
		_y += ROCKET_SPEED;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_setWeapon = MISSILE;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_setWeapon = BEAM;
	}

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	switch (_setWeapon)
	{
		case MISSILE:
			if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
			{
				_missileM1->fire(_x, _y - 60);
			}
		break;
		case BEAM:
			if (KEYMANAGER->isStayKeyDown(VK_SPACE))
			{
				_beam->fire(_x, _y - 430);
				_beamIrradiation = true;
			}
			else
			{
				_beamIrradiation = false;
			}
		break;
	}
	
	_flame->update();
	_beam->update();
	_missileM1->update();

	_hpBar->setX(_x - (_rc.right - _rc.left) / 2);
	_hpBar->setY(_y - 10 - (_rc.bottom - _rc.top) / 2);
	_hpBar->update();
	_hpBar->setGauge(_currentHp, _maxHp);
}

void Rocket::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
	_flame->render();
	_beam->render();
	_missileM1->render();
	_hpBar->render();
}

void Rocket::removeMissile(int arrNum)
{
	_missileM1->removeBullet(arrNum);
}

/*
과제1. 미사일 충돌 처리

- 내가 발사한 미사일로 적을 제거한다.
ㄴ 본인이 생각한 가장 효율적인 (객체지향적인) 방법으로

과제2. 체력 바 구현

- 로켓과 적의 체력바를 구현한다.

ㄴ 1. 체력바를 각각의 객체위에 띄워주는 방법
ㄴ 2. 적 객체 한정으로 체력바를 공유하는 방법
*/