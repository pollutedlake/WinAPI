#include "stdafx.h"
#include "HS_Player.h"

HRESULT HS_Player::init(void)
{
    return S_OK;
}

HRESULT HS_Player::init(int _x, int _y)
{
    hp = 300;
    position.x = _x;
    position.y = _y;
    rc = RectMakeCenter(position.x, position.y, PLAYERWIDTH, PLAYERHEIGHT);
    return S_OK;
}

void HS_Player::update()
{

}

void HS_Player::render(HDC hdc)
{
    EllipseMakeCenter(hdc, position.x, position.y, PLAYERWIDTH, PLAYERHEIGHT);
	oldBrush = (HBRUSH)SelectObject(hdc, redBrush);
	if (hp > 200)
	{
        if(position.x < WINSIZE_X / 2)
        {
		    FillRect(hdc, &RectMake(0, 0, WINSIZE_X / 2, 10), orangeBrush);
		    FillRect(hdc, &RectMake(0, 0, WINSIZE_X / 2 * (hp - 200) / 100, 10), greenBrush);
        }
        else
        {
			FillRect(hdc, &RectMake(WINSIZE_X / 2, 0, WINSIZE_X, 10), orangeBrush);
			FillRect(hdc, &RectMake(WINSIZE_X / 2 + WINSIZE_X / 2 * (300 - hp) / 100, 0, WINSIZE_X, 10), greenBrush);
        }
	}
	else if (hp > 100)
	{
        if(position.x < WINSIZE_X / 2)
        {
		    FillRect(hdc, &RectMake(0, 0, WINSIZE_X / 2, 10), redBrush);
		    FillRect(hdc, &RectMake(0, 0, WINSIZE_X / 2 * (hp - 100) / 100, 10), orangeBrush);
        }
        else
        {
			FillRect(hdc, &RectMake(WINSIZE_X / 2, 0, WINSIZE_X, 10), redBrush);
			FillRect(hdc, &RectMake(WINSIZE_X / 2 + WINSIZE_X / 2 * (200 - hp) / 100, 0, WINSIZE_X, 10), orangeBrush);
        }
	}
	else
	{
        if(position.x < WINSIZE_X / 2)
        {
		    FillRect(hdc, &RectMake(0, 0, WINSIZE_X / 2 * hp / 100, 10), redBrush);
        }
        else
        {
            FillRect(hdc, &RectMake(WINSIZE_X / 2 + WINSIZE_X / 2 * (100 - hp) / 100, 0, WINSIZE_X, 10), redBrush);
        }
	}
	SelectObject(hdc, oldBrush);
}

void HS_Player::release()
{
	DeleteObject(greenBrush);
	DeleteObject(redBrush);
	DeleteObject(orangeBrush);
}

bool HS_Player::shoot()
{
    return false;
}

bool HS_Player::getDamaged(POINT _pt, int _r)
{
    int dist = pow(position.x - _pt.x, 2) + pow(position.y - _pt.y, 2);
    if (dist <= pow(_r / 2 + PLAYERHEIGHT / 2, 2))
    {
        hp -= 10;
        if (hp < 0)
        {
            hp = 0;
        }
        return true;
    }
    return false;
}

bool HS_Player::useSkill1()
{
    return false;
}

bool HS_Player::useSkill2()
{
    return false;
}
