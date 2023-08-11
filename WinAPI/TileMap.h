#pragma once
#include "GameNode.h"


class TileMap : public GameNode
{
private:
	vector<bitset<100>> _tileMap;
	GImage* _image;
	int _tileSize;
	int _tileWidth;
	int _tileHeight;
	int _selectImage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	TileMap() {}
	~TileMap() {}
};

