#include "stdafx.h"
#include "RacingGame.h"

HRESULT RacingGame::init(void)
{
	_player = new RG_Player;
	_player->inint();
	_backGround = new RG_BackGround;
	_backGround->init();
	_enemy = new RG_Enemy;
	_enemy->init();
	return S_OK;
}

void RacingGame::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	_backGround->release();
	SAFE_DELETE(_backGround);
	_enemy->release();
	SAFE_DELETE(_enemy);
}

void RacingGame::update(void)
{
	_player->update();
	_backGround->update(_player->getSpeed());
	_enemy->update(_player->getSpeed(), _player->getRect());
}

void RacingGame::render(void)
{
	_backGround->render(getMemDC());
	_player->render(getMemDC());
	_enemy->render(getMemDC());
}