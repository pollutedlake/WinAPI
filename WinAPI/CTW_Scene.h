#pragma once
#include "GameNode.h"
#include "CTW_BackGround.h"
#include "Player.h"
class CTW_Scene : public GameNode
{
private:
	CTW_BackGround* _backGround;
	Player* _player;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void collisionCheck(RECT playerRC, RECT* platforms);

	CTW_Scene() {}
	virtual ~CTW_Scene() {}
};

