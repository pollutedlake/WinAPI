#pragma once

class SceneManager;

class Scene
{
	// 상속 관계 무시
	// friend로 묶여있는 객체들에게만 데이터 전달
	/*
	friend : 말 그대로 친구
	ㄴ 복잡한 상속 구조 / 효율적인 구조를 설계할 때 많이 등장한다.
	ㄴ 상속(수직)과 친구(수평)의 관계
	ㄴ 접근 제어 지시자의 영향을 받지 않는다.
		ㄴ private까지 모두 접근이 가능하기 때문에 잘 쓰면 효율이 좋지만 그 반대라면 양아치 키워드

	- 클래스 + 함수
	ㄴ 전부이냐 / 단일(함수)

	- friend는 단방향

	- friend 속성은 상속이 Y / N ?
	ㄴ N : friend는 단방향이기 때문에 상속이 안된다. 상속은 양방향
	*/
	friend SceneManager;
private:

	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;

protected:
	

public:

	Scene();
	virtual ~Scene();
};

