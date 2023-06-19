#pragma once
#include "GameNode.h"
#include "CT_Teeth.h"

/*
과제3. 악어이빨 게임

- 악어이빨은 최소 8개 이상

- 악어이빨에 물렸는지 아닌지에 대해서 확인이 가능해야 한다.

- 필수 : 악어이빨이 닫히는 애니메이션 구현
*/
class CrocodileTeeth : public GameNode
{
private:
	CT_Teeth* teeth[8];
public:
	virtual HRESULT init(void);
	virtual void update(void);
	virtual void release(void);
	virtual void render(HDC hdc);

	CrocodileTeeth() {}
	virtual ~CrocodileTeeth() {}
};

