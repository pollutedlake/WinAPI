#pragma once
class BH_BlackHole
{
private:
	float _posX;
	float _posY;
	float _radius;

public:
	HRESULT init(void);
	void release(void);
	bool update(void);
	void render(HDC hdc);

	pair<float, float> getPosition() { return make_pair(_posX, _posY); }

	BH_BlackHole() {}
	virtual ~BH_BlackHole() {}
};

