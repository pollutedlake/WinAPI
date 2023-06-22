#pragma once
#include "GameNode.h"
#include "GImage.h"

class FWP_Paint : public GameNode
{
private:
	GImage* _paint;
	int _stage;
	vector<std::pair<POINT, bool>> _wrongPoint;
	int correctN;

public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void release(void);
	virtual void render(HDC hdc);
	bool isCorrect();

	int getWrongPointN() {return _wrongPoint.size();}
	bool isFinish() {return correctN == _wrongPoint.size();}

	FWP_Paint(int stage) : _stage(stage) { };
	virtual ~FWP_Paint() {};
};

