#include "stdafx.h"
#include "SB_Bullet.h"

HRESULT SB_Bullet::init(void)
{
    velocity = 5;
    position.y = WINSIZE_Y - 160;
    dir = { 0, -1 };
    isActive = true;
    return S_OK;
}

HRESULT SB_Bullet::init(int playerPosX)
{
    this->init();
    position.x = playerPosX;
    return S_OK;
}

void SB_Bullet::update(void)
{
    position.y += dir.y * velocity;
    if (position.y < -10)
    {
        isActive = false;
    }
}

void SB_Bullet::release(void)
{

}

void SB_Bullet::render(HDC hdc)
{
    EllipseMakeCenter(hdc, position.x, position.y, 20, 20);
}
