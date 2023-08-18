#include "stdafx.h"
#include "Bullets.h"
#include "SG_Enemy.h"

HRESULT Missile::init(int bulletMax, float range)
{
	_range = range;

	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		// ZeroMemory(Zero) vs memset(nonZero) ZeroMemory 안에 memset동작함
		ZeroMemory(&bullet, sizeof(tagBullet));

		bullet.img = new GImage;
		bullet.img->init("Resources/Images/ShootingGame/Missile.bmp", 0.f, 0.f, 416, 64, 13, 1, true, RGB(255, 0, 255));
		bullet.fire = false;
		bullet.speed = 5.0f;
		_vBullet.push_back(bullet);
	}
	return S_OK;
}

void Missile::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void Missile::update(void)
{
	move();
}

void Missile::render(void)
{
	draw();
}

void Missile::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if(_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->count  = 0; 
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());

		break;
	}
}

void Missile::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
		
		_viBullet->count++;

		if(_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void Missile::move(void)
{
	
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		if (MY_UTIL::getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y) > _range)
		{
			_viBullet->fire = false;
		}
	}
}

HRESULT MissileM1::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;

	return S_OK;
}

void MissileM1::release(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void MissileM1::update(void)
{
	move();
}

void MissileM1::render(void)
{
	draw();
}

void MissileM1::fire(float x, float y)
{
	if(_bulletMax <= _vBullet.size()) return;
	tagBullet bullet; 
	// ZeroMemory(Zero) vs memset(nonZero) ZeroMemory 안에 memset동작함
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = new GImage;
	bullet.img->init("Resources/Images/ShootingGame/Missile.bmp", 0.f, 0.f, 416, 64, 13, 1, true, RGB(255, 0, 255));
	bullet.speed = 5.0f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());
	//vector<EventListener*> temp = EVENTMANAGER->getBullet();
 	/*for (auto iter = temp.begin(); iter != temp.end(); ++iter)
	{
		cout << (*iter)->getRect()->left << endl;
	}*/
	_vBullet.push_back(bullet);
	//_vBullet.back().setRect(&_vBullet.back().rc);
	//EVENTMANAGER->addBullet(&_vBullet.back());
}

void MissileM1::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
	for (_viEffect = _vEffect.begin(); _viEffect != _vEffect.end();)
	{
		_viEffect->img->frameRender(getMemDC(), _viEffect->rc.left, _viEffect->rc.top);
		_viEffect->count++;
		if (_viEffect->count % 5 == 0)
		{
			_viEffect->img->setFrameX(_viEffect->img->getFrameX() + 1);
			if (_viEffect->img->getFrameX() >= _viEffect->img->getMaxFrameX())
			{
				SAFE_DELETE(_viEffect->img);
				_viEffect = _vEffect.erase(_viEffect);
			}
			else
			{
				++_viEffect;
			}
		}
		else
		{
			++_viEffect;
		}
	}
}

void MissileM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		if (MY_UTIL::getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y) > _range)
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}
void MissileM1::removeBullet(int arrNum)
{
	tagEffect effect;
	effect.img = new GImage;
	effect.img->init("Resources/Images/ShootingGame/Explosion.bmp", 0.f, 0.f, 1426, 77, 18, 1, true, RGB(255, 0, 255));
	effect.x = (_vBullet.begin() + arrNum)->x;
	effect.y = (_vBullet.begin() + arrNum)->y;
	effect.rc = RectMakeCenter(effect.x, effect.y, effect.img->getFrameWidth(), effect.img->getFrameHeight());
	_vEffect.push_back(effect);
	SAFE_DELETE(_vBullet[arrNum].img);

	_vBullet.erase(_vBullet.begin() + arrNum);
}
/*
과제 1. 움직이는 적 패턴 추가
- 움직임을 서로 다르게 해온다.
ㄴ 패턴은 총 3가지를 만들면 OK

과제 2. 로켓 무장 변경 추가

- F1: 일반 미사일

- F2: 산탄

- F3 : 미니 로켓 생성

- F4 : 실드

_ F5 : 유도 미사일

_ F6 : 레이저

_ F7 : 블랙홀
ㄴ 영향을 맏는 적과 아닌 적으로 구분
ㄴ 블랙홀에 가까운 적일수록 스킬이 끝나면 팅겨 나가는 관성이 강해진다.
*/

HRESULT Beam::init(int bulletMax, float range)
{
	_range = range;
	_bulletMax = bulletMax;
	return S_OK;
}

