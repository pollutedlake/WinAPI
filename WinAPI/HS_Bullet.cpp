#include "stdafx.h"
#include "HS_Bullet.h"

HRESULT HS_Bullet::init(void)
{
	return S_OK;
}

HRESULT HS_Bullet::init(int _x, int _y, int _whoShoot, BulletType _type, float _angle)
{
	position.x = _x;
	position.y = _y;
	whoShoot = _whoShoot;
	type = _type;
	count = _angle;
	if (_type == NORMAL)
	{
		width = BULLETWIDTH;
		height = BULLETHEIGHT;
		speed = 14;
	}
	else if (_type == SHOCKWAVE)
	{
		width = BULLETWIDTH / 2;
		height = BULLETHEIGHT / 2;
		speed = 7;
	}
	else if (_type == CHARGESHOT)
	{
		width = WINSIZE_X;
		height = BULLETHEIGHT;
		position.x = _x - BULLETWIDTH / 2 + width / 2;
	}
	else if (_type == SPRINKLER)
	{
		width = BULLETWIDTH;
		height = BULLETHEIGHT;
		speed = 7;
	}
	else if (_type == SPRINKLERCHILD)
	{
		width = BULLETWIDTH;
		height = BULLETHEIGHT;
		speed = 14;
	}
	return S_OK;
}

void HS_Bullet::update(void)
{
	if (whoShoot == PLAYER1)
	{
		if(type == NORMAL)
		{
			position.x += speed;
			if (position.x > WINSIZE_X + BULLETWIDTH)
			{
				active = false;
			}
		}
		else if (type == SHOCKWAVE)
		{
			position.x += speed;
			if (position.x > WINSIZE_X * 3 / 4)
			{
				position.x = WINSIZE_X * 3 / 4;
				width += 5;
				height += 5;
				if (width > WINSIZE_X / 2)
				{
					active = false;
				}
			}
		}
		else if (type == CHARGESHOT)
		{
			count += 20;
			if (count > 2000)
			{
				count = 0;
				active = false;
			}
		}
	}
	else
	{
		if(type == NORMAL || type == SPRINKLERCHILD)
		{
			position.x -= cos(count / (float)180 * PI) * speed;
			position.y += sin(count / (float)180 * PI) * speed;
			if (position.x < -BULLETWIDTH / 2)
			{
				active = false;
			}
			if (position.x > WINSIZE_X + BULLETWIDTH / 2)
			{
				active = false;
			}
			if (position.y < -BULLETHEIGHT / 2)
			{
				active = false;
			}
			if (position.x > WINSIZE_Y + BULLETHEIGHT / 2)
			{
				active = false;
			}
		}
		else if (SPRINKLER)
		{
			position.x -= speed;
			if (position.x < -BULLETWIDTH / 2)
			{
				active = false;
			}
			count += 10;
		}
	}
}

void HS_Bullet::render(HDC hdc)
{
	EllipseMakeCenter(hdc, position.x, position.y, width, height);
}

void HS_Bullet::release()
{
}
