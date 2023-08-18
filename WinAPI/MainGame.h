#pragma once
#include "GameNode.h"

#define CLASS			0
#define ASSIGNMENT		1
#define SHOOTINGGAME	2
#define MAIN		SHOOTINGGAME

#if MAIN == CLASS
#include "StartScene.h"
#include "SecondScene.h"

#elif MAIN == ASSIGNMENT
//#include "CTW_Scene.h"
//#include "RacingGame.h"
//#include "BlackHole.h"
#include "Cube.h"
//#include "TileMap.h"
#elif MAIN == SHOOTINGGAME
//#include "Rocket.h"
//#include "EnemyManager.h"
#include "SG_MainGame.h"
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
#elif MAIN == SHOOTINGGAME
	//EnemyManager* _em;
#endif
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

#if MAIN == SHOOTINGGAME
	void collision(void);
#endif

	MainGame() {}
	virtual ~MainGame() {}
};