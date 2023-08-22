#include "stdafx.h"
#include "AniScene.h"


HRESULT AniScene::init(void)
{
	//_image = IMAGEMANAGER->addImage("内尝府", "Resources/Images/Object/InARowSting.bmp", 660, 268, true, RGB(255, 0, 255));
	_image = IMAGEMANAGER->addImage("内尝府", "Resources/Images/Object/InARowSting.bmp", 12111, 774, true, RGB(255, 0, 255));

	_animationA = new Animation;
	//_animationA->init(_image->getWidth(), _image->getHeight(), 110, 67);
	_animationA->init(_image->getWidth(), _image->getHeight(), 1101, 387);
	//_animationA->setDefPlayFrame(false, true);
	//_animationA->setPlayFrame(2, 7, false, true);
	int test[8] = {0, 5, 7, 9, 2, 11, 15, 3};
	_animationA->setPlayFrame(test, 8, true);
	_animationA->setFPS(3);

	return S_OK;
}

void AniScene::release(void)
{
	_animationA->release();
	SAFE_DELETE(_animationA);
}

void AniScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_animationA->AniStart();
	}

	_animationA->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AniScene::render(void)
{
	//_image->aniRender(getMemDC(), WINSIZE_X / 2 - 50, WINSIZE_Y / 2 - 35, _animationA);
	_image->aniRender(getMemDC(), WINSIZE_X / 2 - 550, WINSIZE_Y / 2 - 193, _animationA);
}
