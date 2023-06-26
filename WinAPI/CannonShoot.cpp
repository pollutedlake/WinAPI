#include "stdafx.h"
#include "CannonShoot.h"

/*
���� 2. ���� ������ ���� �Ѿ� �߻�

- ���� ó�� : ���� �ޱ��� �����ش�.->ȭ�� ������

- �ʼ� : ���� / �ڵ� ����->�� 2������

���� 3. �߻�� �Ѿ˳��� �浹

- �ٽ� ��Ҵ� �Ѿ˳��� �浹�� �Ǹ� �ڿ������� �ð� ������ �Ѵ�.

���� 4. �߻��� �Ѿ˿� �߷� ����

- �Ѿ��� �߷��� �޾� ��������.->���� ���ϸ�

�� �߻�� �Ѿ� ���� ó��
�� 4�� ������ ����
�� �߻�� �Ѿ��� ȭ������� ���� �� ����.
�� ���� ���� �߻�� �Ѿ��� ȭ�� ������ ��� �ð� ���� �� ������ �Ű澴��.
*/

HRESULT CannonShoot::init(void)
{
	GameNode::init();
	cannon = new CS_Cannon;
	cannon->init();
	gravity = false;
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
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		gravity = !gravity;
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
	if(gravity == false)
	{
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
			shells[i]->fire(WINSIZE_X / 2 + 175.0f * cos(cannon->getAngle() / 180 * PI),  WINSIZE_Y + 175.0f * sin(cannon->getAngle() / 180.0f * PI), cannon->getAngle());
			break;
		}
	}
}

void CannonShoot::collision(CS_Shell* shell1, CS_Shell* shell2)
{
	POINT point1 = shell1->getPosition();
	POINT point2 = shell2->getPosition();
	float pushDist = (50.0f - sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2))) / 2.0f;
	shell1->move(pushDist * cos(shell1->getAngle() + PI), pushDist * sin(shell1->getAngle() + PI));
	shell2->move(pushDist * cos(shell2->getAngle() + PI), pushDist * sin(shell2->getAngle() + PI));
	point1 = shell1->getPosition();
	point2 = shell2->getPosition();
	float angle = atan(-(float)(point1.x - point2.x) / (float)(point1.y - point2.y));
	if(angle < 0)
	{
		angle = PI + angle;
	}
	shell1->setAngle(2 * angle - shell1->getAngle());
	shell2->setAngle(2 * angle - shell2->getAngle());
}