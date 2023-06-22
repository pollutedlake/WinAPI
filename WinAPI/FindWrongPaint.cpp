/*
과제 1. 틀린 그림 찾기

- 이미지는 포토샵 편집 / 검색으로 처리한다.

- 스테이지는 총 2개의 스테이지
ㄴ 틀린 곳은 다섯 곳 이상

- 게임이 시작되면 타임 게임지가 점점 줄어들며 잘못 클릭하면 게이지가 감소된다.

- 틀린 곳을 맞추면 시간 증가

- 타임 게이지가 모두 소진되면 타임오버 메세지를 화면에 띄우며 게임 종료
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
			if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료확인", MB_OKCANCEL) == IDOK)
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
				if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료확인", MB_OKCANCEL) == IDOK)
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
