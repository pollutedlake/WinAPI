#include "stdafx.h"
#include "Mole.h"

Mole::Mole()
{
	active = FALSE;
	height = 0;
	waitTime = RND->getFromIntTo(0, 40);
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
			height -= 5;
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
				waitTime = RND->getFromIntTo(0, 40);
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
}

BOOL Mole::checkHit(POINT pt, int i)
{
	if(active == TRUE)
	{
		if (pt.x > 100 + 250 * (i % 3) && pt.x < 200 + 250 * (i % 3))
		{
			if (pt.y > 175 + 150 * (i / 3) - height && pt.y < 175 + 150 * (i / 3))
			{
				active = FALSE;
				return TRUE;
			}
		}
	}
	return FALSE;
}