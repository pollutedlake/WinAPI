#pragma once
#include "SingletonBase.h"

class JsonSaveLoader : public SingletonBase<JsonSaveLoader>
{
private:
	void saveString(char* fileName, string data);
	void saveStringwithFileStream(char* fileName, string data);

	string loadString(char* fileName);
	string loadStringWidthFileStream(char* fileName);

public:
	HRESULT init(void);
	void release(void);
	void saveJsonFile(char* fileName, Json::Value root);

	Json::Value loadJsonFile(char* fileName);

	JsonSaveLoader();
	~JsonSaveLoader();
};

