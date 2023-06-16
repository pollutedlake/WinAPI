#include "stdafx.h"
#include "Clay.h"

Clay::Clay(int _type, POINT _position, POINT _dir, BOOL _isHit)
{
	type = _type;
	position = _position;
	dir = _dir;
	isHit = _isHit;
}

Clay::~Clay()
{

}

void Clay::move()
{
	if (isHit)
	{
		position.y += 20;
	}
	else
	{
		position.x += dir.x;
		position.y += dir.y;
	}
}