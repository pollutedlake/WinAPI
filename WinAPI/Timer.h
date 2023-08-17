#pragma once

/*
- API ���� �Լ�
�� ������ �ִ�...
�� ���� ���� �ܰ迡�� ������ ����ϰ� ���� Ÿ�̸ӵ��� �ƴϱ� ������ ���е��� ��������.

timeGetTime (�����찡 ���۵ǰ� 1���� �������� 60000 ����)
GetTickCount (���� �ð� üũ -> ���õ� ���� 1�ʿ� 1000�� ƽ�� �����Ѵ�. �� 50�� ���� ����)
������ �� �Լ��� �Ѱ谡 �ִµ� �ٷ� ��ȯ �ð��� �ִ� DWORD(32��Ʈ)��� ���̴�.
��¥�� ������ 49.7���ε�, 49.7�� ���� ������� �������� ���� ��� 0���� �ʱ�ȭ �Ǵ� ���̴�.
GetTickCount64 

- Ÿ�̸�
�� �ð��� �����ϴ� �Լ����� �⺻������ �����찡 ���۵� ���� ���� �ð��� Milli Second ������ ��ȯ(1000���� 1��)
�� �и� ������ �⺻������ ���е��� �������� -> ���ӿ���
�� �׷��� ������ ���� ���� ���е��� ���Ѵٸ� �� �ػ� Ÿ�̸Ӹ� �߰��ؼ� ����ؾ� �Ѵ�.

- Ÿ�̸Ӹ� �����Ҷ��� ���� �ػ󵵿� Ŭ���� �˰� �־�� �Ѵ�.

�� �ػ�?

- �پ��� �ð� �Լ����� �ð��� �����ϱ� ���� ������ ƽ ��� ������ �ִ�.
	�� �� ������ 1���� �������� ����� �� �󸶳� ���� ���������� ���� �� �ִ��� ���
- 1�е��� �󸶳� ���� ƽ���� ������ �ð��� ��Ȯ���� ���̴��İ� ���ػ󵵿� ���ػ��� ���̸� �߻� ��Ų��.

�� Ŭ�� (������)

- Ÿ�̸ӿ��� ����ϴ� Ŭ���� CPU Ŭ��

- Ŭ�� ��ü�� ������ ȸ���� ������ ���� ���̸� �츣�� ������ ǥ���ϴ°� �Ϲ��� (Hz)
�� Ex: 1�ʿ� 1Hz�̸� �������� ��ȣ�� �ѹ� �شٴ� ���(0 �Ǵ� 1)
	�� 1 ��Ʈ�� �ű� �� �ִٴ� ���
	�� 1GHz�� 10�� 9���� -> 10���
		�� 3.7GHz�� 37���

����
�� Milli Second
�� 10 Milli Second
�� 100 Milli Second

// int�� ���ȯ�濡 ���� �ٲ� �� ������ long�� ����ϴ� �ü���� ���� ����

*/

class Timer
{
private:
	float _timeScale;
	float _timeElapsed;
	bool _isHardware;

	__int64 _curTime;
	__int64 _lastTime;
	__int64 _periodFrequency;

	unsigned long _frameRate;
	unsigned long _FPSframeCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT init(void);
	// -> 
	void tick(float lockFPS = 0.0f);

	// �Լ� �ڿ� const ���̴� ���� : �� �Լ� �ȿ��� � ������ ������ �� ���ٴ� �ǹ�
	unsigned long getFrameRate(char* str = nullptr) const;
	inline float getElapsedTime(void) const {return _timeElapsed;}
	inline float getWorldTime(void) const {return _worldTime;}

	Timer();
	~Timer();
};

