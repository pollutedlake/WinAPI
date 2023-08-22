#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"
#include "AniScene.h"

class SG_MainGame : public GameNode
{
private:
	Rocket* _rocket;
	EnemyManager* _em;
	AniScene* _as;
	float _x, _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void collision(void);

	SG_MainGame() {}
	~SG_MainGame() {}
};

/*
과제1. 적이 죽을때 이펙트 구현

- 무장마다 다른 이펙트 구현

- 이펙트는 프레임 렌더 처리

과제2. 적 미사일 발사

- 적이 미사일을 발사하며 미사일은 로켓의 위치로 쏴야 한다.

- 적이 발사하는 미사일은 발사 주기와 스피드가 모두 달라야 한다.
*/

/*
과제1. SVN or Git 점검

- SVN or Git 사용법을 터득해서 X자 모양이 되도록 팀원끼리 대화를 나눈다.

- 작업 이력 캡쳐해서 같이 제출

과제 2. 애니메이션 클래스에 속한 함수 완성

- 미완성 함수 완성 시키기

ㄴ setPlayFrame()
ㄴ setPlayFrame()
ㄴ setFPS()

과제 3. 세미 포트폴리오 선행 작업(코드 X -> 이미지)
*/