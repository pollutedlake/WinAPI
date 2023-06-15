#pragma once
#include <Windows.h>

#pragma region 순수 가상 함수
/*
▶ 순수 가상 함수
- 함수의 구현부가 없고, 기본적으로 선언부가 = 0으로 끝나는 가상함수를 뜻한다.

- 부모 클래스에서 순수 가상함수를 선언하면 자식 클래스에서 반드시 재정의한 함수를 멤버로 가져와야 한다.

EX)
- 선언 예시

IFunction() = 0;
IFunction() = NULL;
IFunction() PURE;
IFunction() abstract;

▶ 추상 클래스

- 순수 가상 함수가 N개 이상 있는 클래스를 의미한다.

▷ 특징

1. 객체를 생성할 수 없다.

2. 포인터 변수는 반들 수 있다.

3. 추상 클래스로 지정한 객체는 인스턴스를 만들 수 없다.
ㄴ 클래스

4. 추상 클래스의 자식 클래스를 통해 인스턴스를 생성할 수 있다.

5. C++ 언어가 개정되면서 추가된 abstract 키워드를 통해 명시하는것 가능

6. 더 나아가 C++11 이상의 버전부터는 멤버 변수 또는 멤버 함수가 포함된 여부와 상관없이 순수 가상함수를 1개 이상 가지고 있다면 이 클래스는 추상 클래스로 승격이 된다.

C++
class IWindowsMessageHandler atstract
{

};

C#
abstract class ITessellation
{

}

▶ 인터페이스

- OCP(개방 폐쇄의 원칙)
ㄴ 자신의 확장에는 열려 있고, 주변 변화에 대해서는 닫혀 있어야 한다.

- 순수 가상함수로만 이루어진 클래스를 인터페이라고 불렀다.
ㄴ 지금도

- 인터페이스의 개념은 하위 클래스에서 반드시 정의해야 할 함수를 정해주는 클래스라고 할 수 있다.

- C/C++ 언어에서는 공식적으로 인터페이스라는 기능을 지원하지 않는다.

※ 표기법 : 파스칼 케이스(I)

※ 구조도 : (C++ 기준)

Interface -> (상속) -> abstract 클래스 (기본 기능 구현) -> (상속) -> 기본 클래스 (순수 가상함수 재정의)

▷ 인터 페이스 특징

- 멤버 변수 및 함수를 포함할 수 없다. (정적 함수 포함 - template)
- 속성을 정의하는 한정자 사용금지
ㄴ EX : const

- 기본 클래스를 상속 받을 수 없다.

- 순수 가상 함수만 포함 시켜야 한다.

- 생성자 / 소멸자 / 연산자를 포함할 수 없다.

- 상속이 전제되기 때문에 public 속성을 가지고 있어야 한다.

▷ 장점

- 다중 상속에서의 안정성이 좋다.
ㄴ C++ 언어에서 많이 발생하는 다중 상속 / 중첩화 현상을 방지할 수 있다.
ㄴ 인터페이스를 이용하면 중첩화 현상 없이 다중 상속을 가능하게 한다.

▷ 단점

- 추상화를 기본으로 삼아 구현하기 때문에 가독성이 떨어진다.

- C++ 언어에서는 키워드를 사용할 수 없기 때문에 멤버 변수 선언등에 주의를 요해야 한다.

- 강제성이 없고 프로그래머에 의한 실수가 발생할 여지가 아주 다분하다.

★ 가상 소멸자
ㄴ 상속 관계에서 사용하면 자식 클래스의 소멸자를 호출한다는 점에서 잠재적인 오류를 예방하지만 상속 관계가 아닐 경우 성능저하가 발생하기 때문에 주의해야 한다.
*/
#pragma endregion
/*
__interface IGameClass
{
	virtual void idle() PURE;
	virtual void attack() PURE;
};

class CharacterChoices abstract : public IGameClass
{
private:

public:

};

// 파생 클래스

class Warrior : public CharacterChoices
{
private:

public:
	virtual void idle();
	virtual void attack();
};*/

class IWindowsMessageHandler
{
public:
	IWindowsMessageHandler();
	~IWindowsMessageHandler();
};

