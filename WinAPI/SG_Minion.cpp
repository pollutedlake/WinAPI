#include "stdafx.h"
#include "SG_Minion.h"

void SG_Minion::move(void)
{
	_count++;
	if(_count % 5 == 0)
	{
		_angle++;
		_count = 0;
	}
	_rc = RectMakeCenter(_x + _radius * cos((_angle / PI)), _y + _radius * sin(_angle / PI),
		_image->getFrameWidth(), _image->getFrameHeight());
}

SG_Minion::SG_Minion()
{
	// Do Nothing
}

SG_Minion::SG_Minion(float angle, int radius) : _angle(angle), _count(0), _radius(radius)
{
}

SG_Minion::~SG_Minion()
{
	// Do Nothing
}
