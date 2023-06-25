#include "stdafx.h"
#include "RotateFigure.h"

/*
도전 과제1.도형 회전

- 사각형을 회전시킨다.

- hdc를 통해 그려온다
ㄴ WinAPI를 활용해 구현
ㄴ Rectangle함수를 이용해서 그린다.

- 화면축이 바뀐 상태면 상대 좌표로 이동하게 구현을 한다.
*/

HRESULT RotateFigure::init(void)
{
	GameNode::init();
	//rectCenter = {WINSIZE_X / 2, WINSIZE_Y / 2};
	rectCenter = {0, 0};
	angle = 0.0f;
	return S_OK;
}

void RotateFigure::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		rectCenter.y -= 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		rectCenter.y += 10;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		angle -= 3.0f;
		POINT temp = rectCenter;
		rectCenter.x = cos(3.0f / 180.0f * PI) * temp.x - sin(3.0f / 180.0f * PI) * temp.y;
		rectCenter.y = sin(3.0f / 180.0f * PI) * temp.x + cos(3.0f / 180.0f * PI) * temp.y;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		angle += 3.0f;
		POINT temp = rectCenter;
		rectCenter.x = ceil(cos(-3.0f / 180.0f * PI) * temp.x - sin(-3.0f / 180.0f * PI) * temp.y);
		rectCenter.y = ceil(sin(-3.0f / 180.0f * PI) * temp.x + cos(-3.0f / 180.0f * PI) * temp.y);
	}
	xForm.eM11 = (FLOAT) cos(angle / 180.0f * PI);
	xForm.eM12 = (FLOAT) sin(angle / 180.0f * PI);
	xForm.eM21 = (FLOAT) -sin(angle / 180.0f * PI);
	xForm.eM22 = (FLOAT) cos(angle / 180.0f * PI);
	xForm.eDx = WINSIZE_X / 2;
	xForm.eDy = WINSIZE_Y / 2;
}

void RotateFigure::release(void)
{
	GameNode::release();
}

void RotateFigure::render(HDC hdc)
{	
	char str[128];
	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc, &xForm);
	DrawRectMake(hdc, RectMakeCenter(rectCenter.x, rectCenter.y, 100, 50));
}
