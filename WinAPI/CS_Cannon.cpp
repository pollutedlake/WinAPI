#include "stdafx.h"
#include "CS_Cannon.h"

HRESULT CS_Cannon::init(void)
{
    barrel = POINT{ WINSIZE_X / 2, WINSIZE_Y - 150 };
    angle = 270.0f;
    autoMove = false;
    dir = 1.0f;
    return S_OK;
}

void CS_Cannon::release(void)
{
}

void CS_Cannon::update(void)
{
    if (!autoMove == true)
    {
        if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
        {
            if (angle < 340.0f)
            {
                angle += 1.0f;
            }
        }
        if (KEYMANAGER->isStayKeyDown(VK_LEFT))
        {
            if (angle > 200.0f)
            {
                angle -= 1.0f;
            }
        }
    }
    else
    {
        angle += dir;
        if (angle == 340.0f || angle == 200.0f)
        {
            dir *= -1;
        }
    }
    if (KEYMANAGER->isOnceKeyDown('A'))
    {
        autoMove = true;
    }
    barrel.x = WINSIZE_X / 2 + 150 * cos(angle / 180.0f * PI);
    barrel.y = WINSIZE_Y + 150 * sin(angle / 180.0f * PI);
}

void CS_Cannon::render(HDC hdc)
{
    LineMake(hdc, WINSIZE_X / 2, WINSIZE_Y, barrel.x, barrel.y);
    EllipseMakeCenter(hdc, WINSIZE_X / 2, WINSIZE_Y, 200, 200);
}
