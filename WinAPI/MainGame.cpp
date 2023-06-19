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
//#include "Example_Mole.h"

HRESULT MainGame::init(void)
{
	GameNode::init();

	_currentRect = CURRENTRECT_NULL;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			_rc[i * 4 + j] = RectMakeCenter(100 + j * 200, 200 + i * 200, 100, 100);
		}
	}

	_index = 0;
	_count = 0;
	_score = 0;
	_time = RND->getFromIntTo(30, 60);

	_bIsSelected = false;
	_bIsOnceCheck = false;

	_mole = new Example_Mole;
	_mole->init();

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	_mole->release();
	SAFE_DELETE(_mole);
}

void MainGame::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		// PtInRect() : Rect �ȿ� POINT(x, y�� �ִ��� �˻��Ͽ� ����Ʈ�� �簢�� �ȿ� ������ true�� ��ȯ�ϴ� API �Լ�
		// �簢���̶� ���콺�� �浹 �ƴ���?
		if (PtInRect(&_rc[_index], _ptMouse) && !_bIsOnceCheck)
		{
			_score += 100;
			_bIsOnceCheck = true;
		}
	}

	if (!_bIsSelected)
	{
		_count++;
		if (_count % _time == 0)
		{
			_count = 0;
			_index = RND->getInt(8);
			_currentRect = (CURRENT_RECT)_index;
			_bIsSelected = true;
		}
	}
	else
	{
		_count++;

		if (_count % _time == 0)
		{
			_bIsOnceCheck = false;
			_bIsSelected = false;
			_currentRect = CURRENTRECT_NULL;
			_time = RND->getFromIntTo(30, 60);
			_index = 100;
		}
	}

	_mole->update();
}

void MainGame::render(HDC hdc)
{
	for (int i = 0; i < 8; i++)
	{
		Rectangle(hdc, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}
	char strScore[128];

	wsprintf(strScore, "Score : %d", _score);
	TextOut(hdc, 50, 100, strScore, strlen(strScore));

	if (_bIsSelected)
	{
		int r = RND->getInt(256);
		int g = RND->getInt(256);
		int b = RND->getInt(256);
		HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
		FillRect(hdc, &_rc[_index], brush);
		DeleteObject(brush);
	}

	_mole->render(hdc);
}