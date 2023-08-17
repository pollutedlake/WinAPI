#include "stdafx.h"
#include "EventManager.h"

void EventManager::update(void)
{
	for (auto iter = _eventMap.first.begin(); iter != _eventMap.first.end();)
	{
		if (*iter == nullptr)
		{
			iter = _eventMap.first.erase(iter);
		}
		else
		{
			for (auto iter2 = _eventMap.second.begin(); iter2 != _eventMap.second.end(); ++iter2)
			{
				RECT temp;
				if (IntersectRect(&temp, ((*iter)->getRect()), ((*iter2)->getRect())))
				{
					(*iter)->collision();
					(*iter2)->collision();
					break;
				}
			}
			++iter;
		}
	}
}

void EventManager::addBullet(EventListener* bullet)
{
  	_eventMap.first.push_back(bullet);
}

void EventManager::addEnemy(EventListener* enemy)
{
	_eventMap.second.push_back(enemy);
}
