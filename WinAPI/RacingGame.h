#pragma once
#include "GameNode.h"
#include "RG_Player.h"
#include "RG_BackGround.h"
#include "RG_Enemy.h"

class RacingGame : public GameNode
{
private:
	RG_Player* _player;
	RG_BackGround* _backGround;
	RG_Enemy* _enemy;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	RacingGame() {}
	virtual ~RacingGame() {}
};

