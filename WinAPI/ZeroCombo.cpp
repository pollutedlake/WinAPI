#include "stdafx.h"
#include "ZeroCombo.h"

/*
���� 1. ���� �޺� �̹��� �ϼ�

- �����̽� �ٸ� ������ 1Ÿ����->������ ���ݱ��� �ڵ����� ���
�� ���� �ݺ�
*/

HRESULT ZeroCombo::init(void)
{
	GameNode::init();
	_zero = new GImage;
	_zero->init("Resources/Images/Object/ZeroCombo.bmp", 4386, 73, 34, 1, true, RGB(255, 0, 255));
	_attack = false;
	_count = 0;
	_index = 0;
	return S_OK;
}

void ZeroCombo::release(void)
{
	GameNode::release();
}

void ZeroCombo::update(void)
{
	GameNode::update();
	if(KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_attack = true;
	}
	if(_attack == true)
	{
		_count++;
		if (_count % 3 == 0)
		{
			_index++;
			_zero->setFrameX(_index % _zero->getMaxFrameX());
		}
	}
}

void ZeroCombo::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// ========================================================
	_zero->frameRender(memDC, WINSIZE_X / 2, WINSIZE_Y / 2);
	// ========================================================
	this->getDoubleBuffer()->render(hdc, 0, 0);
}
