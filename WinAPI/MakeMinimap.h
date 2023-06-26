#pragma once
#include "GameNode.h"
class MakeMinimap : public GameNode
{
private:
	GImage* _map;
	GImage* _minimapPlayer;
	POINT _playerPos;
	POINT _mapPos;
	bool _isMinimap;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(HDC hdc);

	MakeMinimap() {}
	~MakeMinimap() {}
};