void Beam::release(void)
{

	// 1. 정석 (C++ 표준에서 얘기하는 문법)
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	// 2. 줄이고 싶다. (변수에 의해서 길어지는 가동석 파괴)
	//_viBullet = _vBullet.begin();
	//for (; _viBullet != _vBullet.end(); ++_viBullet)
	//{
	//	SAFE_DELETE(_viBullet->img);
	//}

	//// 3. 협업시 효율적인건 뭐가 있을까?
	//iterBullet iterBullet = _vBullet.begin();
	//// 협업 x 단, 다른사람의 코드와 전혀 연관이 없다면 사용해도 됨.
	//auto iterBullet = _vBullet.begin();
	//for (; iterBullet != _vBullet.end(); ++iterBullet)
	//{
	//	SAFE_DELETE(iterBullet->img);
	//}

	//// 4. range based -> 언리얼에서는 iterator가 무거원서 빠졌기 때문에 이 방식으로 한다.(Low level)
	//for (auto iter : _vBullet)
	//{
	//	SAFE_DELETE(iter.img);
	//}

	//// 5. for each(High Level) -> 별도의 연산이 필요없을 때 한해서 사용해도 된다.
	//for each (auto iter in _vBullet)
	//{
	//	SAFE_DELETE(iter.img);
	//}

	//// 6. for_each
	//// ㄴ 반복자의 시작과 끝, 그리고 함수를 파라미터로 받는다.
	//// ㄴ 마지막 부분이 파라미터이기 때문에 람다식으로 표현이 가능
	//for_each(_vBullet.begin(), _vBullet.end(), update);

	//int Value = 0;
	//for_each(_vBullet.begin(), _vBullet.end(), [&Value](auto& number)
	//{
	//	Value += number;
	//});

	///*
	//람다식
	//- [](){}()
	//ㄴ [캡쳐] (매개 변수){(반환)함수 동작} (호출 인자(생략 가능))

	//[] (int numA, int numB) { cout << numA + numB << endl; } (10, 20);
	//[] {int numA, int numB) { return numA + numB; } (10, 20);

	//========

	//[]: 같은 영역에 있는 모든 변수에 접근 X
	//[&]: 같은 영역에 있는 모든 변수를 참조 O
	//[=]: 같은 영역에 있는 모든 변수를 값 O
	//[&, 변수A]: 같은 영역에 있는 모든 변수를 참조 캡쳐. 단, 변수A만 값으로 캡쳐
	//[=, 변수A]: 같은 영역에 있는 모든 변수를 값으로 캡쳐. 단, 변수A만 참조로 캡쳐
	//[&변수A]: 같은 영역에 있는 변수A를 참조 캡쳐.
	//*/

	//int numberA = 10;
	//int numberB = 20;

	//auto resultA = [](int NumA, int NumB) {return NumA + NumB;} (10, 10);
	//auto resultB = [&]()->int {return numberA + numberB;} ();
	//auto resultC = [=, &numberA]()->int {return numberA + numberB;} ();

	//// 7. transform
	//// ㄴ 반복자를 이용한 반복문이라고 할 수 있다. (결과를 다른 컨테이너에 저장)
	//// ㄴ 원본 컨테이너도 가능 + 람다

	//vector<int> _vBulletReload;
	//transform(_vBullet.begin(), _vBullet.end(), _vBulletReload.begin(), update);

	//transform(_vBullet.begin(), _vBullet.end(), _vBulletReload.begin(), 
	//[](__int64 numA)->auto {return numA;});

	_vBullet.clear();
}

void Beam::update(void)
{
	move();
}

void Beam::render(void)
{
	draw();
}

void Beam::fire(float x, float y)
{
	if (_bulletMax <= _vBullet.size()) return;
	tagBullet bullet;
	// ZeroMemory(Zero) vs memset(nonZero) ZeroMemory 안에 memset동작함
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.speed = 0.05f;
	bullet.img = new GImage;
	bullet.img->init("Resources/Images/ShootingGame/Beam.bmp", 0.f, 0.f, 412, 801, 4, 1, true, RGB(255, 0, 255));
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.img->getFrameWidth(), bullet.img->getFrameHeight());

	_vBullet.push_back(bullet);
}

void Beam::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
			_viBullet->count = 0;
		}
	}
}

void Beam::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, _viBullet->img->getFrameWidth(), _viBullet->img->getFrameHeight());
		if (MY_UTIL::getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y) > _range)
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else
		{
			++_viBullet;
		}
	}
}
