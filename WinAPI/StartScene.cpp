#include "Stdafx.h"
#include "StartScene.h"

HRESULT StartScene::init(void)
{
    IMAGEMANAGER->addImage(" 시작 화면 ", "Resources/Images/BackGround/StartBG.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addImage(" 텍스트 알파 ", "Resources/Images/Object/StartText.bmp", 1000, 100, true, RGB(255, 0, 255));

    _alpha = _bgAlpha = 0;
    return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
    _alpha -= 3.0f;
    if (_alpha <= 0)_alpha = 255;
    _bgAlpha += 0.5f;
    if (_bgAlpha >= 255)_bgAlpha = 255;
}

void StartScene::render(void)
{
    IMAGEMANAGER->render(" 시작 화면 ", getMemDC());
    IMAGEMANAGER->alphaRender(" 시작 화면 ", getMemDC(), 0, 0, _bgAlpha);
    if (_bgAlpha >= 160)
    {
        IMAGEMANAGER->alphaRender(" 텍스트 알파 ", getMemDC(), 130, WINSIZE_Y / 2 + 200, _alpha);
    }
}