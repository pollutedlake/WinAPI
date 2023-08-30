#include "stdafx.h"
#include "INIDataScene.h"

HRESULT INIDataScene::init(void)
{
	return S_OK;
}

void INIDataScene::release(void)
{
}

void INIDataScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		INIDATA->addData("용식", "무서움", "10");
		INIDATA->addData("민우", "시리어스", "10");
		INIDATA->addData("기태", "민방위", "10");
		INIDATA->addData("호영", "군대", "10");

		INIDATA->iniSave("100팀");
	}

	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		int test = INIDATA->loadDataInteger("100팀", "용석", "무서움");
		printf("용석 : %d \n", test);
	}
}

void INIDataScene::render(void)
{
}
