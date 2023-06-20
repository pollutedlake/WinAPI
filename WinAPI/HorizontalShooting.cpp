#include "stdafx.h"
#include "HorizontalShooting.h"

/*
과제 2. 1 vs 1 횡스크롤 슈팅 게임

- 왼쪽에 1p / 오른쪽에 2p

- 체력바는 대전 게임처럼 중앙을 기준으로 좌우 배치
ㄴ 체력 바 상태에 따라 녹 / 노 / 빨 처리한다.

- 공격 당하면 당한쪽은 당연히 체력이 감소해야 한다.

※ 필수 :
스킬 2개 + 2개 = 4개
아이템을 2종 구현해 온다.
*/

HRESULT HorizontalShooting::init(void)
{
	GameNode::init();
	player1 = new HS_Player1;
	player1->init(20, WINSIZE_Y / 2);
	player2 = new HS_Player2;
	player2->init(WINSIZE_X - 20, WINSIZE_Y / 2);
	for (int i = 0; i < BULLET_MAX; i++)
	{
		bullets[i].setActive(false);
	}
	return S_OK;
}

void HorizontalShooting::release(void)
{
	GameNode::release();
	SAFE_DELETE(player1);
	SAFE_DELETE(player2);
}

void HorizontalShooting::update(void)
{
	GameNode::update();
	player1->update();
	player2->update();
	if (player1->shoot())
	{
		fireBullet(PLAYER1, NORMAL, NULL);
	}
	if (player2->shoot())
	{
		fireBullet(PLAYER2, NORMAL, NULL);
	}
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullets[i].getActive())
		{
			collisionCheck(&bullets[i]);
			if (bullets[i].getType() == CHARGESHOT)
			{
				bullets[i].setPosition(player1->getPosition().x + PLAYERWIDTH / 2 + bullets[i].getWidth() / 2, player1->getPosition().y);
			}
			else if (bullets[i].getType() == SPRINKLER)
			{
				fireBullet(PLAYER2, SPRINKLERCHILD, &bullets[i]);
			}
			bullets[i].update();
		}
	}
	if (player1->useSkill1())
	{
		useSkill(PLAYER1, 1);
	}
	if (player1->useSkill2())
	{
		useSkill(PLAYER1, 2);
	}
	if (player2->useSkill1())
	{
		useSkill(PLAYER2, 1);
	}
	if (player2->useSkill2())
	{
		useSkill(PLAYER2, 2);
	}
}

void HorizontalShooting::render(HDC hdc)
{
	GameNode::render(hdc);
	player1->render(hdc);
	player2->render(hdc);
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (bullets[i].getActive())
		{
			bullets[i].render(hdc);
		}
	}
	MoveToEx(hdc, WINSIZE_X / 2, 0, NULL);
	LineTo(hdc, WINSIZE_X / 2, WINSIZE_Y);
}

void HorizontalShooting::fireBullet(int player, BulletType type, HS_Bullet* sprinkler)
{
	if (player == PLAYER1)
	{
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (bullets[i].getActive())
			{
				continue;
			}
			bullets[i].setActive(true);
			bullets[i].init(player1->getPosition().x + PLAYERWIDTH / 2 + BULLETWIDTH / 2, player1->getPosition().y, PLAYER1, type, 0);
			break;
		}
	}
	else
	{
		int count = 1;
		if (player2->getSkill1())
		{
			count = 3;
		}
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (bullets[i].getActive())
			{
				continue;
			}
			bullets[i].setActive(true);
			if(player2->getSkill1())
			{
				bullets[i].init(player2->getPosition().x - PLAYERWIDTH / 2 - BULLETWIDTH / 2,
				player2->getPosition().y + (count - 2) * PLAYERHEIGHT * 3 / 4, PLAYER2, type, type == SPRINKLERCHILD ? sprinkler->getCount() : 0);
			}
			else
			{
				bullets[i].init(player2->getPosition().x - PLAYERWIDTH / 2 - BULLETWIDTH / 2,
					player2->getPosition().y, PLAYER2, type, type == SPRINKLERCHILD ? sprinkler->getCount() : 0);
			}
			if (type == SPRINKLERCHILD)
			{
				bullets[i].setPosition(sprinkler->getPosition().x, sprinkler->getPosition().y);
			}
			count--;
			if(count == 0)
			{
				break;
			}
		}
	}
}

void HorizontalShooting::collisionCheck(HS_Bullet* bullet)
{
	if (bullet->getWhoShoot() == 1)
	{
		if (bullet->getType() == CHARGESHOT)
		{
			player2->getDamaged({player2->getPosition().x, player1->getPosition().y}, bullet->getHeight());
			return;
		}
		if (player2->getDamaged(bullet->getPosition(), bullet->getWidth()))
		{
			bullet->setActive(false);
		}
	}
	else
	{
		if (player1->getDamaged(bullet->getPosition(), bullet->getWidth()))
		{
			bullet->setActive(false);
		}
	}
}

void HorizontalShooting::useSkill(int player, int skillN)
{
	if (player == PLAYER1)
	{
		if (skillN == 1)
		{
			fireBullet(player, SHOCKWAVE, NULL);
		}
		else
		{
			fireBullet(player, CHARGESHOT, NULL);
		}
	}
	else
	{
		if (skillN == 2)
		{
			fireBullet(player, SPRINKLER, NULL);
		}
	}
}
