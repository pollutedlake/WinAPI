#pragma once
#include "GameNode.h"
#include "EventListener.h"

#define MAX_BULLET 50

// ��� -> ������.
struct tagBullet : public EventListener
{
	GImage* img;
	RECT rc;
	int radius;
	int count;
	float x, y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;
	void collision() {cout << "�̻���" << endl; }
};

class Missile : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
public:

	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	Missile() {}
	~Missile() {}
};

// �߻簡 �ɶ����� ����� ����
class MissileM1 : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;
public:

	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	MissileM1() {}
	~MissileM1() {}
};

class Beam : public GameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	typedef vector<tagBullet>::iterator iterBullet;

	float _range;
	int _bulletMax;
public:

	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y);
	void draw(void);
	void move(void);

	Beam() {}
	~Beam() {}
};