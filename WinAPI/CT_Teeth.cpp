#include "stdafx.h"
#include "CT_Teeth.h"

HRESULT CT_Teeth::init(void)
{
	return S_OK;
}

HRESULT CT_Teeth::init(POINT _center)
{
	isPressDown = false;
	center = _center;
	rc = RectMakeCenter(center.x, center.y, 50, 100);
	return S_OK;
}

void CT_Teeth::update(void)
{
	if(rc.bottom < 550)
	{
		rc.top = 450;
		rc.bottom = 550;
	}
	if (rc.top > 550)
	{
		rc.top = 550;
	}
}

void CT_Teeth::update(POINT _pt)
{
	if (PtInRect(&rc, _pt) && !isPressDown)
	{
		isPressDown = true;
		rc.top += 50;
	}
}

void CT_Teeth::release(void)
{

}

void CT_Teeth::render(HDC hdc)
{
	DrawRectMake(hdc, rc);
}
