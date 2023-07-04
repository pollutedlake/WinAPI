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
	//_assignment = new CTW_Scene;			// ĳ���� ��¤��, �̴ϸ� ����
	//_assignment = new RacingGame;			// ���̰̽���
	_assignment = new BlackHole;			// ��Ȧ
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
1. ��ȹ�� ����

2. ��ȹ�� �긴��

-����, ������

- ����
- ������Ʈ ��ǥ/�����ǵ�
- 00�帣�� 00������ ���۷������� ���� ����
- 0000�� ��̸� �������Ϸ� ��

- ���� �Ұ�
- ���Ӹ�, ���ӼҰ�, ����Ư¡
- �����ο�, ���� ����, ���� ���, ��� ��ų
- ���߰�ȹ(����)
- ���()

-���/ȸ��
- 00��� �ɷ� ȹ��
- ������, �����, ������ �κ�, �����н��� ����� ������ �ڷ�(����/��ũ/���� ��)
- ����/����� ������ �κ�

- �÷ο� ��Ʈ

- Ŭ���� ������

- ���� ����

- ���� ��
���־� ��Ʃ��� ���� ���伥���� �����������α׷�
15��~20��

����1. ��Ʈ������ PPT �ۼ�

- ��ǥ���� ���� ����

- �������ϰ� + ����ϰ�

���� 2. ��Ȧ

- �������� �����Ǵ� ������Ʈ ��ü

- �׸��� �ֺ� ������Ʈ�� ���Ƶ��̴� ��Ȧ�� �����
�� ��Ȧ�� ������ ���ؼ� ������ �� �ִ�.

- ������Ʈ�� �����Ǵ� ��ġ�� �˱� ���� ǥ�ø� �Ѵ�.
�� EX : �� / �̹��� / ũ��

- �ʼ� : STL -> vetor or list�� �ݵ�� �Ἥ ����
*/