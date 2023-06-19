#pragma once
#include "GameNode.h"
#include "CT_Teeth.h"

/*
����3. �Ǿ��̻� ����

- �Ǿ��̻��� �ּ� 8�� �̻�

- �Ǿ��̻��� ���ȴ��� �ƴ����� ���ؼ� Ȯ���� �����ؾ� �Ѵ�.

- �ʼ� : �Ǿ��̻��� ������ �ִϸ��̼� ����
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

