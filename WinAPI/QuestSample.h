#pragma once
#include "Quest.h"

//class Quest;

// ���� ������ �Ǹ� �ȵȴ�.

#pragma region ť
/*
�� ť (queue)
- ť�� ����Ʈ�� �������� ���ð� �ٸ��� FIFO �ڷᱸ��

- ������ �Ͼ�� ���� ��, ������ �Ͼ�� ���� ���̶�� �Ѵ�.

�� ����Ʈ ť / CPU �����ٸ� / ���� (������) / BFS + DFS � ���� ���ȴ�.

�� ť���� ���� ����ϴ� ��� �Լ�

- front()
 �� ù��° ��� ����

- back()
 �� ������ ��� ����

- push()
 �� ������ ����

- size()
 �� ũ��

- empty()
 �� ����ִ��� Ȯ��
*/
#pragma endregion

class QuestSample
{
private:
	// CPU �����ٸ�
	// ������ ����
	// ����Ʈ ť, BFS / DFS
	queue<Quest*> _quest;

public:
	void init(void);
	void questSetup(Quest* pQuest = nullptr);

	queue<Quest*>* getQuest() {return &this->_quest;}

	QuestSample() {}
	~QuestSample() {}

};

