#pragma once
#include "GameNode.h"
#include "EWG_EarthWorm.h"

struct Item
{
	POINT _position;
	int _index;
};

class EarthWormGame : public GameNode
{
private:
	EWG_EarthWorm* _earthWorm;
	Item _item;
	POINT _itemPosition;
	int _itemTime;
	bool _itemRegen;

public:
	HRESULT init(void);
	void update(void);
	void release(void);
	void render(HDC hdc);

	EarthWormGame() {}
	~EarthWormGame() {}
};

