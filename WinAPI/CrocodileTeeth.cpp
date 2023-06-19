#include "stdafx.h"
#include "CrocodileTeeth.h"

HRESULT CrocodileTeeth::init(void)
{
	GameNode::init();
	for (int i = 0; i < 8; i++)
	{
		teeth[i] = new CT_Teeth;
		teeth[i]->init();
		teeth[i]
	}
	return S_OK;
}

void CrocodileTeeth::update(void)
{
	GameNode::update();
}

void CrocodileTeeth::release(void)
{
	GameNode::release();
}

void CrocodileTeeth::render(HDC hdc)
{
}
