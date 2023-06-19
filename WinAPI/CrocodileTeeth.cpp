#include "stdafx.h"
#include "CrocodileTeeth.h"

HRESULT CrocodileTeeth::init(void)
{
	GameNode::init();
	for (int i = 0; i < 16; i++)
	{
		teeth[i] = new CT_Teeth;
		if(i < 8)
		{
			teeth[i]->init({100 + 50 * i, 600});
		}
		else
		{
			teeth[i]->init({100 + 50 * (i % 8), 400});
		}
	}
	prize = RND->getInt(8);
	gameOver = false;
	return S_OK;
}

void CrocodileTeeth::update(void)
{
	GameNode::update();
	if(gameOver == false)
	{
		if(KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 8; i++)
			{
				teeth[i]->update(_ptMouse);
				if (teeth[i]->getIsPressDown() && i == prize)
				{
					gameOver = true;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < 16; i++)
		{
			teeth[i]->update();
		}
	}
}

void CrocodileTeeth::release(void)
{
	GameNode::release();
	for (int i = 0; i < 8; i++)
	{
		SAFE_DELETE(teeth[i]);
	}
}

void CrocodileTeeth::render(HDC hdc)
{
	for (int i = 0; i < 16; i++)
	{
		teeth[i]->render(hdc);
	}
}
