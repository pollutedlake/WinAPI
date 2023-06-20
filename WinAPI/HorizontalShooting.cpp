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
	player1 = new Player1;
	player1->init(20, WINSIZE_Y / 2);
	player2 = new Player2;
	player2->init(20, WINSIZE_Y / 2);
	/*playerRC1 = RectMakeCenter(20, WINSIZE_Y / 2, 40, 40);
	playerRC2 = RectMakeCenter(WINSIZE_X - 20, WINSIZE_Y / 2, 40, 40);
	for (int i = 0; i < 3; i++)
	{
		hp1[i] = 100;
		hp2[i] = 100;
	}
	for (int i = 0; i < BULLET_MAX; i++)
	{
		_bullet1[i].fire = false;
		_bullet2[i].fire = false;
	}*/
	return S_OK;
}

void HorizontalShooting::release(void)
{
	GameNode::release();
}

void HorizontalShooting::update(void)
{
	GameNode::update();
	/*if (KEYMANAGER->isStayKeyDown(VK_DOWN) && playerRC1.bottom < WINSIZE_Y)
	{
		playerRC1.top += PLAYER_SPEED;
		playerRC1.bottom += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && playerRC1.top > 10)
	{
		playerRC1.top -= PLAYER_SPEED;
		playerRC1.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && playerRC1.right < WINSIZE_X / 2)
	{
		playerRC1.left += PLAYER_SPEED;
		playerRC1.right += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && playerRC1.left > 0)
	{
		playerRC1.left -= PLAYER_SPEED;
		playerRC1.right -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('S') && playerRC2.bottom < WINSIZE_Y)
	{
		playerRC2.top += PLAYER_SPEED;
		playerRC2.bottom += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('W') && playerRC2.top > 10)
	{
		playerRC2.top -= PLAYER_SPEED;
		playerRC2.bottom -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('D') && playerRC2.right < WINSIZE_X)
	{
		playerRC2.left += PLAYER_SPEED;
		playerRC2.right += PLAYER_SPEED;
	}
	if (KEYMANAGER->isStayKeyDown('A') && playerRC2.left > WINSIZE_X / 2)
	{
		playerRC2.left -= PLAYER_SPEED;
		playerRC2.right -= PLAYER_SPEED;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		fireBullet(2);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		fireBullet(1);
	}
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		useSkill(2, 1);
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		useSkill(2, 2);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD2))
	{
		useSkill(1, 2);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		useSkill(1, 1);
	}
	RECT* temp = new RECT;
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (_bullet1[i].fire)
		{
			_bullet1[i].rc.left += 14;
			_bullet1[i].rc.right += 14;
			if (_bullet1[i].rc.left > WINSIZE_X)
			{
				_bullet1[i].fire = false;
			}
			if (IntersectRect(temp, &playerRC2, &_bullet1[i].rc))
			{
				if (hp2[2] > 0)
				{
					hp2[2] -= 10;
				}
				else if (hp2[1] > 0)
				{
					hp2[1] -= 10;
				}
				else if (hp2[0] > 0)
				{
					hp2[0] -= 10;
				}
				_bullet1[i].fire = false;
			}
		}
		if (_bullet2[i].fire)
		{
			_bullet2[i].rc.left -= 14;
			_bullet2[i].rc.right -= 14;
			if (_bullet2[i].rc.left < 0)
			{
				_bullet2[i].fire = false;
			}
			if (IntersectRect(temp, &playerRC1, &_bullet2[i].rc))
			{
				if (hp1[2] > 0)
				{
					hp1[2] -= 10;
				}
				else if (hp1[1] > 0)
				{
					hp1[1] -= 10;
				}
				else if (hp1[0] > 0)
				{
					hp1[0] -= 10;
				}
				_bullet2[i].fire = false;
			}
		}
	}
	SAFE_DELETE(temp);*/
}

void HorizontalShooting::render(HDC hdc)
{
	GameNode::render(hdc);
	MoveToEx(hdc, WINSIZE_X / 2, 0, NULL);
	LineTo(hdc, WINSIZE_X / 2, WINSIZE_Y);
	DrawRectMake(hdc, playerRC1);
	DrawRectMake(hdc, playerRC2);
	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH orangeBrush = CreateSolidBrush(RGB(255, 127, 39));
	HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, redBrush);
	DrawRectMake(hdc, { 0, 0, WINSIZE_X / 2 * hp1[0] / 100, 10 });
	DrawRectMake(hdc, { WINSIZE_X / 2 + WINSIZE_X / 2 * (100 - hp2[0]) / 100, 0, WINSIZE_X, 10 });
	SelectObject(hdc, orangeBrush);
	DrawRectMake(hdc, { 0, 0, WINSIZE_X / 2 * hp1[1] / 100, 10 });
	DrawRectMake(hdc, { WINSIZE_X / 2 + WINSIZE_X / 2 * (100 - hp2[1]) / 100, 0, WINSIZE_X, 10 });
	SelectObject(hdc, greenBrush);
	DrawRectMake(hdc, { 0, 0, WINSIZE_X  / 2 * hp1[2] / 100, 10 });
	DrawRectMake(hdc, { WINSIZE_X / 2 + WINSIZE_X / 2 * (100 - hp2[2]) / 100, 0, WINSIZE_X, 10 });
	SelectObject(hdc, oldBrush);
	DeleteObject(greenBrush);
	DeleteObject(redBrush);
	DeleteObject(orangeBrush);
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (_bullet1[i].fire)
		{
			EllipseMakeCenter(hdc, _bullet1[i].rc.left + 10, _bullet1[i].rc.top + 10, 20, 20);
		}
		if (_bullet2[i].fire)
		{
			EllipseMakeCenter(hdc, _bullet2[i].rc.left + 10, _bullet2[i].rc.top + 10, 20, 20);
		}
	}
}

void HorizontalShooting::fireBullet(int player)
{
	if (player == 1)
	{
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (_bullet1[i].fire) continue;
			_bullet1[i].fire = true;
			_bullet1[i].rc = RectMakeCenter(playerRC1.right + 10, playerRC1.top + 20, 20, 20);
			break;
		}
	}
	else
	{
		for (int i = 0; i < BULLET_MAX; i++)
		{
			if (_bullet2[i].fire) continue;
			_bullet2[i].fire = true;
			_bullet2[i].rc = RectMakeCenter(playerRC2.left - 10, playerRC2.top + 20, 20, 20);
			break;
		}
	}
}

void HorizontalShooting::useSkill(int player, int skill)
{

}
