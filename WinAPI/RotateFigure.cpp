#include "stdafx.h"
#include "RotateFigure.h"

/*
���� ����1.���� ȸ��

- �簢���� ȸ����Ų��.

- hdc�� ���� �׷��´�
�� WinAPI�� Ȱ���� ����
�� Rectangle�Լ��� �̿��ؼ� �׸���.

- ȭ������ �ٲ� ���¸� ��� ��ǥ�� �̵��ϰ� ������ �Ѵ�.
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
