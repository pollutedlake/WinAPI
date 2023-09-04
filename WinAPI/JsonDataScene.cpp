#include "Stdafx.h"
#include "JsonDataScene.h"
#pragma warning(disable : 4996)

HRESULT JsonDataScene::init(void)
{
    _questSample = new QuestSample;
    _questSample->init();
    return S_OK;
}

void JsonDataScene::release(void)
{
    
}

void JsonDataScene::update(void)
{
}

void JsonDataScene::render(void)
{
    questPopUp();
}

void JsonDataScene::questPopUp()
{
    char str[256];
    queue<Quest*>* temp = _questSample->getQuest();
    Quest* node = temp->front();

    sprintf(str, "%s", node->getName().c_str());
    TextOut(getMemDC(), 200, 150, str, strlen(str));

    sprintf(str, "개요 : %s", node->getDescription().c_str());
    TextOut(getMemDC(), 200, 170, str, strlen(str));

    sprintf(str, "몬스터 이름 : %s", node->getMonsterName().c_str());
    TextOut(getMemDC(), 200, 190, str, strlen(str));

    sprintf(str, "처치해야 할 몬스터 : %d 마리", node->getMonster());
    TextOut(getMemDC(), 200, 210, str, strlen(str));

    sprintf(str, "처치해야 할 몬스터 : %d 마리", node->getMonster());
    TextOut(getMemDC(), 200, 230, str, strlen(str));

    sprintf(str, "퀘스트 체크 : %s", node->getQuestCheck().c_str());
    TextOut(getMemDC(), 200, 250, str, strlen(str));

    sprintf(str, "보상 경험치 : %d Exp", node->getExp());
    TextOut(getMemDC(), 200, 270, str, strlen(str));

    sprintf(str, "퀘스트 보상 아이템 : %s", node->getItem().c_str());
    TextOut(getMemDC(), 200, 290, str, strlen(str));

    sprintf(str, "퀘스트 보상 골드 : %d Gold", node->getGold());
    TextOut(getMemDC(), 200, 310, str, strlen(str));
}

void JsonDataScene::currentQuest()
{
}
