#include "Stdafx.h"
#include "QuestSample.h"
//#include "Quest.h"

void QuestSample::init(void)
{
	questSetup();
}

void QuestSample::questSetup(Quest* pQuest)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("Quest.json");
	for (auto it = root["Quest"].begin(); it != root["Quest"].end(); it++)
	{
		if ((*it).isObject())
		{
			Quest* qQuest = new Quest;
			qQuest->init
			(
				(*it)["_name"].asString(),
				(*it)["_gold"].asInt(),
				(*it)["_exp"].asInt(),
				(*it)["_description"].asString(),
				(*it)["_item"].asString(),
				(*it)["_monster"].asInt(),
				(*it)["_questCheck"].asString(),
				(*it)["_questName"].asString(),
				(*it)["_questStage"].asString()
			);
			_quest.push(qQuest);
		}
	}

	/*
	asString
	ㄴ 변수가 NULL이면 별도의 예외 없이 NULL 변환

	toString
	ㄴ 변수가 NULL이면 예외
	*/
}
