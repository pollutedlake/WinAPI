#include "Stdafx.h"
#include "MainGame.h"
#define _USE_MATH_DEFINES
#include<math.h>

HRESULT MainGame::init(void)
{
	GameNode::init();

	_bgImage = new GImage;
	_bgImage->init("Resources/Images/BackGround/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);

	_plImage = new GImage;
	_plImage->init("Resources/Images/Object/Airplane.bmp", 173, 291 , true, RGB(255, 0, 255));

	_nine = new GImage;
	_nine->init("Resources/Images.Object/Nine.bmp", WINSIZE_X / 2 - 200, WINSIZE_Y / 2 - 200, 3315, 2398, 13, 11, true, RGB(255, 0, 255));

	_alphaA = 0;
	_count = _index = 0;

	_isLeft = false;
	_isAlphaIncrease = false;

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_plImage);
	SAFE_DELETE(_nine);
}

void MainGame::update(void)
{
	GameNode::update();
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		_nine->setX(_nine->getX() + 8.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		_nine->setX(_nine->getX() - 8.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		
	}
	if (_isLeft)
	{
		_count++;

		_nine->setFrameY(1);

		if (_count % 3 == 0)
		{
			_index--;

			if (_index < 0)
			{
				_index = 10;
			}

			_nine->setFrameX(_index);
		}
	}
	else
	{
		_count++;
		_nine->setFrameY(0);

		if (_count % 2 == 0)
		{
			_index++;

			if (_index > 10)
			{
				_index = 0;
			}
			_nine->setFrameX(_index);
		}
	}

}

void MainGame::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	// PatBlt(): 사각형 안에 영역을 브러쉬로 채우는 함수
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// ========================================================
	//_bgImage->render(memDC, 0, 0);
	_bgImage->alphaRender(memDC, _alphaA);
	_plImage->alphaRender(memDC, _rc.left, _rc.top, _alphaB);
	//_bgImage->render(memDC, _rc.left, _rc.top, 500, 300, 300, 300);
	// ========================================================
	this->getDoubleBuffer()->render(hdc, 0, 0);
}

void MainGame::fireBullet(void)
{
	
}

/*
과제 1. 제로 콤보 이미지 완성

- 스페이스 바를 누르면 1타부터 -> 마지막 공격까지 자동으로 재생
ㄴ 무한 반복
과제 2. 프레임 이미지 처리
- 시작 씬 + 게임 씬

- 게임씬에서는 아래의 이미지를 GUI화 시켜서 재생 시킨다. (버튼)
ㄴ프레임 렌더

- 필수 이미지:

ㄴ 배경, 대기, 이동(좌 + 우), 찌르기(좌 + 우), 대각선 찌르기, 연속 찌르기(좌, 우), 원 돌리기, 승리 포즈(옷 던지기), 스킬 클라이막스 연출, 패배
*/