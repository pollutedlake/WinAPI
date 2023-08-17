#include "stdafx.h"
#include "Timer.h"

HRESULT Timer::init(void)
{
    // QueryPerformanceFrequency() : 초당 진동 수를 체크하고 고성능 타이머를 지원하면 T / 반대라면 F
    // ㄴ LARGE_INTEGER
    // ㄴ lpperiodFrequency : 초당 파악할 수 있는 시간이 들어간다. (기본은 밀리 세컨)
    // 사용이 가능한 경우
    if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
    {
        _isHardware = true;

        // QueryPerformanceCounter : 특정 지점에서 몇번 진동했는가를 나타내는 함수
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
