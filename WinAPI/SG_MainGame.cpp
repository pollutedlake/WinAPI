#include "stdafx.h"
#include "SG_MainGame.h"
#include "Collision.h"

HRESULT SG_MainGame::init(void)
{
	IMAGEMANAGER->addImage("½´ÆÃ ¸Ê", "Resources/Images/ShootingGame/ShootingBG.bmp", WINSIZE_X, WINSIZE_Y);
	_rocket = new Rocket;
	_em = new EnemyManager;
	_em->init();
	_rocket->init();
    return S_OK;
}

void SG_MainGame::release(void)
{
	_rocket->release();
	_em->release();
}

void SG_MainGame::update(void)
{
	_rocket->update();
	_em->update();
	//EVENTMANAGER->update();
	collision();
	//EVENTMANAGER->update();
}

void SG_MainGame::render(void)
{
	IMAGEMANAGER->findImage("½´ÆÃ ¸Ê")->render(getMemDC());
	_rocket->render();
	_em->render();
}
