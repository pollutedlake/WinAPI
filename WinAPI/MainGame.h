#pragma once
#include "GameNode.h"

#define CLASS			0
#define ASSIGNMENT		1
#define MAIN		CLASS

#if MAIN == CLASS
#include "StartScene.h"
#include "SecondScene.h"

#elif MAIN == ASSIGNMENT
//#include "CTW_Scene.h"
//#include "RacingGame.h"
#include "BlackHole.h"
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
	StartScene* _start;
	SecondScene* _second;
	GameNode* _currentScene;
#endif
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	MainGame() {}
	virtual ~MainGame() {}
};