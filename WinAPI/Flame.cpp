#include "Stdafx.h"
#include "Flame.h"

HRESULT Flame::init(void)
{
	_image = IMAGEMANAGER->addFrameImage("�ν���", "Resources/Images/ShootingGame/Flame.bmp", 432, 297, 9, 1, true, RGB(255, 0, 255));
	_count = _boosterIndex = _x = _y = 0;
	width = _image->getFrameWidth();
	height = _image->getFrameHeight();
	return S_OK;
}

void Flame::release(void)
{

}
//�� Flame Ŭ�������� ���Ͽ� ���� ������ ������ �ȵǸ� MainGame���� Flame�� ���� ������ �� �ʿ䰡 ����.
void Flame::update(RECT rc)
{
	_count++;

	if (_count % 3 == 0)
	{
		_boosterIndex++;
	}

	_x = rc.left + (rc.right - rc.left) / 2 - width / 2;
	_y = rc.bottom;
}

void Flame::render()
{
	_image->frameRender(getMemDC(), _x, _y, _boosterIndex % 8, 0);
}