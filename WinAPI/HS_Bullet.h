#pragma once
#include "GameNode.h"

#define PLAYER1			1
#define PLAYER2			2
#define BULLETWIDTH		20
#define BULLETHEIGHT	20

enum BulletType
{
	NORMAL,
	SHOCKWAVE,
	CHARGESHOT,
	SPRINKLER,
	SPRINKLERCHILD
};

class HS_Bullet : public GameNode
{
private:
	POINT position;
	bool active;
	int whoShoot;
	BulletType type;
	int width;
	int height;
	float count;
	int speed;

public:
	virtual HRESULT init(void);
	HRESULT init(int _x, int _y, int _whoShoot, BulletType _type, float _angle);
	virtual void update(void);
	virtual void render(HDC hdc);
	virtual void release();

	float getCount() { return count;}
	void setActive(bool _active) {active = _active;}
	void setPosition(int _x, int _y) {position.x = _x; position.y = _y;}
	bool getActive() {return active;}
	int getWhoShoot() {return whoShoot;}
	RECT getRect() {return RectMakeCenter(position.x, position.y, width, height);}
	POINT getPosition() {return position;}
	int getWidth() {return width;}
	int getHeight() {return height;}
	BulletType getType() {return type;}
};

