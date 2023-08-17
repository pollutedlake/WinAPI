#pragma once
#include "SingletonBase.h"
class TimeManager : public SingletonBase<TimeManager>
{
public:
	TimeManager();
	~TimeManager();
};

