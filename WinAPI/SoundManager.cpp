#include "Stdafx.h"
#include "SoundManager.h"

HRESULT SoundManager::init()
{
    System_Create(&_system);
    _system->init(totalSoundChannel, FMOD_INIT_NORMAL, 0);

    // ä�� �� ��ŭ �޸� ���� �� ���� ���� -> ä�μ��� ���� ���� ���� �����ִ� ���� ����.
    // �� 1 : 1
    
    _sound = new Sound*[totalSoundChannel];
    _channel = new Channel*[totalSoundChannel];

    // �޸� �ѹ� ��
    memset(_sound, 0, sizeof(Sound*) * (totalSoundChannel));
    memset(_channel, 0, sizeof(Channel*) * (totalSoundChannel));

    return S_OK;
}

void SoundManager::release(void)
{
    if (_channel != nullptr || _sound != nullptr)
    {
        for (int i = 0; i < totalSoundChannel; i++)
        {
            if (_channel != nullptr)
            {
                if(_channel[i]) _channel[i]->stop();
            }
            if (_sound != nullptr)
            {
                if (_sound[i] /* != nullptr*/) _sound[i]->release();
            }
        }
    }

    SAFE_DELETE_ARRAY(_channel);
    SAFE_DELETE_ARRAY(_sound);

    if (_system != nullptr)
    {
        _system->release();
        _system->close();
    }
}

void SoundManager::update(void)
{
    // _system->update() : ���� ����, ����� ���� ���带 ä�ο��� ���� �� �پ��� �۾��� �ڵ����� ���ش�.
    _system->update();
}

void SoundManager::render(void)
{
}

void SoundManager::addSound(string keyName, string soundName, bool background, bool loop)
{
    if (loop)
    {
        if (background)
        {
            _system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);
        }

        // �Ϲ� ���� (ȿ����)
        else
        {
            _system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);

            /*
            createStream vs createSound
            �� ���ڵ� ���� -> ���ο� �޸𸮸� ��� �����ϴ��� �ƴϳ��� ���̰� �����Ѵ�.

            1. ���� �̸�    2. ���带 ���� ���� FMOD �ɼ�   3. ���忡 ���� �������� �����ڿ��� �������ٰ�����? �ƴ���?(0 -> ����)
            4. ���� ������Ʈ ������ �ּ�
            */
        }
    }

    else
    {
        // FMOD_DEFAULT : Once
        _system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);
    }

    _mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));
}

void SoundManager::play(string keyName, float volume)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
            _channel[count]->setVolume(volume);
            break;
        }
    }
}

void SoundManager::stop(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->stop();
            break;
        }
    }
}

void SoundManager::pause(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->setPaused(true);
            break;

        }
    }
}

void SoundManager::resume(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->setPaused(false);
            break;
        }
    }
}

bool SoundManager::isPlaySound(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    bool isPlay;
    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->isPlaying(&isPlay);
            break;
        }
    }
    return isPlay;
}

bool SoundManager::isPauseSound(string keyName)
{
    arrSoundsIter iter = _mTotalSounds.begin();

    bool isPause;
    int count = 0;

    for (iter; iter != _mTotalSounds.end(); ++iter, count++)
    {
        if (keyName == iter->first)
        {
            _channel[count]->isPlaying(&isPause);
            break;
        }
    }
    return !isPause;
}

SoundManager::SoundManager() : _system(nullptr), _channel(nullptr), _sound(nullptr)
{
    
}