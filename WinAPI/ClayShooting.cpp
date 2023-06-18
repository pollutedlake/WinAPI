#include "Stdafx.h"
#include "ClayShooting.h"

/*
과제 2. 클레이 사격

- 좌/우에서 무작위로 출현하는 타겟을 마우스로 제거한다.

- 타겟을 제거하면 점수 획득
ㄴ 제거된 타겟은 그 자리에서 바로 떨어진다.

- 등장하는 타겟의 종류는 무작위 도형 처리

ㄴ 사각형 : 50점, 원 : -100점, 다각형 100점

ㄴ 게임 시간은 60초 한정하고 / 시간이 다 되거나 내 점수가 5천점이 되면 게임 종료

타임 어택. API 프레임 워크

- 가상화를 통해 메인게임 클래스가 만들어지고 키 매니저를 통해 렉트를 움직이는 파트까지

- 실패시 : 깜지 5번
*/

POINT _ptMouse;

HRESULT ClayShooting::init(void)
{
	GameNode::init();
	score = 0;
	deltaTime = 0;
	nextClayTime = 20;
	gameTime = 620;
	playGame = TRUE;
	return S_OK;
}

void ClayShooting::release(void)
{
	GameNode::release();
	for (auto it = clays.begin(); it != clays.end(); ++it)
	{
		delete (*it);
	}
	clays.clear();
}

void ClayShooting::update(void)
{
	gameTime--;
	if (!gameTime || score > 5000)
	{
		playGame = FALSE;
	}
	if (playGame == TRUE)
	{
		nextClayTime--;
		if (!nextClayTime)
		{
			nextClayTime = RND->getFromIntTo(3, 6);
			int startPosX = (RND->getFromIntTo(0, 1)) * 800;
			float angle;
			angle = RND->getFromFloatTo(20.0f, 70.0f);
			angle = (startPosX == 0) ? -angle : (-180 + angle);
			POINT startDir;
			startDir.x = 40 * cos(angle / 180 * PI);
			startDir.y = (WINSIZE_X / 2) / startDir.x;
			startDir.y = -abs(startDir.y);
			clays.push_back(new Clay(RND->getFromIntTo(0, 2), { startPosX, RND->getFromIntTo(200, 400) }, startDir, FALSE));
		}
	}
	for (auto it = clays.begin(); it != clays.end();)
	{
		if ((*it)->getType() == 2)
		{
			if ((*it)->getVertexes()[0].y > 600)
			{
				delete (*it);
				it = clays.erase(it);
				continue;
			}
		}
		if ((*it)->getPosition().y > 575)
		{
			delete (*it);
			it = clays.erase(it);
			continue;
		}
		if ((*it)->getPosition().x > 825 || (*it)->getPosition().x < -25)
		{
			delete (*it);
			it = clays.erase(it);
			continue;
		}
		(*it)->move();
		(*it)->setDir({ (*it)->getDir().x, (*it)->getDir().y + 1 });
		++it;
	}
	GameNode::update();
}

void ClayShooting::render(HDC hdc)
{
	MoveToEx(hdc, 0, 600, NULL);
	LineTo(hdc, 800, 600);
	for (auto it = clays.begin(); it != clays.end(); ++it)
	{
		switch ((*it)->getType())
		{
			case 0:
				DrawRectMake(hdc, RectMakeCenter((*it)->getPosition().x, (*it)->getPosition().y, 50, 50));
			break;
			case 1:
				EllipseMakeCenter(hdc, (*it)->getPosition().x, (*it)->getPosition().y, 50, 50);
			break;
			case 2:
				Polygon(hdc, (*it)->getVertexes(), (*it)->getVertexN());
			break;
		}
	}
	char str[128];
	wsprintf(str, "Your Score : %d", score);
	SetTextAlign(hdc, TA_CENTER);
	TextOut(hdc, WINSIZE_X / 2, 700, str, lstrlen(str));
	if (playGame == TRUE)
	{
		if (gameTime <= 600 && gameTime > 0)
		{
			wsprintf(str, "Time : %d", gameTime / 10);
		}
		else
		{
			wsprintf(str, "Time : 0");
		}
		TextOut(hdc, WINSIZE_X / 2, 650, str, lstrlen(str));
	}
	else
	{
		if (score > 5000)
		{
			wsprintf(str, "YOU WIN");

		}
		else
		{
			wsprintf(str, "YOU LOSE");

		}
		TextOut(hdc, WINSIZE_X / 2, 750, str, lstrlen(str));

	}
}

void ClayShooting::Shoot(POINT _pt)
{
	for (auto it = clays.begin(); it != clays.end(); ++it)
	{
		if ((*it)->getIsHit())
		{
			continue;
		}
		if ((*it)->isHitted(_pt))
		{
			switch ((*it)->getType())
			{
			case 0:
				score += 50;
				break;
			case 1:
				score -= 100;
				break;
			case 2:
				score += 100;
				break;
			}
			break;
		}
	}
}

LRESULT ClayShooting::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
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
		if (playGame == TRUE)
		{
			Shoot(pt);
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
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