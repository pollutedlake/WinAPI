#pragma once
class Mole
{
private:
	BOOL active;
	int height;
	int waitTime;
	BOOL up;
	int isRed;
	int twinkleTime;
	

public:
	void setActive(BOOL _active) {active = _active;}
	BOOL getActive() { return active;}
	int getHeight() {return height;}
	void update();
	int getIsRed() {return isRed;}

	BOOL checkHit(POINT pt, int i);

	Mole();
	~Mole();
};

