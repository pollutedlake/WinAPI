#pragma once
#include "GameNode.h"
#include "CS_Cannon.h"
#include "CS_Shell.h"

#define SHELL_MAX		100

class CannonShoot : public GameNode
{
private:
	CS_Cannon* cannon;
	CS_Shell* shells[100];

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(HDC hdc);

	void fireShell(void);

	void collision(CS_Shell* shell1, CS_Shell* shell2);

	CannonShoot() {}
	virtual ~CannonShoot() {}
};

