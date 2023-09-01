#include "stdafx.h"
#include "JsonSaveLoader.h"

// UTF-8...

HRESULT JsonSaveLoader::init(void)
{
    // Ȯ���� �Ǹ� ������ ������ null
    return S_OK;
}

void JsonSaveLoader::release(void)
{
}

void JsonSaveLoader::saveString(char* fileName, string data)
{
    TCHAR* buf = (TCHAR*)data.c_str();

    // HANDLE : �����쿡�� �ο��� ���� �ĺ���ȣ
    // �� ���������� 32��Ʈ ������
    HANDLE file;

    /*
    �� ����Ʈ ���� ǥ��(BOM)

    - ��ǻ�ʹ� �����͸� �޸𸮿� ������ �� ����Ʈ ������ ������ �����Ѵ�.

    - ����Ʈ ���� ǥ���� ����Ʈ ������ ǥ���ϴ� ������ ���� �� �տ� ���ڵ� ��Ŀ� ���õ� ���ڸ� �־ ���ڵ� ����� ǥ���ϴ� ��

    - �Ϲ����� �����Ϳ����� BOM�� Ȯ���� �� ���� ��� �����ͷ� �������� �� �� �ִ�.

    - �����ڵ��� ��� ���ڵ� ����̳� �ص�� ��Ŀ� ���� ����Ʈ ���� ǥ���� �ʿ��� ��찡 ���� ����.

    �� ������ -> UTF-16 ����� ��� 0xFEFF�� BOM���� ����Ѵ�.
        �� �ݴ�� ��Ʋ �ص�� ��� oxFFEF�� ǥ���Ѵ�.

    �� UTF-16�� �����ڵ� ����̱� ������ �ѱ��� 2����Ʈ�� ó���Ѵ�.
    �� �޸� �������� ������ ��ų �� �ִ�. -> �ƽ�Ű X
    �� ��Ȥ���� ���ڰ� �����ų� �ּ��� ������ ���̸� ���ڵ� ���� (�ڵ�)

    �� �ص��

    - ��ǻ�� ��Ű��ó���� ���� �߿��� ����

    - �ص���� ǥ���� ���� �� CPUȸ�縶�� ������ ���Ǹ� �� ����̱� ������ CPU ����̱� ������ CPU ȸ�縶�� ó���ϴ� �ص�� ����� �ٸ���. (���� / �ϵ� -> ��Ʋ �ص��)

    - �ص�ȿ� ���� ���ٸ� ó���� ���� �ʾҴٸ� �����ʹ� ��.�� -> ��.�� ���ʴ�� ����

    - �� �ص�� : �� -> ��
    �� �޸𸮿� ����� ���� �״�� ���� �� ������ ����� �����ϱⰡ ���� ����.
    �� ���� ģ���� �����̱� ������ ���� ������ �����ϴ�.

    - ��Ʋ �ص�� : �� <- ��
    �� ��Ʋ ���� ��� ��� ����� ���ڸ� ����ϴ� ���� ��İ��� �ٸ��� �Ųٷ� �о�� �Ѵ�.
    �� �޸𸮿� ����� ���� ���� ����Ʈ�� ����� �� ������ ������ �ʿ���� ��찡 ���� ������
       ������ ���ų� / ���������� �����ϴ�.

    �� �̷��� ������ ������ �� �𸣰ڴٸ� �׳� 0xFEFF����ϸ� ����

    */
    WORD BOM = 0xFEFF;
    DWORD dwBytes = 0;
    DWORD dwRead;

    /*
    CreateFile(): ���� ����� ��ġ�� ����ų� �о� ���� ����� �� �ִ� �ڵ� ��ȯ
    */

    file = CreateFile
    (
        fileName,                   // �����ϰų� �� ������ �̸�
        GENERIC_WRITE,              // ���� ���� Ÿ��
        0,                          // 0 -> ���� X -> �ٸ� ��ü X
        NULL,                       // ��� ����
        CREATE_ALWAYS,              // ���ο� ���� ���� -> ������ ���� ���� -> �����
        FILE_ATTRIBUTE_NORMAL,      // ���Ͽ� ���� �Ӽ� ������ �Ϲ����� �Ӽ��� �������� �ʰڴ�.
        NULL                        // ���¿� ���� ����
    );

    // return 0 / while(1) / -1
    // INVALID_HANDLE_VALUE : �ַ� �ʱ�ȭ ����� �ȴ�. -> �Ϲ������� -1�� �����Ѵ�.
    if (file == INVALID_HANDLE_VALUE)
    {
        MessageBox(_hWnd, "���� ���� ����", "����", MB_OK);
    }
    else
    {
        // �Ϲ����� ����
        //WriteFile(file, &BOM, 2, &dwBytes, NULL);
        // C / C++
        WriteFile(file, buf, strlen(buf) + sizeof(TCHAR), &dwRead, NULL);
        CloseHandle(file);
    }
}

