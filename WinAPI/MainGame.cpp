/*
과제1.카드 짝 맞추기

- 사이즈 : 5 x 4

- 카드 짝을 맞추면 맞춘 카드는 계속 오픈되어야 한다.

- 치트 필수
ㄴ 1. 전부 오픈 후 일정 시간 후 다시 감추기
ㄴ 2. 1쌍을 제외하고 나머지는 전부 오픈되고 유저가 1쌍을 맞추면서 종료

※ HBRUSH
*/

#include "Stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void)
{
	GameNode::init();
	HBRUSH hBrush = NULL;
	for (int i = 0; i < 20; i++)
	{
		if (i % 2 == 0)
		{
			hBrush = (HBRUSH)CreateSolidBrush(RGB(RND->getFromIntTo(0, 255), RND->getFromIntTo(0, 255), RND->getFromIntTo(0, 255)));
		}
		cards[i] = new Card(100 + 100 * (i % 4), 100 + 150 * (i / 4), 50, 75, hBrush);
	}
	for (int i = 0; i < 500; i++)
	{
		int dest = RND->getFromIntTo(0, 19);
		int sour = RND->getFromIntTo(0, 19);
		Card* temp = cards[dest];
		cards[dest] = cards[sour];
		cards[sour] = temp;
		RECT tempRect = cards[dest]->getRect();
		cards[dest]->setRect(cards[sour]->getRect());
		cards[sour]->setRect(tempRect);
	}
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	for (int i = 0; i < 20; i++)
	{
		DeleteObject(cards[i]->getCardColor());
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
					if (oldCardColor != cards[i]->getCardColor())
					{
						bCardPairCheck = TRUE;
					}
					else
					{
						openCards.push_back(selectCard[0]);
						openCards.push_back(selectCard[1]);
						count = 0;
					}
					pt.x = -1;
					pt.y = -1;
					break;
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
		if(count != 0)
		{
			selectCard[0]->reverseCard();
			selectCard[1]->reverseCard();
		}
		count = 0;
		for (int i = 0; i < 20; i++)
		{
			cards[i]->reverseCard();
		}
		for (auto it = openCards.begin(); it != openCards.end(); ++it)
		{
			(*it)->openCard();
		}
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
			SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		}
		DrawRectMake(hdc, cards[i]->getRect());
	}
	SelectObject(hdc, (HBRUSH)GetStockObject(BLACK_BRUSH));
}

void MainGame::cheat1()
{
	for (int i = 0; i < 20; i++)
	{
		cards[i]->openCard();
	}
	bCardPairCheck = TRUE;
}

void MainGame::cheat2()
{
	HBRUSH hBrush = NULL;
	for (int i = 0; i < 20; i++)
	{
		if (cards[i]->getOpen() == FALSE)
		{
			hBrush = cards[i]->getCardColor();
			break;
		}
	}
	for (int i = 0; i < 20; i++)
	{
		if (hBrush == cards[i]->getCardColor())
		{
			continue;
		}
		cards[i]->openCard();
	}
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_LBUTTONDOWN:
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		case VK_UP:
			cheat1();
			break;
		case VK_DOWN:
			cheat2();
			break;
		}
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_DESTROY:                // 소멸자
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}