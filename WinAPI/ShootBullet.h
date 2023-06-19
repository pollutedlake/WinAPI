#pragma once
#include "GameNode.h"
#include "SB_Player.h"
#include "SB_Bullet.h"

/*
���� 2. �Ѿ� �߻�

- �ϴܿ��� �¿�� ������ �� �ִ� �÷��̾ ����

- �����̽� �ٸ� ������ �÷��̾ �Ѿ��� �߻��Ѵ�.
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

