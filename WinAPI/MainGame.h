#pragma once
#include "GameNode.h"

// 0. 상속을 받은 클래스
// 1. 최상위 관리자 클래스
// 2. 대리자 (오류 맞고 사망하는 클래스)

// 설계 연습

class MainGame : public GameNode
{
private:
	GImage* _bgImage;
	GImage* _plImage;
	GImage* _nine;		// 프레임 이미지
	RECT _rc;

	int _count;
	int _alphaA;
	int _index;
	bool _isLeft;
	bool _isAlphaIncrease;
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void fireBullet(void);

	MainGame() {}
	virtual ~MainGame() {}
};