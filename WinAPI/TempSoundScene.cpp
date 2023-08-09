#include "stdafx.h"
#include "TempSoundScene.h"

HRESULT TempSoundScene::init(void)
{
	TEMPSOUNDMANAGER->addMp3FileWithKey("찬란", "Resources/Sounds/창세기전-회상.mp3");
	return S_OK;
}

void TempSoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		TEMPSOUNDMANAGER->playSoundWithKey("찬란");
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sounds/sound.wav");
	}
}
