#include "stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
    return S_OK;
}

HRESULT Player::init(int _x, int _y)
{
    position.x = _x;
    position.y = _y;
    rc = RectMakeCenter(position.x, position.y, WIDTH, HEIGHT);
    return S_OK;
}

void Player::update()
{

}

void Player::render(HDC hdc)
{
    DrawRectMake(hdc, rc);
}

void Player::release()
{

}
