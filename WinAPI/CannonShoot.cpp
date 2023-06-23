#include "stdafx.h"
#include "CannonShoot.h"

/*
과제 2. 포신 각도에 따른 총알 발사

- 예외 처리 : 포신 앵글을 막아준다.->화면 밖으로

- 필수 : 수동 / 자동 버전->총 2가지로

과제 3. 발사된 총알끼리 충돌

- 핵심 요소는 총알끼리 충돌이 되면 자연스럽게 팅겨 나가야 한다.

과제 4. 발사한 총알에 중력 적용

- 총알이 중력을 받아 떨어진다.->힘이 다하면

※ 발사된 총알 예외 처리
ㄴ 4번 과제는 제외
ㄴ 발사된 총알은 화면밖으로 나갈 수 없다.
ㄴ 주의 사항 발사된 총알이 화면 끝점에 닿아 팅겨 나갈 때 각도에 신경쓴다.
*/

HRESULT CannonShoot::init(void)
{
	GameNode::init();
	cannon = new CS_Cannon;
	cannon->init();
	for (int i = 0; i < SHELL_MAX; i++)
	{
		shells[i] = new CS_Shell;
		shells[i]->init();
	}
	return S_OK;
}

void CannonShoot::release(void)
{
	GameNode::release();
	SAFE_DELETE(cannon);
}

void CannonShoot::update(void)
{
	GameNode::update();
	cannon->update();
	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		for (int i = 0; i < SHELL_MAX; i++)
		{
			shells[i]->toggleGravity();
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		fireShell();
	}
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (shells[i]->getActive())
		{
			shells[i]->update();
		}
	}
	for (int i = 0; i < SHELL_MAX - 1; i++)
	{
		if (shells[i]->getActive())
		{
			for (int j = i + 1; j < SHELL_MAX; j++)
			{
				if (shells[j]->getActive() && shells[i]->collisionCheck(shells[j]->getPosition()))
				{
					collision(shells[i], shells[j]);
				}
			}
		}
	}
}

void CannonShoot::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	cannon->render(memDC);
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (shells[i]->getActive())
		{
			shells[i]->render(memDC);
		}
	}

	this->getDoubleBuffer()->render(hdc, 0, 0);

}

void CannonShoot::fireShell(void)
{
	for (int i = 0; i < SHELL_MAX; i++)
	{
		if (!shells[i]->getActive())
		{
			shells[i]->fire(WINSIZE_X / 2 + 175.0f * cos(cannon->getAngle() / 180 * PI),  WINSIZE_Y + 175.0f * sin(cannon->getAngle() / 180.0f * PI), 5.0f * cos(cannon->getAngle() / 180 * PI), 5.0f * sin(cannon->getAngle() / 180 * PI));
			break;
		}
	}
}

void CannonShoot::collision(CS_Shell* shell1, CS_Shell* shell2)
{
	POINT point1 = shell1->getPosition();
	POINT point2 = shell2->getPosition();
	-(float)(point1.x - point2.x) / (float)(point1.y - point2.y)
}
