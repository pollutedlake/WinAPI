#pragma once
#include "GameNode.h"
#include "SG_Tile.h"
class SliceGame : public GameNode
{
private:
	GImage* _image;
	SG_Tile* _tiles[9];
	int _playerPos;
	int _alpha = 0;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(HDC hdc);

	bool isClear();

	SliceGame() {}
	~SliceGame() {}
};

