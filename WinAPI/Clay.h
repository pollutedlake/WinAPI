#pragma once
class Clay
{
private:
	POINT position;
	int type;
	int speed;
	POINT dir;
	BOOL isHit;

public:
	Clay();
	~Clay();
};

