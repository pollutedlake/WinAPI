#include "stdafx.h"
#include "SliceGame.h"
/*
과제 1. 슬라이스 게임

- 치트 필수
ㄴ 1개의 퍼즐을 제외하고 나머지는 정렬
ㄴ 플레이어가 남은 1개를 맞추면서 종료되는 구조

- 화면 왼쪽에 원본 사진 출력 < - > 화면 오른쪽에는 9등분된 이미지 출력

- 9등분 된 이미지 제일 아래 오른쪽 칸이 시작 칸

- 퍼즐이 완성되면 알파블렝딩효과로 이미지가 나타난다.
ㄴ 중앙에서 완성된 이미지를 보여주면 된다.
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
