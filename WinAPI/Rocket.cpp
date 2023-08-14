#include "Stdafx.h"
#include "Rocket.h"

HRESULT Rocket::init(void)
{
	_image = IMAGEMANAGER->addImage("로켓", "Resources/Images/ShootingGame/Rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	_flame = new Flame;
	_flame->init("Flame.bmp", &_x, &_y, 180);
	_missile = new Missile;
	_missileM1 = new MissileM1;
	_missile->init(MAX_BULLET, WINSIZE_Y);
	_missileM1->init(MAX_BULLET, WINSIZE_Y);

	_x = WINSIZE_X / 2;
	_y = WINSIZE_Y / 2;

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	//spRocket.push_back(std::shared_ptr<Rocket>(new Rocket));

	return S_OK;
}

void Rocket::release(void)
{
	SAFE_DELETE(_flame);
	SAFE_DELETE(_missile);
	SAFE_DELETE(_missileM1);
}

void Rocket::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZE_X)
	{
		_x += ROCKET_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0)
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

	_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_missile->fire(_x, _y - 60);
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_missileM1->fire(_x, _y - 60);
	}
	
	_flame->update();
	_missile->update();
	_missileM1->update();
}

void Rocket::render(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
	_flame->render();
	_missile->render();
	_missileM1->render();
}