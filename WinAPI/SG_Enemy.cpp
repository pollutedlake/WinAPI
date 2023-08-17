#include "stdafx.h"
#include "SG_Enemy.h"
#include "Bullets.h"

SG_Enemy::SG_Enemy(void) : _rc(RectMake(0, 0, 0, 0)), _currentFrameX(0), _currentFrameY(0), _x(0.0f), _y(0.0f), _worldTimeCount(0.0f), _rndTimeCount(0.0f)
{

}

HRESULT SG_Enemy::init(void)
{
    return S_OK;
}

HRESULT SG_Enemy::init(const char* imageName, POINT position)
{
    _worldTimeCount = GetTickCount();
    _rndTimeCount = RND->getFromFloatTo(50, 150);
    _x = position.x;
    _y = position.y;
    _image = IMAGEMANAGER->findImage(imageName);
    _rc = RectMakeCenter(position.x, position.y,
        _image->getFrameWidth(), _image->getFrameHeight());
    _colliderRC = &_rc;
    _collisionPtr = &EventListener::collision;
    EVENTMANAGER->addEnemy(this);
    return S_OK;
}

HRESULT SG_Enemy::init(const char* imageName, POINT center, int radius, float angle)
{
    // DO NOTHING
    return S_OK;
}

HRESULT SG_Enemy::init(const char* imageName, POINT position, int rndSpeed)
{
	// DO NOTHING
	return S_OK;
}

void SG_Enemy::release(void)
{
}

void SG_Enemy::update(void)
{
    move();
}

void SG_Enemy::render(void)
{
    draw();
    animation();
}

// 구현하지 않는 이유 : 적마다 움직임이 다르다. -> 상속을 전제한 클래스인데.. -> 자식 구현
void SG_Enemy::move(void)
{
}

void SG_Enemy::draw(void)
{
    _image->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void SG_Enemy::animation(void)
{
    if (_rndTimeCount + _worldTimeCount <= GetTickCount())
    {
        _worldTimeCount = GetTickCount();
        _currentFrameX++;

        if (_image->getMaxFrameX() < _currentFrameX)
        {
            _currentFrameX = 0;
        }
    }
}

void SG_Enemy::getDamaged(void)
{
    
}

void SG_Enemy::collision()
{
    cout << "Enemy" << endl;
}