void JsonSaveLoader::saveStringwithFileStream(char* fileName, string data)
{
    ofstream outFile(fileName);

    outFile << data << endl;

    outFile.close();
}

string JsonSaveLoader::loadString(char* fileName)
{
    // 8192 : Ŭ�󿡼� ����ϴ� �ֻ��� ��Ʈ -> ���� -> ���� ���۶�� �θ���.
    // ����� -> byte(1 ~ 8) / word(1 ~ 16) / dword(4 ~ 32) / qword(8 ~ 64)
    // �� 1��Ʈ (������) -> 8��Ʈ (1 ����Ʈ) -> 2����Ʈ (1 word)
    TCHAR* buf[8192];
    ZeroMemory(buf, sizeof(buf));

    HANDLE file;
    DWORD dwBytes;

    file = CreateFile
    (
        fileName,                   
        GENERIC_WRITE,              // �Ϲ����� ���·� �о���̰ڴ�.         
        0,                          
        NULL,                       
        OPEN_EXISTING,              // ������ �����Ҷ��� ����.
        FILE_ATTRIBUTE_NORMAL,      
        NULL                        
    );

    if (file == INVALID_HANDLE_VALUE)
    {
        MessageBox(_hWnd, "���� ���� ����", "����", MB_OK);

        return "";
    }
    else
    {
        ReadFile(file, buf, 8192, &dwBytes, NULL);
        CloseHandle(file);
    }
    //// ������ ����غ��� �Ѵ�.
    //return string(buf);
}

// �ٽ�
string JsonSaveLoader::loadStringWidthFileStream(char* fileName)
{
    ifstream fileIn;

    fileIn.open(fileName, ios::in);

    /*
    ios::in -> ���� ����(�б⸸ ������ ���·�)
    ios::out -> ���� ����(���⸸ ������ ���·�)
    ios::ate -> ������ ������ ���� ������ �̵� ��Ų��.(������ ������ ��)
    ios::app -> ������ �߰� (������ ���ʺ���)
    ios::binary -> ���̳ʸ� ���� ����
    */

    char data;
    string jsonStr;

    while (fileIn.get(data))
    {
        jsonStr += data;
    }

    fileIn.close();

    return jsonStr;
}


void JsonSaveLoader::saveJsonFile(char* fileName, Json::Value root)
{
    Json::StyledWriter writer;
    string outputConfig = writer.write(root);

    saveStringwithFileStream(fileName, outputConfig);
}

Json::Value JsonSaveLoader::loadJsonFile(char* fileName)
{
    string jsonStr = loadStringWidthFileStream(fileName);

    if (jsonStr == "")
    {
        MessageBox(_hWnd, "�����Ͱ� ����", "���", MB_OK);
        return NULL;
    }

    Json::Reader reader;
    Json::Value root;

    // parsing (�Ľ�) : Ư�� ������ �о� �鿩�� �̸� �ٸ� ���α׷��̳� ���� ��ƾ�� ����� �� �ִ� ���� ǥ�� ������� ��ȯ�� �ִ� ��
    // parse : �Ľ��� �ϴ� ���μ���
    bool parsingRet = reader.parse(jsonStr, root);
    return Json::Value();
}

JsonSaveLoader::JsonSaveLoader()
{
}

JsonSaveLoader::~JsonSaveLoader()
{
}
