#pragma once
#include "GameNode.h"

#define CLASS			0
#define ASSIGNMENT		1
#define MAIN		ASSIGNMENT

#if MAIN == CLASS
#elif MAIN == ASSIGNMENT
#include "CTW_Scene.h"
#endif

// 0. ����� ���� Ŭ����
// 1. �ֻ��� ������ Ŭ����
// 2. �븮�� (���� �°� ����ϴ� Ŭ����)

// ���� ����

class MainGame : public GameNode
{
private:
	GameNode* _assignment;
#if MAIN == CLASS
	GImage* _bgImage;

	int _alphaA;
#endif
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	MainGame() {}
	virtual ~MainGame() {}
};