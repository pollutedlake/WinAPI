/*
����1.ī�� ¦ ���߱�

- ������ : 5 x 4

- ī�� ¦�� ���߸� ���� ī��� ��� ���µǾ�� �Ѵ�.

- ġƮ �ʼ�
�� 1. ���� ���� �� ���� �ð� �� �ٽ� ���߱�
�� 2. 1���� �����ϰ� �������� ���� ���µǰ� ������ 1���� ���߸鼭 ����

�� HBRUSH
*/

#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();
	for (int i = 0; i < 20; i++)
	{
		HBRUSH hBrush = NULL;
		if (i % 2 == 0)
		{
			hBrush = (HBRUSH)CreateSolidBrush(RGB(RND->getFromIntTo(0, 255), RND->getFromIntTo(0, 255), RND->getFromIntTo(0, 255)));
		}
		cards[i] = new Card(100 + 100 * (i % 4), 100 + 200 * (i / 4), 50, 100, hBrush);
	}
	for (int i = 0; i < 500; i++)
	{
		int dest = RND->getFromIntTo(0, 19);
		int sour = RND->getFromIntTo(0, 19);
		Card* temp = cards[dest];
		cards[dest] = cards[sour];
		cards[sour] = temp;
	}
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	for (int i = 0; i < 20; i++)
	{
		delete cards[i];
	}
}

void MainGame::update(void)
{
	GameNode::update();
	if (bCardPairCheck == FALSE)
	{
		for (int i = 0; i < 20; i++)
		{
			if (cards[i]->clickCard(pt))
			{
				selectCard[count] = cards[i];
				count++;
				if (count == 1)
				{
					oldCardColor = cards[i]->getCardColor();
				}
				else if (count == 2)
				{
					if (oldCardColor == cards[i]->getCardColor())
					{
						count = 0;
						bCardPairCheck = TRUE;
						break;
					}
				}
			}
		}
	}
	else
	{
		deltaTime++;
	}
	if (deltaTime > reverseTime)
	{
		deltaTime = 0;
		bCardPairCheck = FALSE;
		selectCard[0]->reverseCard();
		selectCard[1]->reverseCard();
	}
}

void MainGame::render(HDC hdc)
{
	for (int i = 0; i < 20; i++)
	{
		if (cards[i]->getOpen())
		{
			SelectObject(hdc, cards[i]->getCardColor());
		}
		else
		{
			SelectObject(hdc, (HBRUSH)GetStockObject(WHITE_BRUSH));
		}
		DrawRectMake(hdc, cards[i]->getRect());
	}
}
