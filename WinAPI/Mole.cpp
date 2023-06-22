#include "stdafx.h"
#include "Mole.h"

Mole::Mole()
{
	active = FALSE;
	height = 0;
	waitTime = RND->getFromIntTo(0, 150);
	isRed = 0;
	twinkleTime = 50;
	up = TRUE;
}

Mole::~Mole()
{

}

void Mole::update()
{
	if (active == FALSE)
	{
		if (height > 0)
		{
			height -= 1;
		}
		else
		{
			height = 0;
			up = TRUE;
		}
	}
	else
	{
		if (height == 75)
		{
			if(waitTime != 0)
			{
				waitTime--;
			}
			else
			{
				height -= 5;
				waitTime = RND->getFromIntTo(0, 150);
				up = FALSE;
			}
		}
		else if (height < 75 && height >= 0)
		{
			if (up == TRUE)
			{
				height += 5;
			}
			else
			{
				height -= 5;
				if (height < 0)
				{
					height = 0;
					active = FALSE;
				}
			}
		}
	}
	if (active == FALSE && up == FALSE)
	{
		twinkleTime -= 10;
		if (twinkleTime <= 0)
		{
			twinkleTime = 50;
			isRed = !isRed;
		}
	}
	else
	{
		isRed = 0;
	}
}

BOOL Mole::checkHit(POINT pt, int i)
{
	if(active == TRUE)
	{
		if (pt.x - 100 > 100 + 250 * (i % 3) && pt.x - 100 < 200 + 250 * (i % 3))
		{
			if (pt.y > 150 + 150 * (i / 3) - height && pt.y < 150 + 150 * (i / 3))
			{
				active = FALSE;
				up = FALSE;
				return TRUE;
			}
		}
	}
	return FALSE;
}