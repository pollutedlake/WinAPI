#include "stdafx.h"
#include "Penitent.h"

HRESULT Penitent::init()
{
	_idle = IMAGEMANAGER->addFrameImage("Idle", "Resources/Images/CatchTheWall/Idle.bmp", 172, 96, 4, 2, true, RGB(255, 0, 255));
	_move = IMAGEMANAGER->addFrameImage("Move", "Resources/Images/CatchTheWall/Move.bmp", 800, 94, 16, 2, true, RGB(255, 0, 255));
	_jumpForward = IMAGEMANAGER->addFrameImage("JumpForward", "Resources/Images/CatchTheWall/Jump.bmp", 506, 158, 11, 2, true, RGB(255, 0, 255));
	_climb = IMAGEMANAGER->addFrameImage("Climb", "Resources/Images/CatchTheWall/Climb.bmp", 40, 112, 1, 2, true, RGB(255, 0, 255));
	_goUp = IMAGEMANAGER->addFrameImage("GoUp", "Resources/Images/CatchTheWall/GoUp.bmp", 159, 120, 3, 2, true, RGB(255, 0, 255));
	_frame = 0;
	_index = 0;
	_position = { WINSIZE_X / 2, WINSIZE_Y - 50 };
	_state = STATE::IDLE;
	_velocity = { 0, 0 };
	_gravity = 10;
	return S_OK;
}

void Penitent::release(void)
{

}

void Penitent::update(void)
{
	_position.x += _velocity.x;
	_position.y += _velocity.y + _gravity;
	_rc = RectMakeCenter(_position.x, _position.y - 75, 100, 150);
	switch (_state)
	{
	case STATE::IDLE:
		_frame++;
		if (_frame % 7 == 0)
		{
			if (_isLeft == true)
			{
				_idle->setFrameY(1);
				_idle->setFrameX(_idle->getMaxFrameX() - _index % _idle->getMaxFrameX());
			}
			else
			{
				_idle->setFrameY(0);
				_idle->setFrameX(_index % _idle->getMaxFrameX());
			}
			_index++;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_state = STATE::MOVE;
			_frame = 0;
			_index = 0;
			break;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_state = STATE::MOVE;
			_frame = 0;
			_index = 0;
			break;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_state = STATE::JUMPFORWARD;
			_velocity.y = -40;
			_jumpForward->setFrameY(_move->getFrameY());
			_frame = 0;
			_index = 0;
			break;
		}
		break;
	case STATE::MOVE:
		_frame++;
		if (_frame % 3 == 0)
		{
			if (_isLeft == true)
			{
				_move->setFrameY(1);
				if(_index < _move->getMaxFrameX())
				{
					_move->setFrameX(_move->getMaxFrameX() - _index % _move->getMaxFrameX());
				}
				else
				{
					_move->setFrameX(_move->getMaxFrameX() - _index % (_move->getMaxFrameX() - 2) - 2);
				}
			}
			else
			{
				_move->setFrameY(0);
				if(_index < _move->getMaxFrameX())
				{
					_move->setFrameX(_index % _move->getMaxFrameX());
				}
				else
				{
					_move->setFrameX(_index % (_move->getMaxFrameX() - 2) + 2);
				}
			}
			_index++;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_velocity.x = 0;
			_state = STATE::IDLE;
			_index = 0;
			_frame = 0;
			break;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_state = STATE::JUMPFORWARD;
			_velocity.y = -40;
			_jumpForward->setFrameY(_move->getFrameY());
			_frame = 0;
			_index = 0;
			break;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && !KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_velocity.x = 7;
			_isLeft = false;
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && !KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_velocity.x = -7;
			_isLeft = true;
		}
		break;
	case STATE::JUMPFORWARD:
		_frame++;
		if (_frame % 5 == 0)
		{
			_velocity.y += 40 / ((_jumpForward->getMaxFrameX() + 1) / 2);//8;
			if(_isLeft == true)
			{
				_jumpForward->setFrameX(_jumpForward->getMaxFrameX() - _index);
			}
			else
			{
				_jumpForward->setFrameX(_index);
			}
			_index++;
		}
		break;
	case STATE::CLIMB:
		if (_climb->getFrameY())
		{
			_rc.right -= 10;
			_position.x += 10;
		}
		else
		{
			_rc.left += 50;
			_position.x -= 50;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_position.y -= 40;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_position.y += 40;
		}
		if (_rc.top <= _catchPlatform.top)
		{
			_position.y = _catchPlatform.top + 150;
			_state = STATE::CATCHCORNER;
			_velocity.y = -_gravity;
			_velocity.x = 0;
			break;
		}
		if (_rc.top >= _catchPlatform.bottom)
		{
			_state = STATE::FALL;
			_velocity.y = 0;
			_velocity.x = 0;
		}
		break;
	case STATE::CATCHCORNER:
		if (_climb->getFrameY())
		{
			_rc.right -= 10;
			_position.x += 10;
		}
		else
		{
			_rc.left += 10;
			_position.x -= 10;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_state = STATE::GoUp;
			_frame = 0;
			_index = 0;
		}
		break;
	case STATE::FALL:
		_frame++;
		_gravity = 10;
		if (_frame % 5 == 0)
		{
			if (_isLeft == true)
			{
				_jumpForward->setFrameX((_jumpForward->getFrameX() + 1) / 2 - _index);
			}
			else
			{
				_jumpForward->setFrameX((_jumpForward->getFrameX() + 1) / 2 + _index);
			}
			_index++;
		}
		break;
	case STATE::GoUp:
		if (_index > _goUp->getMaxFrameX())
		{
			_state = STATE::IDLE;
			_frame = 0;
			_index = 0;
			if (_isLeft == true)
			{
				_position.x -= 50;
				_position.y -= 150;
			}
			else
			{
				_position.x += 50;
				_position.y -= 150;
			}
		}
		_frame++;
		if (_frame % 5 == 0)
		{
			if (_isLeft == true)
			{
				_goUp->setFrameX(_goUp->getMaxFrameX() - _index);
			}
			else
			{
				_goUp->setFrameX(_index);
			}
			_index++;
		}
		break;
	}
}

