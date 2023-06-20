#include "stdafx.h"
#include "VerticalShooting.h"

/*
과제 1. 종스크롤 슈팅 게임

- 플레이어 체력바 설정
ㄴ 적과 충돌하면 체력이 감소되고 체력바는 3단계로 처리
ㄴ 빨 / 주 / 초

- 플레이어가 발사한 총알로 적을 제거
*/

HRESULT VerticalShooting::init(void)
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

	hpRc = { _rc.left, _rc.top - 10, _rc.right, _rc.top - 5 };
	for (int i = 0; i < 3; i++)
	{
		hp[i] = 100;
	}
	return S_OK;
}

void VerticalShooting::release(void)
{
}

void VerticalShooting::update(void)
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
	RECT* temp = new RECT;
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!_bullet[i].fire) continue;
		_bullet[i].rc.top -= 14;
		_bullet[i].rc.bottom -= 14;

		if (_bullet[i].rc.bottom < 0) _bullet[i].fire = false;
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			if (IntersectRect(temp, &_bullet[i].rc, &_enemy[j].rc))
			{
				_enemy[j].rc = RectMakeCenter(
					RND->getFromIntTo(20, WINSIZE_X - 20),
					-(RND->getFromIntTo(80, WINSIZE_Y * 2)),
					20, 20);
			}
		}
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
		if (IntersectRect(temp, &_enemy[i].rc, &_rc))
		{
			if (hp[2] > 0)
			{
				hp[2] -= 10;
			}
			else if (hp[1] > 0)
			{
				hp[1] -= 10;
			}
			else if (hp[0] > 0)
			{
				hp[0] -= 10;
			}
			_enemy[i].rc = RectMakeCenter(
				RND->getFromIntTo(20, WINSIZE_X - 20),
				-(RND->getFromIntTo(80, WINSIZE_Y * 2)),
				20, 20);
		}
	}
	hpRc = { _rc.left, _rc.top - 10, _rc.right, _rc.top - 5 };
	SAFE_DELETE(temp);
}

void VerticalShooting::render(HDC hdc)
{
	DrawRectMake(hdc, _rc);
	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH orangeBrush = CreateSolidBrush(RGB(255, 127, 39));
	HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, redBrush);
	DrawRectMake(hdc, {hpRc.left, hpRc.top, hpRc.left + 40 * hp[0] / 100, hpRc.bottom});
	SelectObject(hdc, orangeBrush);
	DrawRectMake(hdc, { hpRc.left, hpRc.top, hpRc.left + 40 * hp[1] / 100, hpRc.bottom });
	SelectObject(hdc, greenBrush);
	DrawRectMake(hdc, { hpRc.left, hpRc.top, hpRc.left + 40 * hp[2] / 100, hpRc.bottom });
	SelectObject(hdc, oldBrush);
	DeleteObject(greenBrush);
	DeleteObject(redBrush);
	DeleteObject(orangeBrush);

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

void VerticalShooting::fireBullet(void)
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
