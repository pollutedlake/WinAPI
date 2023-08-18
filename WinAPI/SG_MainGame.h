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
����1. ���� ������ ����Ʈ ����

- ���帶�� �ٸ� ����Ʈ ����

- ����Ʈ�� ������ ���� ó��

����2. �� �̻��� �߻�

- ���� �̻����� �߻��ϸ� �̻����� ������ ��ġ�� ���� �Ѵ�.

- ���� �߻��ϴ� �̻����� �߻� �ֱ�� ���ǵ尡 ��� �޶�� �Ѵ�.
*/