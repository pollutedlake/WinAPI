#include "Stdafx.h"
#include "MainGame.h"
#define _USE_MATH_DEFINES
#include<math.h>

HRESULT MainGame::init(void)
{
	GameNode::init(true);
#if MAIN == CLASS
	IMAGEMANAGER->addImage("DeadSpace", "Resources/Images/BackGround/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);

	_alphaA = 255;
#elif MAIN == ASSIGNMENT
	_assignment = new CTW_Scene;
	_assignment->init();
#endif
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
#if MAIN == CLASS
#elif MAIN == ASSIGNMENT
	_assignment->release();
	SAFE_DELETE(_assignment);
#endif
}

void MainGame::update(void)
{
	GameNode::update();
#if MAIN == CLASS
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (MessageBox(_hWnd, "������ �����Ͻðڽ��ϱ�?", "����Ȯ��", MB_OKCANCEL) == IDOK)
		{
			PostQuitMessage(0);
		}
	}
#elif MAIN == ASSIGNMENT
	_assignment ->update();
#endif	

}

void MainGame::render(void)
{
	// PatBlt(): �簢�� �ȿ� ������ �귯���� ä��� �Լ�
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// ========================================================
#if MAIN == CLASS
	IMAGEMANAGER->findImage("DeadSpace")->alphaRender(getMemDC(), _alphaA);
#elif MAIN == ASSIGNMENT
	_assignment->render();
#endif
	// ========================================================
	this->getBackBuffer()->render(getHDC());
}

/*
����1. ĳ���� �����

�̹��� �ʼ� : ���, ��, ĳ����(���,�̵�,����,���� ����ִ� ���)

�⺻������ ���� �������� ���� ���� �𼭸��� ������ �� �߰��� �������� õõ�� �������� �������

ĳ���Ͱ� ���� ��� �ִ� ���¿��� �� / �Ǵ� �Ʒ�����Ű�� ������ �ö󰡰ų� �������� �־���Ѵ�.

���� ĳ���Ͱ� �� ���� �ö� ���� �ٽ� �Ʒ��� �����ϸ� ĳ���ʹ� ���鿡 �����Ҽ��־���Ѵ�

ĳ���� ���� ������ ������ �ְ� ĳ���ʹ� ���� �ؿ��� ������ ���� �� �ö� �� ���ִ�

ĳ���ʹ� ������ �ö� ���¿��� �������� �ٽ� ������ �� ������ ok

����2. �̴ϸ� ����

�÷��̾��� �������� �̴ϸʿ��� �״�� Ȯ���ؾ� �Ѵ�
�� �����ӱ��� �����ϰ�
*/