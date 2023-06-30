#pragma once
#include "GameNode.h"

enum class STATE
{
	IDLE,
	MOVE,
	JUMPFORWARD,
	STATENUM
};

class Penitent : public GameNode
{
private:
	GImage* _move;
	GImage* _jumpForward;
	GImage* _idle;
	int _frame;
	int _index;

	POINT _position;
	POINT _velocity;
	RECT _rc;
	
	bool _isLeft;
	STATE _state;

public:
	HRESULT init(bool managerInit);
	void release(void);
	void update(void);
	void render(void);

	RECT getRect() {return _rc;}

	void modifyPosition(RECT rc);

	Penitent() {}
	~Penitent() {}
};

