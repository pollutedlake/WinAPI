#include "stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("������", "Resources/Images/BackGround/Repeating_BackGround.bmp", WINSIZE_X, WINSIZE_Y);
	return S_OK;
}

void SecondScene::release(void)
{

}

void SecondScene::update(void)
{
	_bgSpeed += 3;
}

void SecondScene::render(void)
{
	IMAGEMANAGER->loopRender("������", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);

	// SetBkMode : �ؽ�Ʈ ���۵��� �����ϰ� �Ѵ�.
	SetBkMode(getMemDC(), TRANSPARENT);

	// ���� �ؽ�Ʈ
	char str[128];
	wsprintf(str, "����");
	TextOut(getMemDC(), 230, 350, str, strlen(str));

	// ���ο� ���
	HFONT font;
	HFONT oldFont;
	/*
	font = CreateFont
	(
		����ũ��, ������, ����(��ü), ���ڹ���, ���� ����, ����(t / f), ����(t / f), ��Ҽ�, ���� ����, ��� ��Ȯ��, Ŭ���� ��Ȯ��, ����� ��, �ڰ�, ��Ʈ
	);
	*/
	font = CreateFont
	(
		70, 0, 0, 0, 600,
		0, 0, 1,
		HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�޸ձ���")
	);

	oldFont = (HFONT)SelectObject(getMemDC(), font);

	wsprintf(str, "���ο� ��Ʈ");
	TextOut(getMemDC(), 100, 400, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}
