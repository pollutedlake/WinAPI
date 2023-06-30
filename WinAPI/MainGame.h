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

// 0. ����� ���� Ŭ����
// 1. �ֻ��� ������ Ŭ����
// 2. �븮�� (���� �°� ����ϴ� Ŭ����)

// ���� ����

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