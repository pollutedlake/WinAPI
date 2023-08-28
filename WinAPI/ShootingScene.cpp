#include "stdafx.h"
#include "ShootingScene.h"

HRESULT ShootingScene::init(void)
{
	IMAGEMANAGER->addImage("전장", "Resources/Images/Background/BattleField.bmp", WINSIZE_X, WINSIZE_Y);
	_rocket = new Rocket;
	_rocket->init();
	_em = new EnemyManager;
	_em->init();

	_em->setRocketMemoryAddress(_rocket);
	_rocket->setEnemyMemoryAddress(_em);

	_x = _y = 0;

	wsprintf(_text, "ShootingScene");
	return S_OK;
}

void ShootingScene::release(void)
{
	_rocket->release();
	_em->release();
}

void ShootingScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SCENEMANAGER->changeScene("시작");
	}
	_rocket->update();
	_em->update();
	_y -= 2.0;
	collision();
}

void ShootingScene::render(void)
{
	RECT _rc;
	_rc = { 0, 0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->findImage("전장")->loopRender(getMemDC(), &_rc, _x, _y);
	_rocket->render();
	_em->render();

	TextOut(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, _text, strlen(_text));
}
