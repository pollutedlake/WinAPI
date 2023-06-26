#include "stdafx.h"
#include "EarthWormGame.h"

/*
과제 1. 지렁이 만들기

- 지렁이는 구슬이 꼬리를 물고 이어지는 형태
ㄴ 각 구슬마다 번호를 표기한다.

- 지렁이는 화면밖의 무작위 위치에서 등장을 한다.

- 특별한 키 입력이 없어도 지렁이는 화면안에서 움직인다.

- 벽에 부딪히면 튕겨 나가야 하고 왼쪽/ 오른쪽 방향키로 조종이 가능해야 함

- 따라오는 구슬은 머리가 방향을 튼다고 같이 틀면 안되고 머리가 있던 위치까지 와서 방향을 전환한다.

- 임의의 숫자가 표시된 아이템이 게임이 시작되면 지렁이가 아이템을 먹으면 해당하는 번호의 지렁이 구슬이 커진다.

※ 얼마나 자연스러운지 핵심
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
