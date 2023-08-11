#include "Stdafx.h"
#include "Flame.h"

HRESULT Flame::init(const char* imageName, float* x, float* y, float offsetY)
{
	_image = IMAGEMANAGER->addFrameImage("�ν���", "Resources/Images/ShootingGame/Flame.bmp", 0.0f, 0.0f, 432, 297, 9, 1, true, RGB(255, 0, 255));
	_x = x;
	_y = y;
	_offsetY = offsetY;

	_rc = RectMakeCenter((int)_x, (int)_y + offsetY, _image->getFrameWidth(), _image->getFrameHeight());

	_flameTick = 7.0f;
	return S_OK;
}

void Flame::release(void)
{

}
//�� Flame Ŭ�������� ���Ͽ� ���� ������ ������ �ȵǸ� MainGame���� Flame�� ���� ������ �� �ʿ䰡 ����.
void Flame::update()
{
	if (FLAME_COUNT + _flameTick <= GetTickCount64())
	{
		_flameTick = GetTickCount64();
		_image->setFrameX(_image->getFrameX() + 1);

		if (_image->getFrameX() >= _image->getMaxFrameX())
		{
			_image->setFrameX(0);
		}
	}
	_rc = RectMakeCenter(*_x, *_y + _offsetY, _image->getFrameWidth(), _image->getFrameHeight());
}

void Flame::render()
{
	_image->frameRender(getMemDC(), _rc.left, _rc.top, _image->getFrameX(), _image->getFrameY());
}