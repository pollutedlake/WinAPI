#include "stdafx.h"
#include "SliceGame.h"
/*
���� 1. �����̽� ����

- ġƮ �ʼ�
�� 1���� ������ �����ϰ� �������� ����
�� �÷��̾ ���� 1���� ���߸鼭 ����Ǵ� ����

- ȭ�� ���ʿ� ���� ���� ��� < - > ȭ�� �����ʿ��� 9��е� �̹��� ���

- 9��� �� �̹��� ���� �Ʒ� ������ ĭ�� ���� ĭ

- ������ �ϼ��Ǹ� ���ĺ����ȿ���� �̹����� ��Ÿ����.
�� �߾ӿ��� �ϼ��� �̹����� �����ָ� �ȴ�.
*/

HRESULT SliceGame::init(void)
{
    GameNode::init();
    _image = new GImage;
    _image->init("Resources/Images/BackGround/DeadSpace.bmp", WINSIZE_X / 2, WINSIZE_Y / 2);
    for (int i = 0; i < 9; i++)
    {
        _tiles[i] = new SG_Tile(i, _image, i);
    }
    int shuffleN = RND->getFromIntTo(500, 999);
    for (int i = 0; i < shuffleN; i++)
    {
        int dest = RND->getInt(8);
        int sour = RND->getInt(8);
        int temp = _tiles[dest]->getIndex();
        _tiles[dest]->setIndex(_tiles[sour]->getIndex());
        _tiles[sour]->setIndex(temp);
    }
    _playerPos = 8;
    return S_OK;
}

void SliceGame::update(void)
{
    GameNode::update();
    if (isClear())
    {
        _alpha++;
        if (_alpha > 255)
        {
            _alpha = 255;
        }
    }
    else
    {
        if (KEYMANAGER->isOnceKeyDown(VK_UP) && _playerPos / 3 != 0)
        {
            _tiles[_playerPos]->setIndex(_tiles[_playerPos - 3]->getIndex());
            _playerPos -= 3;
        }
        if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _playerPos / 3 != 2)
        {
            _tiles[_playerPos]->setIndex(_tiles[_playerPos + 3]->getIndex());
            _playerPos += 3;
        }
        if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _playerPos % 3 != 0)
        {
            _tiles[_playerPos]->setIndex(_tiles[_playerPos - 1]->getIndex());
            _playerPos -= 1;
        }
        if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _playerPos % 3 != 2)
        {
            _tiles[_playerPos]->setIndex(_tiles[_playerPos + 1]->getIndex());
            _playerPos += 1;
        }
        if (KEYMANAGER->isOnceKeyDown(VK_F1))
        {
            for (int i = 0; i < 7; i++)
            {
                _tiles[i]->setIndex(i);
            }
            _tiles[8]->setIndex(7);
            _playerPos = 7;
        }
    }
}

void SliceGame::release(void)
{
    GameNode::release();
    for (int i = 0; i < 8; i++)
    {
        SAFE_DELETE(_tiles[i]);
    }
    SAFE_DELETE(_image);
}

void SliceGame::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	
    _image->render(memDC, 0, WINSIZE_Y / 4);
    for (int i = 0; i < 9; i++)
    {
        if (i == _playerPos)
        {
            continue;
        }
        _tiles[i]->render(memDC);
    }
    if (isClear())
    {
        _image->alphaRender(memDC, 10, 10, WINSIZE_X - 20, WINSIZE_Y - 20, 0, 0, WINSIZE_X / 2, WINSIZE_Y / 2, _alpha);
    }

	this->getDoubleBuffer()->render(hdc, 0, 0);
}

bool SliceGame::isClear()
{
    for (int i = 0; i < 8; i++)
    {
        if (_tiles[i]->getIndex() != _tiles[i]->getPosition())
        {
            return false;
        }
    }
    return true;
}
