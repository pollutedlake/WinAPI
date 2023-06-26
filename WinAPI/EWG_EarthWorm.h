#pragma once
#include "GameNode.h"

struct Circle
{
	float _positionX;
	float _positionY;
	float _dirX;
	float _dirY;
	vector<pair<pair<float, float>, pair<float, float>>> _turn;
	bool _exit;
	int _size;
};

class EWG_EarthWorm : public GameNode
{
private:
	Circle _circles[50];
	float _speed;
	float _angle;

public:
	HRESULT init(void);
	void update(void);
	void render(HDC hdc);
	void release(void);

	void eatItem(int index);

	POINT getHeadPosition() {return {(LONG)_circles[0]._positionX, (LONG)_circles[0]._positionY}; }

	EWG_EarthWorm() {}
	~EWG_EarthWorm() {}
};

