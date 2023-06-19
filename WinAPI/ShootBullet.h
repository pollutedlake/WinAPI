#pragma once
#include "GameNode.h"
#include "SB_Player.h"
#include "SB_Bullet.h"

/*
과제 2. 총알 발사

- 하단에서 좌우로 움직일 수 있는 플레이어가 존재

- 스페이스 바를 누르면 플레이어가 총알을 발사한다.
*/

class ShootBullet : public GameNode
{
private:
	SB_Player* player;
	vector<SB_Bullet*> bullets;

public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void release(void);
	virtual void render(HDC hdc);

	ShootBullet() {}
	virtual ~ShootBullet() {}
};

