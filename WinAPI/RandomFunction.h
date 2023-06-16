#pragma once
#include "SingletonBase.h"

class RandomFunction : public SingletonBase <RandomFunction>
{
public:
	RandomFunction()
	{
		// GetTickCount() : API 공용 함수
		// ㄴ API 함수로 OS가 부팅된 후의 경과 시간을 체크해 준다.
		// ㄴ 밀리세컨드 단위로 체크가 가능하며 밀리세컨드 단위로 시간 값을 반환하기 때문에 규모가 크지 않는 로직에 적합하다.
		srand(GetTickCount());
	}
	~RandomFunction() {}
	
	inline int getInt(int num)
	{
		return rand() % num;
	}
	HRESULT init(void) { return S_OK; }
	// 0을 조심하자
	inline int getFromIntTo(int fromNum, int toNum)
	{
		return rand() % (toNum - fromNum + 1) + fromNum;
	}

	float getFloat(void)
	{
		return (float)rand() / (float)RAND_MAX;
	}

	float getFloat(float num)
	{
		return (float)rand() / (float)RAND_MAX * num;
	}

	float getFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;

		return (rnd * (toNum - fromNum) + fromNum);
	}
};