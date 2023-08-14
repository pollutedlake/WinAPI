#pragma once
#include "GameNode.h"


class TileMap : public GameNode
{
private:
	vector<bitset<100>> _tileMap;
	GImage* _image;
	int _tileSize;
	char _tileSizeChar[20];
	int _index;
	float _tileWidth;
	float _tileHeight;
	//int _selectImage;
	POINT _offset;
	bool _input;
	bool _click;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	TileMap() {}
	~TileMap() {}
};

