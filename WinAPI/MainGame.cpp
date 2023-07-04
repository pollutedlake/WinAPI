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
	//_assignment = new CTW_Scene;			// 캐릭터 벽짚기, 미니맵 연동
	//_assignment = new RacingGame;			// 레이싱게임
	_assignment = new BlackHole;			// 블랙홀
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
1. 기획서 올인

2. 기획서 브릿지

-목차, 중제목

- 개요
- 프로젝트 목표/제작의도
- 00장르의 00게임을 레퍼런스로한 게임 개발
- 0000한 재미를 느끼게하려 함

- 게임 소개
- 게임명, 게임소개, 게임특징
- 제작인원, 제작 도구, 제작 언어, 사용 스킬
- 개발계획(일정)
- 기능()

-결과/회고
- 00기술 능력 획득
- 느낀점, 배운점, 개선할 부분, 보충학습한 내용과 참고한 자료(교재/링크/영상 등)
- 면접/취업과 연관된 부분

- 플로우 차트

- 클래스 구조도

- 개발 일정

- 개발 툴
비주얼 스튜디오 버전 포토샵버전 영상편집프로그램
15장~20장

과제1. 포트폴리오 PPT 작성

- 발표일은 아직 미정

- 디테일하게 + 깔끔하게

과제 2. 블랙홀

- 무작위로 생성되는 오브젝트 객체

- 그리고 주변 오브젝트를 빨아들이는 블랙홀을 만든다
ㄴ 블랙홀은 조작을 통해서 움직일 수 있다.

- 오브젝트가 생성되는 위치를 알기 위해 표시를 한다.
ㄴ EX : 색 / 이미지 / 크기

- 필수 : STL -> vetor or list를 반드시 써서 진행
*/