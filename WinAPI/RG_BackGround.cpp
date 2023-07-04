#include "stdafx.h"
#include "RG_BackGround.h"

HRESULT RG_BackGround::init(void)
{
    _backGround = IMAGEMANAGER->addImage("RG_BackGround", "Resources/Images/RacingGame/BackGround.bmp", WINSIZE_X / 4, WINSIZE_Y);
    _bgSpeedY = 0;
    return S_OK;
}

void RG_BackGround::release(void)
{
}

void RG_BackGround::update(int speed)
{
    _bgSpeedY -= speed;
    _score += speed / 10;
}

void RG_BackGround::render(HDC hdc)
{
    for (int i = 0; i < 3; i++)
    {
        _backGround->loopRender(hdc, &RectMake(WINSIZE_X / 2 - _backGround->getWidth() / 2 + _backGround->getWidth() * (i - 1), 0, _backGround->getWidth(), _backGround->getHeight()), 0, _bgSpeedY);
    }
    char str[128];
    wsprintf(str, "Score : %d", _score);
    TextOut(hdc, 0, 0, str, lstrlen(str));
}
