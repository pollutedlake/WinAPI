#include "stdafx.h"
#include "Clay.h"

Clay::Clay(int _type, POINT _position, POINT _dir, BOOL _isHit)
{
	type = _type;
	position = _position;
	dir = _dir;
	isHit = _isHit;
	if (type == 2)
	{
		do
		{
			vertexN = RND->getFromIntTo(3, 8);
		} while (vertexN == 4);
		POINT vertex;
		for (int i = 0; i < vertexN; i++)
		{
			int r = RND->getFromIntTo(25, 50);
			float angle = RND->getFromIntTo(0, 360);
			vertex.x = position.x + r * cos(angle / 180 * PI);
			vertex.y = position.y + r * sin(angle / 180 * PI);
			vertexes[i] = vertex;
		}
		for (int i = 0; i < vertexN - 1; i++)
		{
			for (int j = i + 1; j < vertexN; j++)
			{
				if (vertexes[i].y < vertexes[j].y)
				{
					POINT temp = vertexes[i];
					vertexes[i] = vertexes[j];
					vertexes[j] = temp;
				}
				else if (vertexes[i].y == vertexes[j].y)
				{
					if (vertexes[i].x < vertexes[j].x)
					{
						POINT temp = vertexes[i];
						vertexes[i] = vertexes[j];
						vertexes[j] = temp;
					}
				}
			}
		}
		for (int i = 1; i < vertexN - 1; i++)
		{
			for (int j = i + 1; j < vertexN; j++)
			{
				double inclinationI = ((double)(vertexes[i].y - vertexes[0].y) / (double)(vertexes[i].x - vertexes[0].x));
				double inclinationJ = ((double)(vertexes[j].y - vertexes[0].y) / (double)(vertexes[j].x - vertexes[0].x));
				if (inclinationI > 0 && inclinationJ > 0)
				{
					if (inclinationI > inclinationJ)
					{
						POINT temp = vertexes[i];
						vertexes[i] = vertexes[j];
						vertexes[j] = temp;
					}
				}
				else if (inclinationI < 0 && inclinationJ > 0)
				{
					POINT temp = vertexes[i];
					vertexes[i] = vertexes[j];
					vertexes[j] = temp;
				}
				else if (inclinationI < 0 && inclinationJ < 0)
				{
					if (inclinationI > inclinationJ)
					{
						POINT temp = vertexes[i];
						vertexes[i] = vertexes[j];
						vertexes[j] = temp;
					}
				}
			}
		}
	}
}

Clay::~Clay()
{

}

void Clay::move()
{
	if (isHit)
	{
		if (type == 2)
		{
			for (int i = 0; i < vertexN; i++)
			{
				vertexes[i].y += 20;
			}
		}
		else
		{
			position.y += 20;
		}
	}
	else
	{
		if (type == 2)
		{
			for (int i = 0; i < vertexN; i++)
			{
				vertexes[i].x += dir.x;
				vertexes[i].y += dir.y;
			}
		}
		else
		{
			position.x += dir.x;
			position.y += dir.y;
		}
	}
}

BOOL Clay::isHitted(POINT pt)
{
	switch (type)
	{
	case 0:
		if ((position.x - 25 < pt.x) && (position.x + 25 > pt.x))
		{
			if ((position.y - 25 < pt.y) && (position.y + 25 > pt.y))
			{
				isHit = TRUE;
				return TRUE;
			}
		}
		break;
	case 1:
		if ((pow(pt.x - position.x, 2) + pow(pt.y - position.y, 2)) < 2500)
		{
			isHit = TRUE;
			return TRUE;
		}
		break;
	case 2:
		int crossN = 0;
		for (int i = 0; i < vertexN; i++)
		{
			int nextI = (i + 1) % vertexN;
			float crossX = (float)(pt.y - vertexes[i].y) * (float)(vertexes[i].x - vertexes[nextI].x) / (float)(vertexes[i].y - vertexes[nextI].y) + (float)vertexes[i].x;
			if (crossX > pt.x)
			{
				if (crossX > min(vertexes[i].x, vertexes[nextI].x) && crossX < max(vertexes[i].x, vertexes[nextI].x))
				{
					crossN++;
				}
			}
		}
		if (crossN % 2 == 1)
		{
			isHit = TRUE;
			return TRUE;
		}
		break;
	}
	return FALSE;
}