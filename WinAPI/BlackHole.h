#pragma once
#include "GameNode.h"
#include "BH_BlackHole.h"
#include "BH_Object.h"

#define OBJECTNUM		3000

class BlackHole : public GameNode
{
private:
	BH_BlackHole* _blackHole;
	vector<BH_Object*> _objectList;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	BlackHole() {}
	virtual ~BlackHole() {}
};

