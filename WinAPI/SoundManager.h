#pragma once
#include "SingletonBase.h"

#pragma region ���� (FMOD + Ʈ������ + ���͸� ����)
/*
�� FMOD

- ���� ���� ���̺귯��
�� ���� ���� �����̱� ������ �Ϲ������� ���Ǵ� ��κ��� ���� Ȯ���ڴ� ���� �����Ѵٰ� ���� �ɰ��̰� �߰��� �پ��� �÷������� ������ �Ѵ�.

- ��� ����?
�� WinAPI / DirectX ���� ��쿡�� ��ü ���� ���̺귯���� ������ ������ ������ �ʿ��� ��찡 ���� �����ϴ�. (����, ���� ������� �и��Ǹ鼭 �������� Ȱ��󵵰� �� ��������.)

�� ��� ����

- �𸮾� + ����Ƽ������ ���̼��� ������� �⺻ ����
�� �׷��� ������ ������ ��찡 ���� ��ø� ��ǥ�� �Ҷ��� ���̼����� �ʿ�� �Ѵ�.

- �𸮾� ������ �⺻������ �ʹ��ʹ��ʹ��ʹ� ���̱� ������ ���̼����� ���� ���� (�⺻ �÷��׽�)�� �Ǿ� �ִ�. -> �÷����� �߰�
�� EX : .bank


- ����Ƽ ���� ����� �⺻������ FMOD�� ��������� ��� ��� ��ɿ� ���Ѱ� �ƴϴ�.
�� �׷��� ������ �߰� ����� ����ϱ� ���ؼ��� �߰� ������ ��ġ�ؾ� �Ѵ�.
�� EX : .bank

- �̿��� ��κ��� �÷��������� ����ϱ� ���� ���� ó���� �ʿ��ϴ�.
�� ���, Ŭ����, �̸� ����, ���̺귯�� ��ũ -> ����..?

�� FMOD�� �̿��� ��ǥ���� ���ӵ�
�� ����, �Ϳ�, ���̿� ��ũ �ø���, ������ �ƽ� ������Ʈ V ��� ���� �ִ�.

�� FMOD ����

- ũ�� 3������ ������.
�� ���̺귯�� + ���α׷�

1. FMOD Ex
�� StudioAPI / Core API
�� �ο췹�� ���� ���� (�ַ� ����Ƽ�� ���� ä��Ǵ� API)
�� API ���·� �Ǿ� �ֱ� ������ �ٸ� ���̺귯�� ��� ������ ������. (����)
�� ������ �ڵ��� ���ϸ� ���� �� ���� ����. (����)
�� �ַ� �Ϲ����� ���� ������ ����Ѵٸ� ������ �ǰ� ���� �����̳ʰ� �������� ������ �Ǵ� ��찡 ����. (wav, mp3, mid)

===================================

2. FMOD �̺�Ʈ �ý���
�� Ex�� ���� ���̾� -> �����̳ʰ� �۾��� ���� �������� ����ϴ� Data ��� Driven API
�� �����̳��� �ɷ¿� ���� ������� ���� ���ʿ��� �ڵ尡 ��κ� ������� �̴� �� ���� ������� �̾�����.
�� Ư�� �����̳ʿ� ���� ���� ��Ʈ���� Ʃ���� ������ ���� ������ ���α׷��Ӱ� ���� ���� �����ؼ� �Ű��� ���� �ʾƵ� �ȴ�. -> ���� �ӵ�

3. FMOD �����̳�
�� ���� �̺�Ʈ�� ����� ���� ��
�� ��ȹ + ���� + ���⼺ �ܰ迡�� FMOD�� ä���� �Ǹ� ���� �����̳ʰ� �ַ� ����Ҳ���.
	�� ���� ����� ��
- ��� ������ ����ϴ� �ƴϸ� �����̳� ���� ����ϴ� �⺻������ Ʈ������ ���踦 �� �����̱� ������ ���α׷��ӷμ��� ���� ���� ���� �ִ�.

�� ���� ������� �����̳ʿ� ���� / ���񿡰� ��ų ������ �ٺ��ϴ� ����� ������ �ؾ� �Ѵ�.

�� FMOD �����ؼ� �ܺ� ����� ��κ� ���̺귯���� ���� �ش� �÷����� �� �°� Ŀ���� �Ǳ� ������ �ܺ� ���̺귯�� ����ϱ� ���ؼ��� ���̺귯���� ���� ���ذ� �ʿ��ϴ�.

- ���̺귯�� ����
���� ���̺귯�� : ������Ÿ�� ���̺귯��(lib)->ã�� ������ ����(����), �뷮�� ���(����)
���� ���̺귯�� : ��Ÿ�� ���̺귯��(dll)->�ʿ��� ������ �����´�.(����)

�ش� ���̺귯���� ������ �� ������ ���η� �������� �������� ������ �Ǵ�

*/
#pragma endregion

// ���� ����
constexpr auto soundBuffer = 10;

// ������ ä�� ���� (����)
constexpr auto extraSoundChannel = 5;

// �� ���� ����
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;

using namespace FMOD;

class SoundManager : public SingletonBase<SoundManager>
{
private:
	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundsIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelsIter;

	System* _system;
	Sound** _sound;
	Channel** _channel;

	arrSounds _mTotalSounds;
public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	void addSound(string keyName, string soundName, bool background, bool loop);

	void play(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	SoundManager();
	~SoundManager() {}
};

