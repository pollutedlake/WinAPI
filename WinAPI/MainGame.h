#pragma once
#include "GameNode.h"
#include "Card.h"
#include "Example_Mole.h"

// 0. 상속을 받은 클래스
// 1. 최상위 관리자 클래스
// 2. 대리자 (오류 맞고 사망하는 클래스)

/*
과제가 두더지.......
1. 두더지 + 맵
ㄴ 클래스 분할..?
	ㄴ 상속 ? / 클래스 갯수? STL?
ㄴ 아직 프레임워크에 이해가 덜

2. 체계 (열거 / 클래스 / 구조체)

3. 구체화
	ㄴ PCH / 함수 -> 로직 구현
*/

enum CURRENT_RECT
{
	CURRENTRECT_A, CURRENTRECT_B,
	CURRENTRECT_C, CURRENTRECT_D,
	CURRENTRECT_E, CURRENTRECT_F,
	CURRENTRECT_G, CURRENTRECT_H,
	CURRENTRECT_NULL
};

class MainGame : public GameNode
{
private:
	Example_Mole* _mole;

	CURRENT_RECT _currentRect;
	RECT _rc[8];
	int _index;					// 두더지 인덱스 (8개)
	int _count;					// 타이머용 카운트
	int _time;					// 랜덤시간 변수
	int _score;					// 점수

	bool _bIsSelected;			// 
	bool _bIsOnceCheck;			// 

	POINT pt;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	MainGame() {}
	~MainGame() {}
};

