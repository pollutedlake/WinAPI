#include "stdafx.h"
#include "Example_Mole.h"

#define CENTER_X	WINSIZE_X / 2
#define CENTER_Y	WINSIZE_Y / 2

HRESULT Example_Mole::init(void)
{
	rc = RectMakeCenter(CENTER_X, CENTER_Y, 100, 100);
	return S_OK;
}

void Example_Mole::release(void)
{
}

void Example_Mole::update(void)
{
}

void Example_Mole::render(HDC hdc)
{
	DrawRectMake(hdc, rc);
}
