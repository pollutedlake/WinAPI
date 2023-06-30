#include "stdafx.h"
#include "Penitent.h"

HRESULT Penitent::init(bool managerInit)
{
	if(managerInit)
	{
		_idle = IMAGEMANAGER->addFrameImage("Idle", "Resources/Images/CatchTheWall/Idle.bmp", 172, 96, 4, 2, true, RGB(255, 0, 255));
		_move = IMAGEMANAGER->addFrameImage("Move", "Resources/Images/CatchTheWall/Move.bmp", 800, 94, 16, 2, true, RGB(255, 0, 255));
		_jumpForward = IMAGEMANAGER->addFrameImage("JumpForward", "Resources/Images/CatchTheWall/Jump.bmp", 506, 158, 11, 2, true, RGB(255, 0, 255));
		_frame = 0;
		_index = 0;
		_position = {WINSIZE_X / 2, WINSIZE_Y};
		_state = STATE::IDLE;
		_velocity = {0, 0};
	}
	return S_OK;
}

void Penitent::release(void)
{
	SAFE_DELETE(_move);
	SAFE_DELETE(_jumpForward);
}

void Penitent::update(void)
{
	_position.x += _velocity.x;
	_position.y += _velocity.y + 10;
	_rc = RectMakeCenter(_position.x, _position.y - 120, 100, 240);
	switch (_state)
	{
	case STATE::IDLE:
		_frame++;
		if (_frame % 3 == 0)
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
			_velocity.y = -(_jumpForward->getMaxFrameX() + 1) * 8 / 2;
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
			_velocity.y = -(_jumpForward->getMaxFrameX() + 1) * 8 / 2;
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
			_velocity.y += 8;
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
	}
}

void Penitent::modifyPosition(RECT intersectRC)
{
	if (intersectRC.right - intersectRC.left > intersectRC.bottom - intersectRC.top)
	{
		if (_position.y > intersectRC.top)
		{
			_position.y -= intersectRC.bottom - intersectRC.top;
			if (_state == STATE::JUMPFORWARD && _index > _jumpForward->getMaxFrameX() / 2)
			{
				_state = STATE::IDLE;
				_velocity.x = 0;
				_velocity.y = 0;
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
		}
		else
		{
			_position.x += intersectRC.right - intersectRC.left;
		}
	}
}
