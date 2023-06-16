#include "Stdafx.h"
#include "ClayShooting.h"

/*
���� 2. Ŭ���� ���

- ��/�쿡�� �������� �����ϴ� Ÿ���� ���콺�� �����Ѵ�.

- Ÿ���� �����ϸ� ���� ȹ��
�� ���ŵ� Ÿ���� �� �ڸ����� �ٷ� ��������.

- �����ϴ� Ÿ���� ������ ������ ���� ó��

�� �簢�� : 50��, �� : -100��, �ٰ��� 100��

�� ���� �ð��� 60�� �����ϰ� / �ð��� �� �ǰų� �� ������ 5õ���� �Ǹ� ���� ����

Ÿ�� ����. API ������ ��ũ

- ����ȭ�� ���� ���ΰ��� Ŭ������ ��������� Ű �Ŵ����� ���� ��Ʈ�� �����̴� ��Ʈ����

- ���н� : ���� 5��
*/

HRESULT ClayShooting::init(void)
{
	GameNode::init();
	score = 0;
	deltaTime = 0;
	nextClayTime = 20;
	gameTime = 600;
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
	GameNode::update();
	deltaTime++;
	if (nextClayTime < deltaTime)
	{
		deltaTime = 0;
		nextClayTime = RND->getFromIntTo(10, 20);
		int startPosX = (RND->getFromIntTo(0, 1)) * 800;
		float angle;
		angle = RND->getFromFloatTo(20.0f, 70.0f);
		angle = (startPosX == 0) ? -angle : (-180 + angle);
		POINT startDir;
		startDir.x = 40 * cos(angle / 180 * PI);
		startDir.y = (WINSIZE_X / 2) / startDir.x;
		startDir.y = -abs(startDir.y);
		clays.push_back(new Clay(RND->getFromIntTo(0, 1), {startPosX, RND->getFromIntTo(200, 400)}, startDir, FALSE));
	}
	for (auto it = clays.begin(); it != clays.end();)
	{
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

			break;
		}
	}
	char str[128];
	wsprintf(str, "Your Score : %d", score);
	SetTextAlign(hdc, TA_CENTER);
	TextOut(hdc, WINSIZE_X / 2, 700, str, lstrlen(str));
}

void ClayShooting::Shoot(POINT _pt)
{
	for (auto it = clays.begin(); it != clays.end(); ++it)
	{
		if ((*it)->getIsHit())
		{
			continue;
		}
		switch ((*it)->getType())
		{
			case 0:
				if ((*it)->getPosition().x - 25 < _pt.x && (*it)->getPosition().x + 25 > _pt.x)
				{
					if ((*it)->getPosition().y - 25 < _pt.y && (*it)->getPosition().y + 25 > _pt.y)
					{
						(*it)->setIsHit(TRUE);
						score += 50;
					}
				}
			break;
			case 1:
				if ((pow(_pt.x - (*it)->getPosition().x, 2) + pow(_pt.y - (*it)->getPosition().y, 2)) < 2500)
				{
					(*it)->setIsHit(TRUE);
					score -= 100;
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
		Shoot(pt);
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
	case WM_DESTROY:                // �Ҹ���
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}