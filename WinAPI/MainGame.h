#pragma once
#include "GameNode.h"

#define CLASS			0
#define CATCHTHEWALL	1
#define MINIMAP			2
#define MAIN		CATCHTHEWALL

#if MAIN == CLASS
#elif MAIN == CATCHTHEWALL
#include "CTW_Scene.h"
#elif MAIN == MINIMAP
#endif

// 0. 상속을 받은 클래스
// 1. 최상위 관리자 클래스
// 2. 대리자 (오류 맞고 사망하는 클래스)

// 설계 연습

class MainGame : public GameNode
{
private:
#if MAIN == CLASS
	GImage* _bgImage;

	int _alphaA;
#elif MAIN == CATCHTHEWALL
	CTW_Scene* _ctw;
#elif MAIN == MINIMAP
#endif
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	MainGame() {}
	virtual ~MainGame() {}
};