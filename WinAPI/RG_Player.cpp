#include "stdafx.h"
#include "RG_Player.h"

HRESULT RG_Player::inint(void)
{
    _player = IMAGEMANAGER->addImage("Car", "Resources/Images/RacingGame/Car.bmp", 860, 1361, true, RGB(255, 0, 255));
    _dashBoard = IMAGEMANAGER->addImage("DashBoard", "Resources/Images/RacingGame/DashBoard.bmp", 270, 198, true, RGB(255, 0, 255));
    _lane = 1;
    _speed = 10;
    _rc = RectMake(WINSIZE_X / 2 - _player->getWidth() / 20, WINSIZE_Y / 2 + 100 + _player->getHeight() / 20, _player->getWidth() / 10, _player->getHeight() / 10);
    _shield = false;
    _frame = 0;
    _shieldTime = 50;
    return S_OK;
}

void RG_Player::release(void)
{
}

void RG_Player::update(void)
{
    if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
    {
        if (_lane > 0)
        {
            _rc.left -= IMAGEMANAGER->findImage("RG_BackGround")->getWidth();
            _rc.right -= IMAGEMANAGER->findImage("RG_BackGround")->getWidth();
            _lane--;
        }
    }
    if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
    {
        if (_lane < 2)
        {
            _rc.left += IMAGEMANAGER->findImage("RG_BackGround")->getWidth();
            _rc.right += IMAGEMANAGER->findImage("RG_BackGround")->getWidth();
            _lane++;
        }
    }
    if (KEYMANAGER->isStayKeyDown(VK_UP))
    {
        if (_speed < 180.0f)
        {
            _speed += 1.0f;
        }
    }
    if (KEYMANAGER->isStayKeyDown(VK_DOWN))
    {
        if (_speed > 10.0f)
        {
            _speed -= 1.0f;
        }
    }
    if (KEYMANAGER->isOnceKeyDown('1'))
    {
        _shield = true;
    }
    if (_shield == true)
    {
        _frame++;
        if (_frame > _shieldTime)
        {
            _shield = false;
            _frame = 0;
        }
    }
    if (KEYMANAGER->isOnceKeyDown('2'))
    {

    }
    if (KEYMANAGER->isOnceKeyDown('3'))
    {

    }
    cout << _speed << endl;
}

void RG_Player::render(HDC hdc)
{
    _player->render(hdc, _rc.left, _rc.top, _player->getWidth() / 10, _player->getHeight() / 10,
        0, 0, _player->getWidth(), _player->getHeight());
    _dashBoard->render(hdc, 0, WINSIZE_Y - _dashBoard->getHeight());
    HPEN velocityHand = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    HPEN oldPen = (HPEN)SelectObject(hdc, velocityHand);
    LineMake(hdc, _dashBoard->getWidth() / 2, WINSIZE_Y - _dashBoard->getHeight() / 2 + 30, _dashBoard->getWidth() / 2 + 75 * cos((180.0f + (_speed - 10) * 9.0f / 8.0f) / 180.0f * PI), WINSIZE_Y - _dashBoard->getHeight() / 2 + 30 + 75 * sin((180.0f + (_speed - 10) * 9.0f / 8.0f) / 180.0f * PI));
    SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
    if (_shield == true)
    {
        EllipseMake(hdc, _rc.left, _rc.top, _player->getWidth() / 10, _player->getHeight() / 10);
    }
    SelectObject(hdc, oldPen);
    DeleteObject(velocityHand);
}