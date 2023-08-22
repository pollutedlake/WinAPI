#pragma once
#include "GameNode.h"
#include "Animation.h"

class AniScene : public GameNode
{
private:
	GImage* _image;
	Animation* _animationA;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	AniScene() {}
	~AniScene() {}
};

