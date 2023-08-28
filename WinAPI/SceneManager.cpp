#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"
//#include "Scene.h"

// �ʱ�ȭ'��' -> ȣ�� ���ο� �������
GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;

DWORD CALLBACK loadingThread(LPVOID proc)
{
	// ��ü�� ���� �Լ� ����
	SceneManager::_readyScene->init();
	// ���� ���� ��ü�� ������ ����
	SceneManager::_currentScene = SceneManager::_readyScene;
	// �ε� �� ����
	SceneManager::_loadingScene->release();
	SceneManager::_loadingScene = nullptr;
	SceneManager::_readyScene = nullptr;
	return 0;
}


HRESULT SceneManager::init()
{
	_currentScene = nullptr;
	_loadingScene = nullptr;
	_readyScene = nullptr;
	return S_OK;
}

void SceneManager::release(void)
{
	// ���⿡ ���� �����ϰ� ������ ���� ���δ�.
	// �� C/C++ ������ �Ⱦ��ϴ� ����
	/*for each (auto scene in _mSceneList)
	{
		SAFE_DELETE(scene.second);
	}*/

	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != nullptr)
		{
			if (miSceneList->second == _currentScene)
			{
				miSceneList->second->release();
			}
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else
		{
			++miSceneList;
		}
	}
	_mSceneList.clear();
}

void SceneManager::update(void)
{
	if(_currentScene) 
	{
		_currentScene->update();
	}
}

void SceneManager::render(void)
{
	if (_currentScene) 
	{
		_currentScene->render();
	}
}

GameNode* SceneManager::addScene(string sceneName, GameNode* scene)
{
	if(!scene)
	{
		return nullptr;
	}
	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}

GameNode* SceneManager::addLoadingScene(string loadingSceneName, GameNode* scene)
{
	if (!scene)
	{
		return nullptr;
	}
	_mSceneList.insert(make_pair(loadingSceneName, scene));
	return scene;
}

bool SceneManager::findScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	// �ٲ��� ���ߴ�.
	if (find == _mSceneList.end())
	{
		return E_FAIL;
	}
	if (find->second == _currentScene)
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT SceneManager::changeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	// �ٲ��� ���ߴ�.
	if (find == _mSceneList.end())
	{
		return E_FAIL;
	}
	if (find->second == _currentScene)
	{
		return S_OK;
	}

	// HRESULT : SUCCEEDED / FAILED

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;

		// Ŭ���� / ����ü

		return S_OK;
	}
	return E_FAIL;
}