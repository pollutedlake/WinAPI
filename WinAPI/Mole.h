#pragma once
class Mole
{
private:
	BOOL active;
	int height;
	int waitTime;
	BOOL up;

public:
	void setActive(BOOL _active) {active = _active;}
	BOOL getActive() { return active;}
	int getHeight() {return height;}
	void update();

	BOOL checkHit(POINT pt, int i);

	Mole();
	~Mole();
};

