#include "stdafx.h"
#include "Card.h"

BOOL Card::clickCard(POINT _pt)
{
	if ((_pt.x > centerX - width / 2) && (_pt.x < centerX + width / 2))
	{
		if ((_pt.y < centerY + height / 2) && (_pt.y > centerY - height / 2))
		{
			if (open == FALSE)
			{
				open = TRUE;
				return TRUE;
			}
		}
	}
	return FALSE;
}

Card::Card(int _centerX, int _centerY, int _width, int _height, HBRUSH _cardColor)
{
	centerX = _centerX;
	centerY = _centerY;
	width = _width;
	height = _height;
	cardColor = _cardColor;
}

Card::~Card()
{
	
}

void Card::setRect(RECT _rt)
{
	width = _rt.right - _rt.left;
	height = _rt.bottom - _rt.top;
	centerX = _rt.left + width / 2;
	centerY = _rt.top + height / 2;
}
