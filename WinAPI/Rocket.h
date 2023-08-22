#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"
#include "ProgressBar.h"
// 설계와의 싸움

#define ROCKET_SPEED 3.0f

#pragma region 스마트 포인터
/*
▶ 스마트 포인터

- auto_ptr를 대체하기 위해 나온 문법 (C++11에서 삭제)
- 메모리 릭을 방지하고 안정성 확보를 위해 사용한다. -> 스마트 포인터

- 포인터처럼 동작하는 클래스 템플릿
ㄴ 사용이 끝난 메모리를 자동으로 해제한다.

- 사용하기전에는 <memory> 헤더가 필요하고 기본적으로 원시 포인터가 실제 메모리를 기리키고 기본 포인터를 스마트 포인터에 대입하는 형식으로 많이 사용한다.

- new..? (동적 할당)
ㄴ 항상 스마트 포인터를 사용할 때 짝꿍처럼 등장하니 왠만한 메모리는 묶어서 속도를 챙겨야 한다.

▷ 종류

1. unique_ptr
ㄴ 유일 객체 (객체에 대한 소유권을 유일하게)

2. shared_ptr
ㄴ 일반적으로 여러 객체에서 하나의 객체를 사용하고 싶을 때 적용한다.
ㄴ 참조 횟수를 기반으로 동작하며 이 포인터는 객체간 소유권을 분할할때 사용하면 좋다.

3. weak_ptr
ㄴ 단독 실행 불가
ㄴ shared ptr이 소유한 객체 대한 접근을 허용할 때 필요하다.
ㄴ 순환 참조를 제거할 때 사용된다.
*/
#pragma endregion

enum EWeapon
{
	MISSILE, BEAM
};

// enable_shared_from_this : 객체의 생성 및 소멸에 의한 참조 문제를 해결한다.
// ㄴ 각각의 객체에게 소유권을 부여한다.
class Rocket : public GameNode, public std::enable_shared_from_this<Rocket>
{
private:

	GImage* _image;
	Flame* _flame;
	MissileM1* _missileM1;
	Beam* _beam;
	EWeapon _setWeapon;
	ProgressBar* _hpBar;


	//GImage* objectData;

	RECT _rc;
	float _x, _y;
	float _currentHp;
	float _maxHp;
	bool _beamIrradiation;

	//vector<std::shared_ptr<Rocket>> spRocket;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void removeMissile(int arrNum);

	MissileM1* getMissile(void) {return _missileM1;}
	Beam* getBeam(void) {return _beam;}

	RECT getRect(void) {return _rc;}

	inline void hitDamage(float damage)
	{
		if (_currentHp <= 0)
		{
			_currentHp = 0;
			return;
		}

		_currentHp -= damage;
	}

	/*std::shared_ptr<Rocket> get_shared_ptr()
	{
		return shared_from_this();
	}*/

	Rocket() {/*objectData = new GImage[10];*/ }
	~Rocket() {/*delete[] objectData;*/ }
};
/* 과제 1. 로켓 미사일 발사

//- 미완성 함수를 완성하고 로켓이 미사일을 발사한다.

//- 당연히 미사일 이미지는 프로엠으로 출력

// 과제 2. 팀 포트폴리오로 만들 게임 선정 임박

// - 최종 후보군 3개 (2개)

// 과제 3. 타일맵 만들기

- 사용자가 입력한 숫자로 타일맵을 그린다.(최대 사이즈 : 100)
ㄴ EX: 20을 입력하면 20 X 20 사이즈의 타일이 화면에 그려진다.

- 타일맵안에는 랜덤한 위치에 이미지 2장이 들어간다.

- 이미지는 매번 타일맵을 새로 그려줄때마다 위치가 바껴야 하고
 그려진 이미지는 마우스로 클릭할 수 있으며 위치 또한 변경할 수 있어야 한다.

 필수: STL 벡터
*/