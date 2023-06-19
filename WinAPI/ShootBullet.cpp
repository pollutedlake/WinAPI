#include "stdafx.h"
#include "ShootBullet.h"

HRESULT ShootBullet::init(void)
{
	GameNode::init();
	player = new SB_Player();
	player->init();
	bullets.clear();
	return S_OK;
}

void ShootBullet::update(void)
{
	GameNode::update();
	player->update();
	for (auto it = bullets.begin(); it != bullets.end();)
	{
		if (!(*it)->getIsActive())
		{
			(*it)->release();
			SAFE_DELETE((*it));
			it = bullets.erase(it);
			continue;
		}
		(*it)->update();
		++it;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SB_Bullet* bullet = new SB_Bullet();
		bullet->init(player->getPosition().x);
		bullets.push_back(bullet);
	}
}

void ShootBullet::release(void)
{
	GameNode::release();
	player->release();
	SAFE_DELETE(player);
	for (auto it = bullets.begin(); it != bullets.end();)
	{
		(*it)->release();
		SAFE_DELETE((*it));
		it = bullets.erase(it);
	}
	bullets.clear();
}

void ShootBullet::render(HDC hdc)
{
	player->render(hdc);
	for (auto it = bullets.begin(); it != bullets.end(); ++it)
	{
		(*it)->render(hdc);
	}
}
