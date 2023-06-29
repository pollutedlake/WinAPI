#pragma once
#include "GameNode.h"

enum class STATE
{
	IDLE,
	MOVE,
	STING,
	DIAGONALLYSTING,
	INAROWSTING,
	SWINGCIRCLE,
	VICTORY,
	SKILLCLIMAX,
	DEFEAT,
	NONE
};

class FrameImage : public GameNode
{
private:
	GImage* _idle;
	GImage* _move;
	GImage* _sting;
	GImage* _swingCircle;
	GImage* _diagonallySting;
	GImage* _inARowSting;
	GImage* _victory;
	GImage* _defeat;
	GImage* _skill;
	GImage* _background;
	GImage* _skill1;
	GImage* _skill2;
	GImage* _skill3;
	bool _gameScene;
	int _count;
	int _index;
	RECT _rc[9];
	STATE _state; 
	bool _isLeft;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC hdc);

	FrameImage() {}
	~FrameImage() {}
};

