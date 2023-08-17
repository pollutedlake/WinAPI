#pragma once
#include "SingletonBase.h"
#include "EventListener.h"

class EventManager : public SingletonBase<EventManager>
{
private:
	typedef pair<vector<EventListener*>, vector<EventListener*>> eventList;

	eventList _eventMap;
public:
	void update(void);
	void addBullet(EventListener* bullet);
	void addEnemy(EventListener* enemy);

	vector<EventListener*> getBullet() {return _eventMap.first;}

	EventManager() {};
	~EventManager() {};
};

