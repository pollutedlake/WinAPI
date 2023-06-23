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

	_rc = RectMakeCenter(WINSIZE_X / 2 - 500, WINSIZE_Y / 2 + 200, 173, 291);

	_radian = 3.141592653f;
	_degree = 180.0f;

	for (int i = 0; i < 5; i++)
	{
		_star[i].x = cosf((i * 72 - 90) * PI / 180.0f) * 200 + WINSIZE_X / 2;
		_star[i].y = sinf((i * 72 - 90) * PI / 180.0f) * 200 + WINSIZE_Y / 2;

		/*
		오망성을 그리기 위한 포인트 5개
		ㄴ 72 / <- 360 / 5
		-90 -> 초기 각도

		Degree -> 라디안으로

		200 -> 중심에서의 거리

		WINSIZE_X / Y -> 중점
		*/
	}

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SAFE_DELETE(_bgImage);
	SAFE_DELETE(_plImage);
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
		_rc.left += 5.0f;
		_rc.right += 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_rc.left -= 5.0f;
		_rc.right -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_rc.top -= 5.0f;
		_rc.bottom -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_rc.top += 5.0f;
		_rc.bottom += 5.0f;
	}

	GetLocalTime(&_st);
	_st.wSecond;
}

void MainGame::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	// PatBlt(): 사각형 안에 영역을 브러쉬로 채우는 함수
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// ========================================================

	char strRadian[128];
	char strDegree[128];
	char strSecond[128];

	sprintf_s(strSecond, "%d 초", _st.wSecond);
	TextOut(memDC, WINSIZE_X / 2, 100, strSecond, strlen(strSecond));

	// 라디안에서 Degree로
	// 1 Radian = 180 / PI Dgree
	sprintf_s(strRadian, "%.2f 라디안 값은 %.2f Degree 값과 같다.", _radian, _radian * (180 / M_PI));
	TextOut(memDC, WINSIZE_X / 2 - 100, WINSIZE_Y / 2 - 100, strRadian, strlen(strRadian));

	// 디그리에서 라디안으로
	// 1 Degree = PI / 180 Radian
	sprintf_s(strDegree, "%.2f 디그리 값은 %.2f 라디안 값과 같다.", _degree, _degree * (PI / 180.0f));
	TextOut(memDC, WINSIZE_X / 2 - 100, WINSIZE_Y / 2, strDegree, strlen(strRadian));

	// CreatePen : 펜 스타일, 길이, 색상
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN currentPen;

	currentPen = (HPEN)SelectObject(memDC, pen);

	LineMake(memDC, WINSIZE_X / 2 - 100, WINSIZE_Y / 2 + 100, WINSIZE_X / 2 + 200, WINSIZE_Y / 2 + 100);

	SetPixel(memDC, _star[0].x, _star[0].y, RGB(255, 0, 0));

	EllipseMakeCenter(memDC, _star[0].x, _star[0].y, 10, 10);

	for (int i = 0; i < 5; i++)
	{
		EllipseMakeCenter(memDC, _star[i].x, _star[i].y, 10, 10);
	}

	// ========================================================
	this->getDoubleBuffer()->render(hdc, 0, 0);
}

void MainGame::fireBullet(void)
{
	
}

/*
과제 1. 아날로그 시계

- 초침 / 분침 / 시침

- 오늘 사용한 SYSTEMTIME을 이용해서 만든다.

- 필수 : 시간 표시

과제 2. 포신 각도에 따른 총알 발사

- 예외 처리 : 포신 앵글을 막아준다. -> 화면 밖으로

- 필수 : 수동 / 자동 버전 -> 총 2가지로

과제 3. 발사된 총알끼리 충돌

- 핵심 요소는 총알끼리 충돌이 되면 자연스럽게 팅겨 나가야 한다.

과제 4. 발사한 총알에 중력 적용

- 총알이 중력을 받아 떨어진다. -> 힘이 다하면

※ 발사된 총알 예외 처리
ㄴ 4번 과제는 제외
ㄴ 발사된 총알은 화면밖으로 나갈 수 없다.
ㄴ 주의 사항 발사된 총알이 화면 끝점에 닿아 팅겨 나갈 때 각도에 신경쓴다.

도전 과제1. 도형 회전

- 사각형을 회전시킨다.

- hdc를 통해 그려온다
ㄴ WinAPI를 활용해 구현
ㄴ Rectangle함수를 이용해서 그린다.

- 화면축이 바뀐 상태면 상대 좌표로 이동하게 구현을 한다.
*/