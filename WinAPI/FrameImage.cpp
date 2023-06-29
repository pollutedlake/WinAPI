#include "stdafx.h"
#include "FrameImage.h"

/*
과제 2. 프레임 이미지 처리
- 시작 씬 + 게임 씬

- 게임씬에서는 아래의 이미지를 GUI화 시켜서 재생 시킨다. (버튼)
ㄴ프레임 렌더

- 필수 이미지:

ㄴ 배경, 대기, 이동(좌 + 우), 찌르기(좌 + 우), 대각선 찌르기, 연속 찌르기(좌, 우), 원 돌리기, 승리 포즈(옷 던지기), 스킬 클라이막스 연출, 패배
*/

HRESULT FrameImage::init(void)
{
	GameNode::init();
	_idle = new GImage;
	_move = new GImage;
	_sting = new GImage;
	_swingCircle = new GImage;
	_diagonallySting = new GImage;
	_inARowSting = new GImage;
	_victory = new GImage;
	_defeat = new GImage;
	_skill = new GImage;
	_background = new GImage;
	_skill1 = new GImage;
	_skill2 = new GImage;
	_skill3 = new GImage;
	_background = new GImage;
	_idle->init("Resources/Images/Object/Idle.bmp", 3384, 393, 9, 1, true, RGB(255, 0, 255));
	_move->init("Resources/Images/Object/Move.bmp", 4576, 810, 11, 2, true, RGB(255, 0, 255));
	_sting->init("Resources/Images/Object/Sting.bmp", 8195, 830, 11, 2, true, RGB(255, 0, 255));
	_swingCircle->init("Resources/Images/Object/SwingCircle.bmp", 9054, 797, 9, 1, true, RGB(255, 0, 255));
	_diagonallySting->init("Resources/Images/Object/DiagonallySting.bmp", 2996, 457, 7, 1, true, RGB(255, 0, 255));
	_inARowSting->init("Resources/Images/Object/InARowSting.bmp", 12111, 774, 11, 2, true, RGB(255, 0, 255));
	_victory->init("Resources/Images/Object/Victory.bmp", 15295, 427, 23, 1, true, RGB(255, 0, 255));
	_defeat->init("Resources/Images/Object/Defeat.bmp", 5070, 389, 13, 1, true, RGB(255, 0, 255));
	_skill->init("Resources/Images/Object/Skill.bmp", 10024, 575, 14, 1, true, RGB(255, 0, 255));
	_skill1->init("Resources/Images/Object/Skill1.bmp", WINSIZE_X / 2, WINSIZE_Y, true, RGB(255, 0, 255));
	_skill2->init("Resources/Images/Object/Skill2.bmp", WINSIZE_X / 2, WINSIZE_Y / 2, true, RGB(255, 0, 255));
	_skill3->init("Resources/Images/Object/Skill3.bmp", WINSIZE_X, WINSIZE_Y, true, RGB(255, 0, 255));
	_background->init("Resources/Images/BackGround/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);
	_gameScene = false;
	for(int i = 0; i < 9; i++)
	{
		_rc[i] = {0, 50 * i, 100, 50 + 50 * i};
	}
	_count = 0;
	_index = 0;
	_state = STATE::NONE;
	_isLeft = false;
	return S_OK;
}

void FrameImage::release(void)
{
	GameNode::release();
}

void FrameImage::update(void)
{
	GameNode::update();
	if(_gameScene == true)
	{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if(PtInRect(&_rc[0], _ptMouse))
		{
			_state = STATE::IDLE;
			_count = 0;
			_index = 0;
			_isLeft = false;
		}
		else if (PtInRect(&_rc[1], _ptMouse))
		{
			_state = STATE::MOVE;
			_count = 0;
			_index = 0;
			_isLeft = !_isLeft;
			if (_isLeft == true)
			{
				_move->setFrameY(0);
			}
			else
			{
				_move->setFrameY(1);
			}
		}
		else if (PtInRect(&_rc[2], _ptMouse))
		{
			_state = STATE::STING;
			_count = 0;
			_index = 0;
			_isLeft = !_isLeft;
			if (_isLeft == true)
			{
				_sting->setFrameY(0);
			}
			else
			{
				_sting->setFrameY(1);
			}
		}
		else if (PtInRect(&_rc[3], _ptMouse))
		{
			_state = STATE::DIAGONALLYSTING;
			_count = 0;
			_index = 0;
			_isLeft = false;
		}
		else if (PtInRect(&_rc[4], _ptMouse))
		{
			_state = STATE::INAROWSTING;
			_count = 0;
			_index = 0;
			_isLeft = !_isLeft;
			if (_isLeft == true)
			{
				_inARowSting->setFrameY(0);
			}
			else
			{
				_inARowSting->setFrameY(1);
			}
		}
		else if (PtInRect(&_rc[5], _ptMouse))
		{
			_state = STATE::SWINGCIRCLE;
			_count = 0;
			_index = 0;
			_isLeft = false;
		}
		else if (PtInRect(&_rc[6], _ptMouse))
		{
			_state = STATE::VICTORY;
			_count = 0;
			_index = 0;
			_isLeft = false;
		}
		else if (PtInRect(&_rc[7], _ptMouse))
		{
			_state = STATE::SKILLCLIMAX;
			_count = 0;
			_index = 0;
			_isLeft = false;
		}
		else if (PtInRect(&_rc[8], _ptMouse))
		{
			_state = STATE::DEFEAT;
			_count = 0;
			_index = 0;
			_isLeft = false;
		}
	}
	switch (_state)
	{
	case STATE::IDLE:
		_count++;
		if (_count % 5 == 0)
		{
			_index++;
			_idle->setFrameX(_index % _idle->getMaxFrameX());
		}
		break;
	case STATE::MOVE:
		_count++;
		if (_count % 5 == 0)
		{
			_index++;
			if(_isLeft == false)
			{
				_move->setFrameX(_move->getMaxFrameX() - _index % _move->getMaxFrameX());
			}
			else
			{
				_move->setFrameX(_index % _move->getMaxFrameX());
			}
		}
		break;
	case STATE::STING:
		_count++;
		if (_count % 5 == 0)
		{
			_index++;
			if (_isLeft == false)
			{
				_sting->setFrameX(_sting->getMaxFrameX() - _index % _sting->getMaxFrameX());
			}
			else
			{
				_sting->setFrameX(_index % _sting->getMaxFrameX());
			}
		}
		break;
	case STATE::DIAGONALLYSTING:
		_count++;
		if (_count % 5 == 0)
		{
			_index++;
			_diagonallySting->setFrameX(_diagonallySting->getMaxFrameX() - _index % _diagonallySting->getMaxFrameX());
		}
		break;
	case STATE::INAROWSTING:
		_count++;
		if (_count % 5 == 0)
		{
			_index++;
			if (_isLeft == false)
			{
				_inARowSting->setFrameX(_inARowSting->getMaxFrameX() - _index % _inARowSting->getMaxFrameX());
			}
			else
			{
				_inARowSting->setFrameX(_index % _inARowSting->getMaxFrameX());
			}
		}
		break;
	case STATE::SWINGCIRCLE:
		_count++;
		if (_count % 5 == 0)
		{
			_index++;
			_swingCircle->setFrameX(_index % _swingCircle->getMaxFrameX());
		}
		break;
	case STATE::SKILLCLIMAX:
		_count++;
		if(_count > 400)
		{
		if (_count % 5 == 0)
			{
				_index++;
				if (_index % _skill->getMaxFrameX() == 0)
				{
					_count = 0;
				}
				_skill->setFrameX(_index % _skill->getMaxFrameX());
			}
		}
		break;
	case STATE::VICTORY:
		_count++;
		if (_count % 5 == 0)
		{
			_index++;
			_victory->setFrameX(_index % _victory->getMaxFrameX());
		}
		break;
	case STATE::DEFEAT:
		_count++;
		if (_count % 5 == 0)
		{
			_index++;
			_defeat->setFrameX(_index % _defeat->getMaxFrameX());
		}
		break;
	}
	}
	else
	{
	if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
	if (PtInRect(&RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 50), _ptMouse))
	{
		_gameScene = true;
	}
	}
	}
}

