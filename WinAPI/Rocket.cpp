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

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y / 2;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

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
}

void Rocket::update(void)
{
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
		break;
	}
	
	_flame->update();
	_beam->update();
	_missileM1->update();
}

void Rocket::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
	_flame->render();
	_beam->render();
	_missileM1->render();
}