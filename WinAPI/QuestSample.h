#pragma once
#include "Quest.h"

//class Quest;

// 맵의 망령이 되면 안된다.

#pragma region 큐
/*
▶ 큐 (queue)
- 큐는 리스트의 일종으로 스택과 다르게 FIFO 자료구조

- 삽입이 일어나는 쪽을 뒤, 삭제가 일어나는 쪽을 앞이라고 한다.

※ 프린트 큐 / CPU 스케줄링 / 버퍼 (데이터) / BFS + DFS 등에 자주 사용된다.

▷ 큐에서 자주 사용하는 멤버 함수

- front()
 ㄴ 첫번째 요소 접근

- back()
 ㄴ 마지막 요소 접근

- push()
 ㄴ 데이터 삽입

- size()
 ㄴ 크기

- empty()
 ㄴ 비어있는지 확인
*/
#pragma endregion

class QuestSample
{
private:
	// CPU 스케줄링
	// 데이터 버퍼
	// 프린트 큐, BFS / DFS
	queue<Quest*> _quest;

public:
	void init(void);
	void questSetup(Quest* pQuest = nullptr);

	queue<Quest*>* getQuest() {return &this->_quest;}

	QuestSample() {}
	~QuestSample() {}

};

