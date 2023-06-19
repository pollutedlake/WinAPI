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
HRESULT AvoidPoop::init(void)
{
    GameNode::init();
    player = new AP_Player();
    player->init();
    deltaTime = 0;
    dropTime = RND->getFromIntTo(1000, 2000);
    isStart = false;
    return S_OK;
}

void AvoidPoop::update(void)
{
    GameNode::update();
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
        ++it;
    }
    deltaTime += 50;
    if (dropTime < deltaTime)
    {
        deltaTime = 0;
        dropTime = RND->getFromIntTo(1000, 2000);
        AP_Poop* poop = new AP_Poop();
        poop->init();
        poops.push_back(poop);
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
    player->render(hdc);
    for (auto it = poops.begin(); it != poops.end(); ++it)
    {
        (*it)->render(hdc);
    }
}
