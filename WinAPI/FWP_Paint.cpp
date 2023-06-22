#include "stdafx.h"
#include "FWP_Paint.h"

HRESULT FWP_Paint::init(void)
{
	_paint = new GImage;
	if (_stage == 1)
	{
		_paint->init("Resources/Images/BackGround/FindWrongPaint1.bmp", WINSIZE_X, WINSIZE_Y - 50, true, RGB(255, 0, 255));
		_wrongPoint.push_back(std::make_pair(POINT{ 1074, 746 }, false));
		_wrongPoint.push_back(std::make_pair(POINT{ 1152, 582 }, false));
		_wrongPoint.push_back(std::make_pair(POINT{ 1224, 283 }, false));
		_wrongPoint.push_back(std::make_pair(POINT{ 1210, 100 }, false));
		_wrongPoint.push_back(std::make_pair(POINT{ 925, 125 }, false));
	}
	else if(_stage == 2)
	{
		_paint->init("Resources/Images/BackGround/FindWrongPaint2.bmp", WINSIZE_X, WINSIZE_Y - 50, true, RGB(255, 0, 255));
		_wrongPoint.push_back(std::make_pair(POINT{ 993, 687 }, false));
		_wrongPoint.push_back(std::make_pair(POINT{ 710, 408 }, false));
		_wrongPoint.push_back(std::make_pair(POINT{ 732, 688 }, false));
		_wrongPoint.push_back(std::make_pair(POINT{ 700, 145 }, false));
		_wrongPoint.push_back(std::make_pair(POINT{ 1145, 270 }, false));
	}
	return S_OK;
}

void FWP_Paint::update(void)
{
	for (auto it = _wrongPoint.begin(); it != _wrongPoint.end(); ++it)
	{
		if (pow(_ptMouse.x - it->first.x, 2) + pow(_ptMouse.y - it->first.y, 2) <= 2500)
		{
			it->second = true;
			correctN++;
			break;
		}
	}
}

void FWP_Paint::release(void)
{
	SAFE_DELETE(_paint);
	_wrongPoint.clear();
}

void FWP_Paint::render(HDC hdc)
{
	_paint->render(hdc, 0, 50);
	for (auto it = _wrongPoint.begin(); it != _wrongPoint.end(); ++it)
	{
		if (it->second == true)
		{
			SelectObject(hdc, (HBRUSH)GetStockObject(NULL_BRUSH));
			HPEN correctPen = CreatePen(PS_SOLID, 7, RGB(255, 0, 0));
			HPEN oldPen = (HPEN)SelectObject(hdc, correctPen);
			EllipseMakeCenter(hdc, it->first.x, it->first.y, 100, 100);
			SelectObject(hdc, oldPen);
			DeleteObject(correctPen);
		}
	}
}

bool FWP_Paint::isCorrect()
{
	for (auto it = _wrongPoint.begin(); it != _wrongPoint.end(); ++it)
	{
		if (pow(_ptMouse.x - it->first.x, 2) + pow(_ptMouse.y - it->first.y, 2) <= 2500)
		{
			it->second = true;
			correctN++;
			return true;
		}
	}
	return false;
}
