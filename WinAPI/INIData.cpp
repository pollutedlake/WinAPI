#include "stdafx.h"
#include "INIData.h"

HRESULT INIData::init(void)
{
    return E_NOTIMPL;
}

void INIData::release(void)
{
}

void INIData::addData(char* section, char* key, char* value)
{
    tagIniData iniData;
    iniData.section = section;
    iniData.key = key;
    iniData.value = value;

    arrIniData vIniData;
    vIniData.push_back(iniData);
    _vIniData.push_back(vIniData);
}

void INIData::iniSave(char* fileName)
{
    char str[256];
    char dir[256];

    ZeroMemory(str, sizeof(str));
    ZeroMemory(dir, sizeof(dir));

    sprintf_s(dir, "\\INIDATA/%s.ini", fileName);

    GetCurrentDirectory(256, str);

    // strcat : 문자열 연결
    // ㄴ 폴더명 + 파일명
    strcat_s(str, dir);

    for (int i = 0; i < _vIniData.size(); i++)
    {
        arrIniData vData = _vIniData[i];

        // 분기 : 너 어떤 파일 볼래? -> INI
        // WritePrivateProfileString() : 파일의 정보(문자열)를 쓰며 만약에 해당 섹션과 키값이 없으면 자동으로 생성을 시킨다.
        WritePrivateProfileString
        (
            vData[0].section,
            vData[0].key,
            vData[0].value,
            str
        );

        vData.clear();
    }

    _vIniData.clear();
}

char* INIData::loadDataString(char* fileName, char* section, char* key)
{
    char str[256];
    char dir[256];

    ZeroMemory(str, sizeof(str));
    ZeroMemory(dir, sizeof(dir));

    sprintf_s(dir, "\\INIData/%s.ini", fileName);

    GetCurrentDirectory(256, str);
    strcat_s(str, dir);

    char data[64] = {NULL};

    // 파일 읽기
    GetPrivateProfileString
    (
        section,        // 읽어올 밸류가 있는 섹션의 이름
        key,            // 읽어올 밸류의 네임
        "",             // 섹션이름이나 키 이름을 찾지 못하면 출력한 문자열
        data,           // 키값에서 가르키는 값을 저장할 버퍼
        64,             // 키값을 저장할 버퍼 사이즈
        str
    );

    return data;
}

int INIData::loadDataInteger(char* fileName, char* section, char* key)
{
    char str[256];
    char dir[256];

    ZeroMemory(str, sizeof(str));
    ZeroMemory(dir, sizeof(dir));

    sprintf_s(dir, "\\INIData/%s.ini", fileName);

    GetCurrentDirectory(256, str);
    strcat_s(str, dir);

    return GetPrivateProfileSection(section, key, 0, str);
}
