/*
���� 1. Ʋ�� �׸� ã��

- �̹����� ���伥 ���� / �˻����� ó���Ѵ�.

- ���������� �� 2���� ��������
�� Ʋ�� ���� �ټ� �� �̻�

- ������ ���۵Ǹ� Ÿ�� �������� ���� �پ��� �߸� Ŭ���ϸ� �������� ���ҵȴ�.

- Ʋ�� ���� ���߸� �ð� ����

- Ÿ�� �������� ��� �����Ǹ� Ÿ�ӿ��� �޼����� ȭ�鿡 ���� ���� ����
*/

#include "stdafx.h"
#include "FindWrongPaint.h"

HRESULT FindWrongPaint::init(void)
{
	GameNode::init();
	_stagePaint[0] = new FWP_Paint(1);
	_stagePaint[0]->init();
	_stagePaint[1] = new FWP_Paint(2);
	_stagePaint[1]->init();
	_time = 300000;
	return S_OK;
}

void FindWrongPaint::release(void)
{
	GameNode::release();
	SAFE_DELETE(_stagePaint[0]);
	SAFE_DELETE(_stagePaint[1]);
}

void FindWrongPaint::update(void)
{
	GameNode::update();
	if(!gameEnd)
	{
		_time -= 10;
		if (_time < 0)
		{	
			_time = 0;
			gameEnd = true;
			if (MessageBox(_hWnd, "������ �����Ͻðڽ��ϱ�?", "����Ȯ��", MB_OKCANCEL) == IDOK)
			{
				PostQuitMessage(0);
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (!_stagePaint[_stage]->isCorrect())
			{
				_time -= 5000;
			}
		}
		if (_stagePaint[_stage]->isFinish())
		{
			if (_stage == 1)
			{
				gameEnd = true;
				if (MessageBox(_hWnd, "������ �����Ͻðڽ��ϱ�?", "����Ȯ��", MB_OKCANCEL) == IDOK)
				{
					PostQuitMessage(0);
				}
			}
			else
			{
				_stage++;
			}
		}
	}
}

void FindWrongPaint::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	_stagePaint[_stage]->render(memDC);
	SelectObject(memDC, GetStockObject(GRAY_BRUSH));
	Rectangle(memDC, 0, 0, WINSIZE_X * _time / 300000, 50);
	this->getDoubleBuffer()->render(hdc, 0, 0);
}
