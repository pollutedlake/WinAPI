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
		INIDATA->addData("���", "������", "10");
		INIDATA->addData("�ο�", "�ø��", "10");
		INIDATA->addData("����", "�ι���", "10");
		INIDATA->addData("ȣ��", "����", "10");

		INIDATA->iniSave("100��");
	}

	if (KEYMANAGER->isOnceKeyDown('0'))
	{
		int test = INIDATA->loadDataInteger("100��", "�뼮", "������");
		printf("�뼮 : %d \n", test);
	}
}

void INIDataScene::render(void)
{
}
