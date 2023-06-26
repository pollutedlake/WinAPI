#pragma once
#include "GameNode.h"

class SG_Tile : public GameNode
{
private:
	int _index;
	GImage* _image;
	int _position;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(HDC hdc);

	void setIndex(int index) { _index = index; }
	int getIndex() { return _index; }
	void setPosition(int position) { _position = position; }
	int getPosition() { return _position; }

	SG_Tile(int index, GImage* image, int position) : _index(index), _image(image), _position(position) {}
	~SG_Tile() {}
};

