#pragma once
#include "GameNode.h"
#include "Flame.h"
#include "Bullets.h"
#include "ProgressBar.h"
// ������� �ο�

#define ROCKET_SPEED 3.0f

#pragma region ����Ʈ ������
/*
�� ����Ʈ ������

- auto_ptr�� ��ü�ϱ� ���� ���� ���� (C++11���� ����)
- �޸� ���� �����ϰ� ������ Ȯ���� ���� ����Ѵ�. -> ����Ʈ ������

- ������ó�� �����ϴ� Ŭ���� ���ø�
�� ����� ���� �޸𸮸� �ڵ����� �����Ѵ�.

- ����ϱ������� <memory> ����� �ʿ��ϰ� �⺻������ ���� �����Ͱ� ���� �޸𸮸� �⸮Ű�� �⺻ �����͸� ����Ʈ �����Ϳ� �����ϴ� �������� ���� ����Ѵ�.

- new..? (���� �Ҵ�)
�� �׻� ����Ʈ �����͸� ����� �� ¦��ó�� �����ϴ� �ظ��� �޸𸮴� ��� �ӵ��� ì�ܾ� �Ѵ�.

�� ����

1. unique_ptr
�� ���� ��ü (��ü�� ���� �������� �����ϰ�)

2. shared_ptr
�� �Ϲ������� ���� ��ü���� �ϳ��� ��ü�� ����ϰ� ���� �� �����Ѵ�.
�� ���� Ƚ���� ������� �����ϸ� �� �����ʹ� ��ü�� �������� �����Ҷ� ����ϸ� ����.

3. weak_ptr
�� �ܵ� ���� �Ұ�
�� shared ptr�� ������ ��ü ���� ������ ����� �� �ʿ��ϴ�.
�� ��ȯ ������ ������ �� ���ȴ�.
*/
#pragma endregion

enum EWeapon
{
	MISSILE, BEAM
};

// enable_shared_from_this : ��ü�� ���� �� �Ҹ꿡 ���� ���� ������ �ذ��Ѵ�.
// �� ������ ��ü���� �������� �ο��Ѵ�.
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
/* ���� 1. ���� �̻��� �߻�

//- �̿ϼ� �Լ��� �ϼ��ϰ� ������ �̻����� �߻��Ѵ�.

//- �翬�� �̻��� �̹����� ���ο����� ���

// ���� 2. �� ��Ʈ�������� ���� ���� ���� �ӹ�

// - ���� �ĺ��� 3�� (2��)

// ���� 3. Ÿ�ϸ� �����

- ����ڰ� �Է��� ���ڷ� Ÿ�ϸ��� �׸���.(�ִ� ������ : 100)
�� EX: 20�� �Է��ϸ� 20 X 20 �������� Ÿ���� ȭ�鿡 �׷�����.

- Ÿ�ϸʾȿ��� ������ ��ġ�� �̹��� 2���� ����.

- �̹����� �Ź� Ÿ�ϸ��� ���� �׷��ٶ����� ��ġ�� �ٲ��� �ϰ�
 �׷��� �̹����� ���콺�� Ŭ���� �� ������ ��ġ ���� ������ �� �־�� �Ѵ�.

 �ʼ�: STL ����
*/