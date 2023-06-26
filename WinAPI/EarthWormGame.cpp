#include "stdafx.h"
#include "EarthWormGame.h"

/*
���� 1. ������ �����

- �����̴� ������ ������ ���� �̾����� ����
�� �� �������� ��ȣ�� ǥ���Ѵ�.

- �����̴� ȭ����� ������ ��ġ���� ������ �Ѵ�.

- Ư���� Ű �Է��� ��� �����̴� ȭ��ȿ��� �����δ�.

- ���� �ε����� ƨ�� ������ �ϰ� ����/ ������ ����Ű�� ������ �����ؾ� ��

- ������� ������ �Ӹ��� ������ ư�ٰ� ���� Ʋ�� �ȵǰ� �Ӹ��� �ִ� ��ġ���� �ͼ� ������ ��ȯ�Ѵ�.

- ������ ���ڰ� ǥ�õ� �������� ������ ���۵Ǹ� �����̰� �������� ������ �ش��ϴ� ��ȣ�� ������ ������ Ŀ����.

�� �󸶳� �ڿ��������� �ٽ�
*/

HRESULT EarthWormGame::init(void)
{
	GameNode::init();
	_earthWorm = new EWG_EarthWorm;
	_earthWorm->init();
	_itemTime = RND->getFromIntTo(300, 400);
	_itemRegen = false;
	return S_OK;
}

void EarthWormGame::update(void)
{
	GameNode::update();
	_earthWorm->update();
	_itemTime--;
	if (_itemTime == 0)
	{
		_itemRegen = true;
		_item._index = RND->getFromIntTo(1, 50);
		_item._position.x = RND->getFromIntTo(25, WINSIZE_X - 25);
		_item._position.y = RND->getFromIntTo(25, WINSIZE_Y - 25);
	}
	if (_itemRegen)
	{
		POINT headPosition = _earthWorm->getHeadPosition();
		if (pow(headPosition.x - _item._position.x, 2) + pow(headPosition.y - _item._position.y, 2) < 2500)
		{
			_earthWorm->eatItem(_item._index - 1);
			_itemRegen = false;
		}
	}
}

void EarthWormGame::release(void)
{
	GameNode::release();
	SAFE_DELETE(_earthWorm);
}

void EarthWormGame::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

	_earthWorm->render(memDC);
	char str[10];
	if (_itemRegen)
	{
		wsprintf(str, "%d", _item._index);
		EllipseMakeCenter(memDC, _item._position.x, _item._position.y, 50, 50);
		TextOut(memDC, _item._position.x, _item._position.y, str, lstrlen(str));
	}

	this->getDoubleBuffer()->render(hdc, 0, 0);
}
