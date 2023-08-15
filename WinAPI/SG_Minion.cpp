#include "stdafx.h"
#include "SG_Minion.h"

HRESULT SG_Minion::init(const char* imageName, POINT center, int radius, float angle)
{
	_worldTimeCount = GetTickCount();
	_rndTimeCount = RND->getFromFloatTo(50, 150);
	_angle = angle;
	_radius = radius;
	_x = center.x;
	_y = center.y;
	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(center.x, center.y,
		_image->getFrameWidth(), _image->getFrameHeight());
	return S_OK;
}

void SG_Minion::move(void)
{
	_count++;
	if(_count % 5 == 0)
	{
		_angle++;
		_count = 0;
	}
	_rc = RectMakeCenter(_x + _radius * cos((_angle)), _y + _radius * sin(_angle),
		_image->getFrameWidth(), _image->getFrameHeight());
}

SG_Minion::SG_Minion()
{
	// Do Nothing
}

SG_Minion::~SG_Minion()
{
	// Do Nothing
}
