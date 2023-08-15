#include "stdafx.h"
#include "SG_Minion2.h"

void SG_Minion2::move(void)
{
	_count++;
	if (_count % 5 == 0)
	{
		_angle++;
		_count = 0;
	}
	/*if (_gather)
	{
		_radius -= _radiusSpeed;
	}
	else
	{
		_radius += _radiusSpeed;
	}
	if (_radius <= 0)
	{
		_gather = false;
		_radius = 0;
	}
	else if (_radius >= _maxRadius)
	{
		_gather = true;
		_radius = _maxRadius;
	}*/
	_rc = RectMakeCenter(_x + _radius * cos(_angle / PI), _y + _radius * sin(_angle / PI),
		_image->getFrameWidth(), _image->getFrameHeight());
}

SG_Minion2::SG_Minion2()
{

}

SG_Minion2::~SG_Minion2()
{
}
