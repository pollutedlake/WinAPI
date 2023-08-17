#pragma once
#include "GameNode.h"
#include "EventListener.h"

// Enemy (�θ�) : ���� �� Ŭ������ ������� �Ϲ� ����, ���� ���� ���� �� �ִ�.
class SG_Enemy : public GameNode, public EventListener
{
protected:
	GImage* _image;
	RECT _rc;
	int _hp;

	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _rndTimeCount;
	float _worldTimeCount;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);
	virtual HRESULT init(const char* imageName, POINT center, int radius, float angle);
	virtual HRESULT init(const char* imageName, POINT position, int rndSpeed);

	void release(void);
	void update(void);
	void render(void);

	virtual void move(void);
	void draw(void);
	void animation(void);

	void getDamaged(void);

	void collision();

	SG_Enemy(void);
	~SG_Enemy(void) {}
};

