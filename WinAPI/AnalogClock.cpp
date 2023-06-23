#include "stdafx.h"
#include "AnalogClock.h"

/*
과제 1. 아날로그 시계

- 초침 / 분침 / 시침

- 오늘 사용한 SYSTEMTIME을 이용해서 만든다.

- 필수 : 시간 표시
*/

HRESULT AnalogClock::init(void)
{
    GameNode::init();
    return S_OK;
}

void AnalogClock::update(void)
{
    GameNode::update();
    GetLocalTime(&_st);
}

void AnalogClock::render(HDC hdc)
{
	HDC memDC = this->getDoubleBuffer()->getMemDC();
	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, WHITENESS);

    char timeStr[128];
    wsprintf(timeStr, "%d시 %d분 %d초", _st.wHour, _st.wMinute, _st.wSecond);
    SetTextAlign(memDC, TA_LEFT);
    TextOut(memDC, 0, 0, timeStr, lstrlen(timeStr));
    EllipseMakeCenter(memDC, WINSIZE_X / 2, WINSIZE_Y / 2, 300, 300);
    SetTextAlign(memDC, TA_CENTER);
    for (int i = 0; i < 12; i++)
    {
        wsprintf(timeStr, "%d", i + 1);
        TextOut(memDC, WINSIZE_X / 2 + 140 * cos((9.0f + i + 1) / 6.0f * PI), WINSIZE_Y / 2 + 140 * sin((float)(9.0f + i + 1) / 6.0f * PI), timeStr, lstrlen(timeStr));
    }
    HPEN seoncdPen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
    HPEN currentPen = (HPEN)SelectObject(memDC, seoncdPen);
    LineMake(memDC, WINSIZE_X / 2, WINSIZE_Y / 2, WINSIZE_X / 2 + 125 * cos((45.0f + _st.wSecond) / 30.0f * PI), WINSIZE_Y / 2 + 125 * sin((45.0f + _st.wSecond) / 30.0f * PI));
    HPEN minutePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
    SelectObject(memDC, minutePen);
    LineMake(memDC, WINSIZE_X / 2, WINSIZE_Y / 2, WINSIZE_X / 2 + 150 * cos((45.0f + _st.wMinute) / 30.0f * PI), WINSIZE_Y / 2 + 150 * sin((45.0f + _st.wMinute) / 30.0f * PI));
    HPEN hourPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
    SelectObject(memDC, hourPen);
    LineMake(memDC, WINSIZE_X / 2, WINSIZE_Y / 2, WINSIZE_X / 2 + 100 * cos((270.0f + _st.wHour * 30.0f + _st.wMinute * 0.5f) / 180.0f * PI), WINSIZE_Y / 2 + 100 * sin((270.0f + _st.wHour * 30.0f + _st.wMinute * 0.5f) / 6.0f * PI));
    SelectObject(memDC, currentPen);
    DeleteObject(seoncdPen);
    DeleteObject(minutePen);
    DeleteObject(hourPen);

	this->getDoubleBuffer()->render(hdc, 0, 0);
}

void AnalogClock::release()
{
    GameNode::release();
}
