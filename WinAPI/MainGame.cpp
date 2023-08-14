#include "Stdafx.h"
#include "MainGame.h"
#include "ResourcesClass.h"
HRESULT MainGame::init(void)
{
	GameNode::init(true);
#if MAIN == CLASS
	_start = new StartScene;
	_start->init();

	_second = new SecondScene;
	_second->init();

	//_currentScene -> 시동이 안되면 그냥 실행 자체가 안된다 -> 굳이 돌려볼 필요가 없다
	_currentScene = _start;

	//assert: 프로그램을 종료시킴
	//C
	assert(_currentScene != nullptr, "MainGame 초기화 부분에서 노드 파트 오류 발생");
	//C++
	//static_assert(): 


	/*
	▶assert

	안정성을 위해 사용

	디버깅 모드에서 동작하는 오류 검출용 함수
	ㄴ릴리즈 모드에서는 동작하지 않는다.

	-assert 함수에 걸리게 되면 버그 발생 위치 / 콜 스택등 여러 정보를 알 수 있다.
	   ㄴExpression -> false -> assert error

	대부분의 문법이 true일때만 동작하지만 assert는 false일때 동작한다.
	ㄴ그렇기 떄문에 일어나면 안되는 조건이 아니라 꼭 일어나야 하는 조건을 명시해야 한다.

	Ex) assert(A != NULL);
	   ㄴA가 NULL이 아니면 true 가 나오게 되므로 패스
	   ㄴA가 NULL이 나오면 false 가 나오게 되므로 assert error

	assert(): "C" -> 컴파일 타임을 지나 프로그램을 실행 시키고 문제를 파악하겠다.
	static_assert(): "C++" -> 컴파일 중에 문제를 파악

	컴파일 중에 문제를 확인하기 위해선 상수값을 넣어줘야 한다.

	*/

#elif MAIN == ASSIGNMENT
	//_assignment = new CTW_Scene;			// 캐릭터 벽짚기, 미니맵 연동
	//_assignment = new RacingGame;			// 레이싱게임
	//_assignment = new BlackHole;			// 블랙홀
	//_assignment = new Cube;
	//_assignment = new TileMap;

	/*std::shared_ptr<Rocket> PlayerA = std::make_shared<Rocket>();
	std::shared_ptr<Rocket> PlayerB = PlayerA->get_shared_ptr();*/

	//PlayerA.use_count();
#elif MAIN == SHOOTINGGAME
	IMAGEMANAGER->addImage("슈팅 맵", "Resources/Images/ShootingGame/ShootingBG.bmp", WINSIZE_X, WINSIZE_Y);
	_assignment = new Rocket;
	_em = new EnemyManager;
	_em->init();
	_assignment->init();
#endif
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
#if MAIN == CLASS
	SAFE_DELETE(_start);
	SAFE_DELETE(_second);

#elif MAIN == ASSIGNMENT
	_assignment->release();
	SAFE_DELETE(_assignment);
#elif MAIN == SHOOTINGGAME
	_assignment->release();
	_em->release();
	SAFE_DELETE(_assignment);
#endif
}

void MainGame::update(void)
{
	GameNode::update();
#if MAIN == CLASS
	_currentScene->update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))_currentScene = _second;
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))_currentScene = _start;

#elif MAIN == ASSIGNMENT
	_assignment ->update();
#elif MAIN == SHOOTINGGAME
	_assignment->update();
	_em->update();
#endif	

}

void MainGame::render(void)
{
	// PatBlt(): 사각형 안에 영역을 브러쉬로 채우는 함수
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// ========================================================
#if MAIN == CLASS
	_currentScene->render();
	TCHAR* fontName = TEXT("휴먼굴림");
	LPCWSTR test[] = {L"안\n녕,", L"나는\n", L"박상현이얗\nㅎㅎㅎ"};
	LPCWSTR test2 = L"안\n녕";
	char* test3 = "안\n녕";
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, fontName, 25, 500, test, sizeof(test) / sizeof(*test), NULL, RGB(0, 0, 255));

#elif MAIN == ASSIGNMENT
	_assignment->render();
#elif MAIN == SHOOTINGGAME
	IMAGEMANAGER->findImage("슈팅 맵")->render(getMemDC());
	_assignment->render();
	_em->render();
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

과제1. 캐릭터 공격 및 방어

- 필수 : 이미지 -> 배경 / 체력바 / 플레이어 (대기, 공격, 방어), 적(대기, 공격, 피격)

- 기본 형식은 대전게임처럼 좌 / 우로 배치
ㄴ + 체력바

- 플레이어는 공격 및 방어를 할 수 있고 적은 공격 및 피격 모션이 존재한다.
ㄴ 적 : 허수아비

- 플레이어는 상시 조종 < - > 적은 공격 On / Off 기능만 (이동 X)

- 공격, 방어, 피격 등이 발생하면 상황에 맞는 결과를 화면에 렌더링 한다.
ㄴ 막기, 빗나감, 치명타 등

- 데미지도 표기한다.
ㄴ컨버팅 할 수 있으면 해본다.
*/