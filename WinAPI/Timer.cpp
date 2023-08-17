#include "stdafx.h"
#include "Timer.h"

HRESULT Timer::init(void)
{
    // QueryPerformanceFrequency() : �ʴ� ���� ���� üũ�ϰ� ���� Ÿ�̸Ӹ� �����ϸ� T / �ݴ��� F
    // �� LARGE_INTEGER
    // �� lpperiodFrequency : �ʴ� �ľ��� �� �ִ� �ð��� ����. (�⺻�� �и� ����)
    // ����� ������ ���
    if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
    {
        _isHardware = true;

        // QueryPerformanceCounter : Ư�� �������� ��� �����ߴ°��� ��Ÿ���� �Լ�
        QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
    }
    return S_OK;
}

void Timer::tick(float lockFPS)
{
}

unsigned long Timer::getFrameRate(char* str) const
{
    return 0;
}

Timer::Timer()
{
}

Timer::~Timer()
{
}
