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
����1. ���� ������ ����Ʈ ����

- ���帶�� �ٸ� ����Ʈ ����

- ����Ʈ�� ������ ���� ó��

����2. �� �̻��� �߻�

- ���� �̻����� �߻��ϸ� �̻����� ������ ��ġ�� ���� �Ѵ�.

- ���� �߻��ϴ� �̻����� �߻� �ֱ�� ���ǵ尡 ��� �޶�� �Ѵ�.
*/

/*
����1. SVN or Git ����

- SVN or Git ������ �͵��ؼ� X�� ����� �ǵ��� �������� ��ȭ�� ������.

- �۾� �̷� ĸ���ؼ� ���� ����

���� 2. �ִϸ��̼� Ŭ������ ���� �Լ� �ϼ�

- �̿ϼ� �Լ� �ϼ� ��Ű��

�� setPlayFrame()
�� setPlayFrame()
�� setFPS()

���� 3. ���� ��Ʈ������ ���� �۾�(�ڵ� X -> �̹���)
*/