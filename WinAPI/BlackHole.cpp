#include "stdafx.h"
#include "BlackHole.h"

HRESULT BlackHole::init(void)
{
    _blackHole = new BH_BlackHole;
    _blackHole->init();
    for (int i = 0; i < OBJECTNUM; i++)
    {
        _objectList.push_back(new BH_Object);
        _objectList[i]->init(_blackHole->getPosition());
    }
    return S_OK;
}

void BlackHole::release(void)
{
    _blackHole->release();
    SAFE_DELETE(_blackHole);
    for (auto it = _objectList.begin(); it != _objectList.end();)
    {
        (*it)->release();
        SAFE_DELETE(*it);
        it = _objectList.erase(it);
    }
}

void BlackHole::update(void)
{
    if (_blackHole->update())
    {
        for (auto it = _objectList.begin(); it != _objectList.end(); ++it)
        {
            if ((*it)->getActive())
            {
                (*it)->setVector(_blackHole->getPosition());
            }
        }
    }
    for (auto it = _objectList.begin(); it != _objectList.end(); ++it)
    {
        (*it)->update(_blackHole->getPosition());
    }
}

void BlackHole::render(void)
{
    _blackHole->render(getMemDC());
    for (auto it = _objectList.begin(); it != _objectList.end(); ++it)
    {
        (*it)->render(getMemDC());
    }
}
