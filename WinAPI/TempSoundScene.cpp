#include "stdafx.h"
#include "TempSoundScene.h"

HRESULT TempSoundScene::init(void)
{
	TEMPSOUNDMANAGER->addMp3FileWithKey("����", "Resources/Sounds/â������-ȸ��.mp3");
	return S_OK;
}

void TempSoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		TEMPSOUNDMANAGER->playSoundWithKey("����");
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sounds/sound.wav");
	}
}