void FrameImage::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	// PatBlt(): 사각형 안에 영역을 브러쉬로 채우는 함수
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);
	// ========================================================
	_background->render(memDC);
	if(_gameScene == true)
	{
	switch (_state)
	{
	case STATE::NONE:
		_idle->render(memDC, WINSIZE_X / 2 - _idle->getFrameWidth() / 2, WINSIZE_Y / 2 - _idle->getFrameHeight() / 2, 0, 0, _idle->getFrameWidth(), _idle->getFrameHeight());
		break;
	case STATE::IDLE:
		_idle->frameRender(memDC, WINSIZE_X / 2 - _idle->getFrameWidth() / 2, WINSIZE_Y / 2 - _idle->getFrameHeight() / 2);
		break;
	case STATE::MOVE:
		_move->frameRender(memDC, WINSIZE_X / 2 - _move->getFrameWidth() / 2, WINSIZE_Y / 2 - _move->getFrameHeight() / 2);
		break;
	case STATE::STING:
		_sting->frameRender(memDC, WINSIZE_X / 2 - _sting->getFrameWidth() / 2, WINSIZE_Y / 2 - _sting->getFrameHeight() / 2);
		break;
	case STATE::DIAGONALLYSTING:
		_diagonallySting->frameRender(memDC, WINSIZE_X / 2 - _diagonallySting->getFrameWidth() / 2, WINSIZE_Y / 2 - _diagonallySting->getFrameHeight() / 2);
		break;
	case STATE::INAROWSTING:
		_inARowSting->frameRender(memDC, WINSIZE_X / 2 - _inARowSting->getFrameWidth() / 2, WINSIZE_Y / 2 - _inARowSting->getFrameHeight() / 2);
		break;
	case STATE::SWINGCIRCLE:
		_swingCircle->frameRender(memDC, WINSIZE_X / 2 - _swingCircle->getFrameWidth() / 2, WINSIZE_Y / 2 - _swingCircle->getFrameHeight() / 2);
		break;
	case STATE::SKILLCLIMAX:
		_skill->frameRender(memDC, WINSIZE_X / 2 - _skill->getFrameWidth() / 2, WINSIZE_Y / 2 - _skill->getFrameHeight() / 2);
		if (_count > 100 && _count < 300)
		{
			_skill1->alphaRender(memDC, WINSIZE_X / 2 - _skill1->getWidth() / 2, WINSIZE_Y / 2 - _skill1->getWidth() / 2, _count < 200 ? 55 + _count : 255);
		}
		if(_count > 200 && _count < 300)
		{
			_skill2->render(memDC, 
			_count <= 250 ? WINSIZE_X - (WINSIZE_X / 2 + _skill2->getWidth() / 2) * (_count - 200) / 50 : WINSIZE_X / 2 - _skill2->getWidth() / 2, WINSIZE_Y / 2 - _skill2->getWidth() / 2);
		}
		if(_count > 300 && _count < 400)
		{
			_skill3->render(memDC);
		}
		break;
	case STATE::VICTORY:
		_victory->frameRender(memDC, WINSIZE_X / 2 - _victory->getFrameWidth() / 2, WINSIZE_Y / 2 - _victory->getFrameHeight() / 2);
		break;
	case STATE::DEFEAT:
		_defeat->frameRender(memDC, WINSIZE_X / 2 - _defeat->getFrameWidth() / 2, WINSIZE_Y / 2 - _defeat->getFrameHeight() / 2);
		break;
	}
	
	for(int i = 0; i < 9; i++)
	{
		Rectangle(memDC, _rc[i].left, _rc[i].top, _rc[i].right, _rc[i].bottom);
	}
	char str[128];
	wsprintf(str, "대기");
	SetTextAlign(memDC, TA_CENTER);
	TextOut(memDC, 50, _rc[0].bottom - 25, str, lstrlen(str));
	wsprintf(str, "이동");
	TextOut(memDC, 50, _rc[1].bottom - 25, str, lstrlen(str));
	wsprintf(str, "찌르기");
	TextOut(memDC, 50, _rc[2].bottom - 25, str, lstrlen(str));
	wsprintf(str, "대각선 찌르기");
	TextOut(memDC, 50, _rc[3].bottom - 25, str, lstrlen(str));
	wsprintf(str, "연속 찌르기");
	TextOut(memDC, 50, _rc[4].bottom - 25, str, lstrlen(str));
	wsprintf(str, "원돌리기");
	TextOut(memDC, 50, _rc[5].bottom - 25, str, lstrlen(str));
	wsprintf(str, "승리포즈");
	TextOut(memDC, 50, _rc[6].bottom - 25, str, lstrlen(str));
	wsprintf(str, "스킬");
	TextOut(memDC, 50, _rc[7].bottom - 25, str, lstrlen(str));
	wsprintf(str, "패배");
	TextOut(memDC, 50, _rc[8].bottom - 25, str, lstrlen(str));
	}
	else
	{
		DrawRectMake(memDC, RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 100, 50));
		char str[128];
		wsprintf(str, "Start");
		SetTextAlign(memDC, TA_CENTER);
		TextOut(memDC, WINSIZE_X / 2, WINSIZE_Y / 2, str, lstrlen(str));
	}
	// ========================================================
	this->getDoubleBuffer()->render(hdc, 0, 0);
}
