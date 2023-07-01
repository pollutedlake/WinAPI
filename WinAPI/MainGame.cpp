#include "Stdafx.h"
#include "MainGame.h"
#define _USE_MATH_DEFINES
#include<math.h>

HRESULT MainGame::init(void)
{
	GameNode::init(true);
#if MAIN == CLASS
	IMAGEMANAGER->addImage("DeadSpace", "Resources/Images/BackGround/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);

	_alphaA = 255;
#elif MAIN == ASSIGNMENT
	_assignment = new CTW_Scene;
	_assignment->init();
#endif
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
#if MAIN == CLASS
#elif MAIN == ASSIGNMENT
	_assignment->release();
	SAFE_DELETE(_assignment);
#endif
}

void MainGame::update(void)
{
	GameNode::update();
#if MAIN == CLASS
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "게임을 종료하시겠습니까?", "종료확인", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
#elif MAIN == ASSIGNMENT
	_assignment ->update();
#endif	

}

void MainGame::render(void)
{
	// PatBlt(): 사각형 안에 영역을 브러쉬로 채우는 함수
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// ========================================================
#if MAIN == CLASS
	IMAGEMANAGER->findImage("DeadSpace")->alphaRender(getMemDC(), _alphaA);
#elif MAIN == ASSIGNMENT
	_assignment->render();
#endif
	// ========================================================
	this->getBackBuffer()->render(getHDC());
}

/*
과제1. 캐릭터 벽잡기

이미지 필수 : 배경, 벽, 캐릭터(대기,이동,점프,벽을 잡고있는 모션)

기본적으로 벽을 잡을때는 가장 위쪽 모서리를 잡으며 벽 중간을 잡았을경우 천천히 지면으로 내려운다

캐릭터가 벽을 잡고 있는 상태에서 위 / 또는 아래방향키를 누르면 올라가거나 내려갈수 있어야한다.

또한 캐릭터가 벽 위로 올라선 다음 다시 아래로 점프하면 캐릭터는 지면에 착지할수있어야한다

캐릭터 점프 높이의 지형이 있고 캐릭터는 지형 밑에서 점프로 지형 위 올라 갈 수있다

캐릭터는 지형에 올라선 상태에서 지면으로 다시 내려올 수 있으면 ok

과제2. 미니맵 연동

플레이어의 움직임을 미니맵에서 그대로 확인해야 한다
ㄴ 움직임까지 동일하게
*/