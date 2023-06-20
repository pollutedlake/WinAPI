/*
과제1.카드 짝 맞추기

- 사이즈 : 5 x 4

- 카드 짝을 맞추면 맞춘 카드는 계속 오픈되어야 한다.

- 치트 필수
ㄴ 1. 전부 오픈 후 일정 시간 후 다시 감추기
ㄴ 2. 1쌍을 제외하고 나머지는 전부 오픈되고 유저가 1쌍을 맞추면서 종료

※ HBRUSH
*/

#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	_rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 200, 40, 40);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		_enemy[i].rc = RectMakeCenter(
			RND->getFromIntTo(20, WINSIZE_X - 20),
			RND->getFromIntTo(80, WINSIZE_Y * 2),
			20, 20);
		_enemy[i].speed = RND->getFromIntTo(2, 8);
		_enemy[i].die = false;
	}

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && WINSIZE_X > _rc.right)
	{
		_rc.left += PLAYER_SPEED;
		_rc.right += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && 0 < _rc.left)
	{
		_rc.left -= PLAYER_SPEED;
		_rc.right -= PLAYER_SPEED;
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP) && 0 < _rc.top)
	{
		_rc.top -= PLAYER_SPEED;
		_rc.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && WINSIZE_Y > _rc.bottom)
	{
		_rc.top += PLAYER_SPEED;
		_rc.bottom += PLAYER_SPEED;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		fireBullet();
	}

	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].fire) continue;
		_bullet[i].rc.top -= 14;
		_bullet[i].rc.bottom -= 14;

		if (_bullet[i].rc.bottom < 0) _bullet[i].fire = false;
	}

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;
		_enemy[i].rc.top += _enemy[i].speed;
		_enemy[i].rc.bottom += _enemy[i].speed;

		if (_enemy[i].rc.top > WINSIZE_Y)
		{
			_enemy[i].rc = RectMakeCenter(
				RND->getFromIntTo(20, WINSIZE_X - 20),
				-(RND->getFromIntTo(80, WINSIZE_Y * 2)),
				20, 20);
		}
	}
}

void MainGame::render(HDC hdc)
{
	DrawRectMake(hdc, _rc);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;
		Rectangle(hdc,
			_enemy[i].rc.left, _enemy[i].rc.top,
			_enemy[i].rc.right, _enemy[i].rc.bottom);
	}
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].fire) continue;
		Ellipse(hdc,
			_bullet[i].rc.left, _bullet[i].rc.top,
			_bullet[i].rc.right, _bullet[i].rc.bottom);
	}
}

void MainGame::fireBullet(void)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (_bullet[i].fire) continue;
		_bullet[i].fire = true;

		_bullet[i].rc = RectMakeCenter(
			_rc.left + (_rc.right - _rc.left) / 2,
			_rc.top + (_rc.bottom - _rc.top) / 2 - 24,
			50, 50
		);
		break;
	}
}