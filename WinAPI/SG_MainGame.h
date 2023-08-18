#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"

class SG_MainGame : public GameNode
{
private:
	Rocket* _rocket;
	EnemyManager* _em;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void collision(void);

	SG_MainGame() {}
	virtual ~SG_MainGame() {}
};

/*
과제1. 적이 죽을때 이펙트 구현

- 무장마다 다른 이펙트 구현

- 이펙트는 프레임 렌더 처리

과제2. 적 미사일 발사

- 적이 미사일을 발사하며 미사일은 로켓의 위치로 쏴야 한다.

- 적이 발사하는 미사일은 발사 주기와 스피드가 모두 달라야 한다.
*/