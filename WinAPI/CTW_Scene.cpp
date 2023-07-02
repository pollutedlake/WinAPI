#include "stdafx.h"
#include "CTW_Scene.h"

HRESULT CTW_Scene::init()
{
	_player = new Player;
	_player->init();
	_backGround = new CTW_BackGround;
	_backGround->init();
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
	_backGround->render(getMemDC());
	_player->render(getMemDC());
	_backGround->render(getMemDC(), getHDC());
}

void CTW_Scene::collisionCheck(RECT playerRC, RECT* platforms)
{
	RECT temp;
	bool _isCollision = false;
	for (int i = 0; i < 7; i++)
	{
		if (IntersectRect(&temp, &playerRC, &platforms[i]))
		{
			if (temp.right - temp.left > temp.bottom - temp.top)
			{
				if (playerRC.bottom > temp.top && playerRC.top < temp.top)
				{
					_isCollision = true;
				}
			}
			_player->modifyPosition(temp, platforms[i]);
		}
	}
	if (_isCollision == false)
	{
		_player->setStateFall();
	}
}
