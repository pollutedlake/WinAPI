#pragma once
#include "SingletonBase.h"

#pragma region 파일 입출력 (INI)
/*
▶ INI(Initialization)
- 응용 프로그램이나 윈도우 자체의 초기 설정에 필요한 정보가 기입된 텍스트 파일

- INI 파일은 설정 파일에 대한 사실상 표준이라고 정의할 수 있다.
ㄴ 대체할 수 있는 포맷이 전무하고 설정 파일을 관리할 때 아주 용이하기 때문
ㄴ 또한 단순 구조의 텍스트 파일로 구성이 되어 있다는 특징이 있다.
ㄴ 텍스트 파일의 포맷을 가지고 있기 때문에 확장자 변환도 허용을 한다 (단, txt에 한해서)

- txt 파일은 마이크로소프트가 만든 OS인 윈도우즈에 연결이 되지만 다른 운영체제에서도 사용을 할 수 있다.

- 일반적으로 프로그램이 실행될 때 해당하는 INI 파일을 통해서 프로그램이 실행에 필요한 기본 정보를 읽어 들이면서 시작이 된다.

▷ 게임에서는 언제 사용해야 하는가?

- 게임쪽에서는 옵션등에 자주 사용이 되고 상용 엔젠의 경우 보통 에디터의 설정값 저장에 사용된다.

- 게임쪽에서 INI 파일은 주로 값이 자주 바뀌는 경우에 사용하면 좋다.

▷ INI 하면 떠올릴 3가지

- 섹션과 키, 그리고 값

- 일반적인 형태 (커스텀 X)

[Section]
Key = Value

- 커스텀 형태 (상용 엔진)
[Section]
Path = Value (C:\........)
LifeTime = / key(1) / = 1
*/
#pragma endregion
struct tagIniData
{
	char* key;
	char* section;
	char* value;
};

class INIData : public SingletonBase<INIData>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<arrIniData> arrIniDatas;

private:
	arrIniDatas _vIniData;

public:
	HRESULT init(void);
	void release(void);

	// 데이터 추가 ->
	void addData(char* section, char* key, char* value);
	// 세이브
	void iniSave(char* fileName);

	// 문자값
	char* loadDataString(char* fileName, char* section, char* key);
	// 정수
	int loadDataInteger(char* fileName, char* section, char* key);

	INIData() {}
	~INIData() {}
};

