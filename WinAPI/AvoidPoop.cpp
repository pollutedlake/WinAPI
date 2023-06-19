#include "stdafx.h"
#include "AvoidPoop.h"
/*
- �ָ� ���� ����

�� �𸮾� 1��_�� �׸���_�����
�� ���� ���� 9��
�� ���� ���� �����ؼ�

���� 1. �����ϱ�
- ���� ��ư�� �����鼭 ���� ����
- ������ ���۵ǰ� �÷��̾ ���������� ��ƾ �ð��� ȭ���� ����Ѵ�.

- �ʼ� : ����� + �ٽ��ϱ�

- �÷��̾�� ��� ������� �¿� ����� �ٸ��� ����
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
