#pragma once
#include "GameNode.h"
#include "Flame.h"
// 설계와의 싸움

#define ROCKET_SPEED 3.0f

class Rocket : public GameNode
{
private:

	GImage* _image;
	Flame* _flame;

	RECT _rc;
	float _x, _y;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Rocket() {}
	~Rocket() {}
};