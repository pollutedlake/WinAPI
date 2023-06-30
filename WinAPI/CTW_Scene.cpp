#include "stdafx.h"
#include "CTW_Scene.h"

HRESULT CTW_Scene::init(bool managerInit)
{
	_player = new Penitent;
	_player->init(true);
	_backGround = new CTW_BackGround;
	_backGround->init(true);
	return S_OK;
}

void CTW_Scene::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
	_backGround->release();
	SAFE_DELETE(_backGround);
}

void CTW_Scene::update(void)
{
	_player->update();
	collisionCheck(_player->getRect(), _backGround->getRect());
}

void CTW_Scene::render(void)
{
	_backGround->render();
	_player->render();
}

void CTW_Scene::collisionCheck(RECT playerRC, RECT* platforms)
{
	RECT temp;
	for (int i = 0; i < 7; i++)
	{
		if (IntersectRect(&temp, &playerRC, &platforms[i]))
		{
			_player->modifyPosition(temp);
		}
	}
}