void Penitent::render(void)
{
	switch(_state)
	{
	case STATE::IDLE:
		_idle->frameRender(getMemDC(), _position.x - _idle->getFrameWidth() / 2 * 3, _position.y - _idle->getFrameHeight() * 3, _idle->getFrameWidth() * 3, _idle->getFrameHeight() * 3, _idle->getFrameX(), _idle->getFrameY());
		break;
	case STATE::MOVE:
		_move->frameRender(getMemDC(), _position.x - _move->getFrameWidth() / 2 * 3, _position.y - _move->getFrameHeight() * 3, _move->getFrameWidth() * 3, _move->getFrameHeight() * 3, _move->getFrameX(), _move->getFrameY());
		break;
	case STATE::JUMPFORWARD:
		_jumpForward->frameRender(getMemDC(), _position.x - _jumpForward->getFrameWidth() / 2 * 3, _position.y - _jumpForward->getFrameHeight() * 3, _jumpForward->getFrameWidth() * 3, _jumpForward->getFrameHeight() * 3, _jumpForward->getFrameX(), _jumpForward->getFrameY());
		break;
	case STATE::CLIMB:
		_climb->frameRender(getMemDC(), _position.x - _climb->getFrameWidth() / 2 * 3, _position.y - _climb->getFrameHeight() * 3, _climb->getFrameWidth() * 3, _climb->getFrameHeight() * 3, _climb->getFrameX(), _climb->getFrameY());
		break;
	case STATE::CATCHCORNER:
		_climb->frameRender(getMemDC(), _position.x - _climb->getFrameWidth() / 2 * 3, _position.y - _climb->getFrameHeight() * 3, _climb->getFrameWidth() * 3, _climb->getFrameHeight() * 3, _climb->getFrameX(), _climb->getFrameY());
		break;
	case STATE::FALL:
		_jumpForward->frameRender(getMemDC(), _position.x - _jumpForward->getFrameWidth() / 2 * 3, _position.y - _jumpForward->getFrameHeight() * 3, _jumpForward->getFrameWidth() * 3, _jumpForward->getFrameHeight() * 3, _jumpForward->getFrameX(), _jumpForward->getFrameY());
		break;
	case STATE::GoUp:
		_goUp->frameRender(getMemDC(), _position.x - _goUp->getFrameWidth() / 2 * 3, _position.y - _goUp->getFrameHeight() * 3, _goUp->getFrameWidth() * 3, _goUp->getFrameHeight() * 3, _goUp->getFrameX(), _goUp->getFrameY());
		break;
	}
}

void Penitent::modifyPosition(RECT intersectRC, RECT platform)
{
	if (intersectRC.right - intersectRC.left > intersectRC.bottom - intersectRC.top)
	{
		if (_rc.bottom > intersectRC.top && _rc.top < intersectRC.top)
		{
			_position.y -= (intersectRC.bottom - intersectRC.top);
			if ((_state == STATE::JUMPFORWARD && _index > _jumpForward->getMaxFrameX() / 2) || (_state == STATE::CLIMB || _state == STATE::FALL))
			{
				_state = STATE::IDLE;
				_velocity.x = 0;
				_velocity.y = 0;
				_gravity = 10;
			}
		}
		else
		{
			_position.y += intersectRC.bottom - intersectRC.top;
		}
	}
	else
	{
		if (_rc.right > intersectRC.left && _rc.left < intersectRC.left)
		{
			_position.x -= intersectRC.right - intersectRC.left;
			_climb->setFrameY(1);
		}
		else
		{
			_position.x += intersectRC.right - intersectRC.left;
			_climb->setFrameY(0);
		}
		if (_state == STATE::JUMPFORWARD || _state == STATE::FALL)
		{
			_state = STATE::CLIMB;
			_gravity = 1;
			_velocity.x = 0;
			_velocity.y = 0;
			_frame = 0;
			_index = 0;
			_catchPlatform = platform;
		}
	}
}
