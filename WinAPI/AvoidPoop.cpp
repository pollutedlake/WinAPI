#include "stdafx.h"
#include "AvoidPoop.h"
/*
- 주말 과제 제출

ㄴ 언리얼 1기_얼굴 그리기_김기태
ㄴ 내일 오전 9시
ㄴ 오늘 과제 포함해서

과제 1. 똥피하기
- 시작 버튼을 누르면서 게임 시작
- 게임이 시작되고 플레이어가 죽을때까지 버틴 시간을 화면을 출력한다.

- 필수 : 재시작 + 다시하기

- 플레이어는 사람 모양으로 좌우 모양이 다르게 구현
*/
#define STARTSCENE      0
#define GAMESCENE       1
#define ENDSCENE        2

HRESULT AvoidPoop::init(void)
{
    GameNode::init();
    player = new AP_Player();
    player->init();
    deltaTime = 0;
    dropTime = RND->getFromIntTo(500, 1000);
    scene = STARTSCENE;
    score = 0;
    scoreTime = 0;
    return S_OK;
}

void AvoidPoop::update(void)
{
    GameNode::update();
    switch(scene)
    {
    case GAMESCENE:
        player->update();
        for (auto it = poops.begin(); it != poops.end();)
        {
            if (!(*it)->getIsActive())
            {
                (*it)->release();
                SAFE_DELETE((*it));
                it = poops.erase(it);
                continue;
            }
            (*it)->update();
            POINT playerPos = player->getPosition();
            RECT playerRect = RectMakeCenter(playerPos.x, playerPos.y - 62, 50, 125);
            POINT poopPos = (*it)->getPosition();
            RECT poopRect = RectMakeCenter(poopPos.x, poopPos.y, 20, 20);
            if (IntersectRect(&playerRect, &playerRect, &poopRect))
            {
                player->setDie(true);
            }
            ++it;
        }
        deltaTime += 50;
        scoreTime += 50;
        if (scoreTime > 1000)
        {
            scoreTime = 0;
            score++;
        }
        if (dropTime < deltaTime)
        {
            deltaTime = 0;
            dropTime = RND->getFromIntTo(1000, 2000);
            AP_Poop* poop = new AP_Poop();
            poop->init();
            poops.push_back(poop);
        }
        if (KEYMANAGER->isOnceKeyDown(VK_F1))
        {
            scene = ENDSCENE;
        }
        if (player->getDie())
        {
            scene = ENDSCENE;
        }
    break;
    case STARTSCENE:
        if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
        {
            if (PtInRect(&RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 200, 100), _ptMouse))
            {
                scene = GAMESCENE;
            }
        }
        break;
    case ENDSCENE:
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (PtInRect(&RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 - 200, 200, 100), _ptMouse) && !player->getDie())
			{
				scene = GAMESCENE;
			}
			else if (PtInRect(&RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 200, 100), _ptMouse))
			{
                release();
                init();
				scene = GAMESCENE;
			}
		}
        break;
    }
}

void AvoidPoop::release(void)
{
    GameNode::release();
    player->release();
    SAFE_DELETE(player);
    for (auto it = poops.begin(); it != poops.end();)
    {
        (*it)->release();
        SAFE_DELETE((*it));
        it = poops.erase(it);
    }
}

void AvoidPoop::render(HDC hdc)
{
    char str[128];
    switch (scene)
    {
    case GAMESCENE:
        wsprintf(str, TEXT("score : %d"), score);
        TextOut(hdc, 0, 0, str, lstrlen(str));
        player->render(hdc);
        for (auto it = poops.begin(); it != poops.end(); ++it)
        {
            (*it)->render(hdc);
        }
    break;
    case STARTSCENE:
        wsprintf(str, TEXT("START"));
        SetTextAlign(hdc, TA_CENTER);
        DrawRectMake(hdc, RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 200, 100));
		TextOut(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, str, lstrlen(str));
    break;
    case ENDSCENE:
		wsprintf(str, TEXT("RESTART"));
		SetTextAlign(hdc, TA_CENTER);
		DrawRectMake(hdc, RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2, 200, 100));
		TextOut(hdc, WINSIZE_X / 2, WINSIZE_Y / 2, str, lstrlen(str));
        if(!player->getDie())
        {
            wsprintf(str, TEXT("RESUME"));
		    DrawRectMake(hdc, RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 - 200, 200, 100));
		    TextOut(hdc, WINSIZE_X / 2, WINSIZE_Y / 2 - 200, str, lstrlen(str));
        }
		break;
    }
}
