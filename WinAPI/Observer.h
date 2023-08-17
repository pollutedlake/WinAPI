#pragma once
#include "GameNode.h"

enum Event
{

};

class Observer
{
public:
	virtual void onNotify(const GameNode& entity, Event event) = 0;
	virtual ~Observer() {}
};

