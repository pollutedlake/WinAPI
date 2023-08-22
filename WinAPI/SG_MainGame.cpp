#include "stdafx.h"
#include "SG_MainGame.h"
#include "Collision.h"

HRESULT SG_MainGame::init(void)
{
	IMAGEMANAGER->addImage("전장", "Resources/Images/Background/BattleField.bmp", WINSIZE_X, WINSIZE_Y);
	_rocket = new Rocket;
	_em = new EnemyManager;
	_em->init();
	_rocket->init();
	_as = new AniScene;
	_as->init();
	_x = _y = 0;
    return S_OK;
}

void SG_MainGame::release(void)
{
	_rocket->release();
	_em->release();
	_as->release();
	SAFE_DELETE(_as);
}

void SG_MainGame::update(void)
{
	_rocket->update();
	_em->update();
	//EVENTMANAGER->update();
	collision();
	_as->update();
	_y -=2.0;
	//EVENTMANAGER->update();
}

void SG_MainGame::render(void)
{
	RECT _rc;
	_rc = {0, 0, WINSIZE_X, WINSIZE_Y};
	IMAGEMANAGER->findImage("전장")->loopRender(getMemDC(), &_rc, _x, _y);
	_rocket->render();
	_em->render();
	_as->render();
}
