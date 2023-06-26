#include "stdafx.h"
#include "SG_Tile.h"

HRESULT SG_Tile::init(void)
{
	return S_OK;
}

void SG_Tile::update(void)
{
}

void SG_Tile::release(void)
{
}

void SG_Tile::render(HDC hdc)
{
	_image->render(hdc, WINSIZE_X / 2 + WINSIZE_X / 6 * (_position % 3), WINSIZE_Y / 4 + WINSIZE_Y / 6 * (_position / 3), WINSIZE_X / 6 * (_index % 3), WINSIZE_Y / 6 * (_index / 3), WINSIZE_X / 6, WINSIZE_Y / 6);
}
