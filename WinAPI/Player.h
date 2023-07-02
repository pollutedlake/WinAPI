#pragma once

enum class STATE
{
	IDLE,
	MOVE,
	JUMPFORWARD,
	CLIMB,
	CATCHCORNER,
	FALL,
	GoUp,
	STATENUM
};

class Player
{
private:
	GImage* _move;
	GImage* _jumpForward;
	GImage* _idle;
	GImage* _climb;
	GImage* _goUp;
	int _frame;
	int _index;

	POINT _position;
	POINT _velocity;
	RECT _rc;
	RECT _catchPlatform;
	
	bool _isLeft;
	STATE _state;
	int _gravity;
	bool _canPhysics;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	RECT getRect() {return _rc;}

	void modifyPosition(RECT rc, RECT platform);
	void setStateFall();

	Player() {}
	~Player() {}
};

