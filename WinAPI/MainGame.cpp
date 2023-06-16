/*
����1.ī�� ¦ ���߱�

- ������ : 5 x 4

- ī�� ¦�� ���߸� ���� ī��� ��� ���µǾ�� �Ѵ�.

- ġƮ �ʼ�
�� 1. ���� ���� �� ���� �ð� �� �ٽ� ���߱�
�� 2. 1���� �����ϰ� �������� ���� ���µǰ� ������ 1���� ���߸鼭 ����

�� HBRUSH
*/

#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	rc = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 100);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
}

void MainGame::update(void)
{
	GameNode::update();

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		rc.top += 3;
		rc.bottom += 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		rc.top -= 3;
		rc.bottom -= 3;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		rc.left -= 3;
		rc.right -= 3;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		rc.left += 3;
		rc.right += 3;
	}
}

void MainGame::render(HDC hdc)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
}