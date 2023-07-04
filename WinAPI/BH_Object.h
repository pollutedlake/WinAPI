#pragma once

#define SPEED		5

class BH_Object
{
private:
	float _vectorX;
	float _vectorY;
	float _posX;
	float _posY;
	float _radius;
	bool _active;

public:
	HRESULT init(pair<float, float> blackHolePos);
	void release(void);
	void update(pair<float, float> blackHolePos);
	void render(HDC hdc);

	void setVector(pair<float, float> blackHolePos);
	bool getActive() { return _active; }

	BH_Object() {}
	virtual ~BH_Object() {}
};

