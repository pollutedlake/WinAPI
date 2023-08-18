#include "stdafx.h"
#include "SG_Minion3.h"

HRESULT SG_Minion3::init(const char* imageName, POINT position, int rndSpeed)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);
	_x = position.x;
	_y = position.y;
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(_x, _y,
		_image->getFrameWidth(), _image->getFrameHeight());
	_rndSpeed = rndSpeed;
	//_colliderRC =&_rc;
	//EVENTMANAGER->addEnemy(this);
	return S_OK;
}

void SG_Minion3::move(void)
{
	_count++;
	if (_count % 5 == 0)
	{
		int rndMove = RND->getInt(4);
		switch (rndMove)
		{
			case 0:
				_x += _rndSpeed;
			break;
			case 1:
				_x -= _rndSpeed;
			break;
			case 2:
				_y += _rndSpeed;
			break;
			case 3:
				_y -= _rndSpeed;
			break;
		}
	}
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
}

SG_Minion3::SG_Minion3()
{

}

SG_Minion3::~SG_Minion3()
{
}
