#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"
//#include "Scene.h"

// 초기화'만' -> 호출 여부에 관계없이
GameNode* SceneManager::_currentScene = nullptr;
GameNode* SceneManager::_loadingScene = nullptr;
GameNode* SceneManager::_readyScene = nullptr;

DWORD CALLBACK loadingThread(LPVOID proc)
{
	// 교체될 씬의 함수 실행
	SceneManager::_readyScene->init();
	// 현재 씬을 교체될 씬으로 변경
	SceneManager::_currentScene = SceneManager::_readyScene;
	// 로딩 씬 해제
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
	// 보기에 좋고 간결하고 문제도 없어 보인다.
	// ㄴ C/C++ 언어에서는 싫어하는 형태
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

	// 바꾸지 못했다.
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

	// 바꾸지 못했다.
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

		// 클래스 / 구조체

		return S_OK;
	}
	return E_FAIL;
}