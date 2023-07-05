#include "stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("배경루프", "Resources/Images/BackGround/Repeating_BackGround.bmp", WINSIZE_X, WINSIZE_Y);
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
	IMAGEMANAGER->loopRender("배경루프", getMemDC(), &RectMake(0, 0, WINSIZE_X, WINSIZE_Y), _bgSpeed, 0);

	// SetBkMode : 텍스트 버퍼등을 투명하게 한다.
	SetBkMode(getMemDC(), TRANSPARENT);

	// 기존 텍스트
	char str[128];
	wsprintf(str, "기존");
	TextOut(getMemDC(), 230, 350, str, strlen(str));

	// 새로운 방식
	HFONT font;
	HFONT oldFont;
	/*
	font = CreateFont
	(
		문자크기, 문자폭, 기울기(전체), 문자방향, 문자 굵기, 기울기(t / f), 밑줄(t / f), 취소선, 문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
	);
	*/
	font = CreateFont
	(
		70, 0, 0, 0, 600,
		0, 0, 1,
		HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림")
	);

	oldFont = (HFONT)SelectObject(getMemDC(), font);

	wsprintf(str, "새로운 폰트");
	TextOut(getMemDC(), 100, 400, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);
}
