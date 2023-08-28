#pragma once
#include "SingletonBase.h"

class GameNode;
//class Scene;

class SceneManager : public SingletonBase<SceneManager>
{
	//friend class SingletonBase<SceneManager>;
public:
	typedef map<string, GameNode*> mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLoadingSceneList;

	//map<int, Scene> _mSceneList;
public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);

	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);
	bool findScene(string sceneName);

	HRESULT changeScene(string sceneName);

	friend DWORD CALLBACK loadingThread(LPVOID proc);

	SceneManager() {};
	~SceneManager() {};
};

//#define SCENEMANAGER SceneManager::getSingleton()