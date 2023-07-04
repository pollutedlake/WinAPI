#include "stdafx.h"
#include "BH_Object.h"

HRESULT BH_Object::init(pair<float, float> blackHolePos)
{
	_posX = RND->getFloat(WINSIZE_X);
	_posY = RND->getFloat(WINSIZE_Y);
	this->setVector(blackHolePos);
	_radius = 10.0f;
	_active = true;
	return S_OK;
}

void BH_Object::release(void)
{

}

void BH_Object::update(pair<float, float> blackHolePos)
{
	if (_posX - _radius / 2 < 0 || _posX + _radius / 2 > WINSIZE_X)
	{
		this->init(blackHolePos);
	}
	float dist = (float)sqrt(pow(blackHolePos.second - _posY, 2) + pow(blackHolePos.first - _posX, 2));
	if(dist < _radius / 2)
	{
		_active = false;
	}
	_posX += _vectorX;
	_posY += _vectorY;
}

void BH_Object::render(HDC hdc)
{
	EllipseMakeCenter(hdc, _posX, _posY, _radius, _radius);
}

void BH_Object::setVector(pair<float, float> blackHolePos)
{
	float dist = (float)sqrt(pow(blackHolePos.second - _posY, 2) + pow(blackHolePos.first - _posX, 2));
	_vectorX = (blackHolePos.first - _posX) / dist * SPEED;
	_vectorY = (blackHolePos.second - _posY) / dist * SPEED;
}
