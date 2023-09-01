#include "stdafx.h"
#include "JsonSaveLoader.h"

// UTF-8...

HRESULT JsonSaveLoader::init(void)
{
    // 확장이 되면 쓸꺼고 지금은 null
    return S_OK;
}

void JsonSaveLoader::release(void)
{
}

void JsonSaveLoader::saveString(char* fileName, string data)
{
    TCHAR* buf = (TCHAR*)data.c_str();

    // HANDLE : 윈도우에서 부여한 고유 식별번호
    // ㄴ 문법적으로 32비트 정수값
    HANDLE file;

    /*
    ▶ 바이트 순서 표식(BOM)

    - 컴퓨터는 데이터를 메모리에 저장할 때 바이트 단위로 나눠서 저장한다.

    - 바이트 순서 표식은 바이트 순서를 표시하는 것으로 문서 맨 앞에 인코딩 방식에 관련된 문자를 넣어서 인코딩 방식을 표현하는 것

    - 일반적인 에디터에서는 BOM을 확인할 수 없고 헥사 에디터로 봐야지만 볼 수 있다.

    - 유니코드의 경우 인코딩 방법이나 앤디안 방식에 따라 바이트 순서 표식이 필요한 경우가 아주 많다.

    ※ 윈도우 -> UTF-16 방식의 경우 0xFEFF를 BOM으로 사용한다.
        ㄴ 반대로 리틀 앤디안 경우 oxFFEF로 표현한다.

    ※ UTF-16은 유니코드 기반이기 때문에 한글을 2바이트로 처리한다.
    ㄴ 메모리 이점으로 연결을 시킬 수 있다. -> 아스키 X
    ㄴ 간혹가다 글자가 깨지거나 주석이 깨져서 보이면 인코딩 문제 (코드)

    ▷ 앤디안

    - 컴퓨터 아키텍처에서 아주 중요한 개념

    - 앤디안은 표준이 없을 때 CPU회사마다 각각의 정의를 한 방법이기 때문에 CPU 방법이기 때문에 CPU 회사마다 처리하는 앤디안 방식이 다르다. (인텔 / 암드 -> 리틀 앤디안)

    - 앤디안에 대한 별다른 처리를 하지 않았다면 데이터는 낮.주 -> 높.주 차례대로 저장

    - 빅 앤디안 : 좌 -> 우
    ㄴ 메모리에 저장된 순서 그대로 읽을 수 있으며 사람이 이해하기가 비교적 쉽다.
    ㄴ 비교적 친숙한 형태이기 때문에 오류 수정도 용이하다.

    - 리틀 앤디안 : 좌 <- 우
    ㄴ 리틀 같은 경우 평소 사람이 숫자를 사용하는 선형 방식과는 다르게 거꾸로 읽어야 한다.
    ㄴ 메모리에 저장된 값의 하위 바이트만 사용할 때 별도의 로직이 필요없는 경우가 많기 때문에
       연산이 많거나 / 수학적으로 유리하다.

    ※ 이렇게 설명을 했지만 잘 모르겠다면 그냥 0xFEFF사용하면 본전

    */
    WORD BOM = 0xFEFF;
    DWORD dwBytes = 0;
    DWORD dwRead;

    /*
    CreateFile(): 파일 입출력 장치를 만들거나 읽어 오고 사용할 수 있는 핸들 변환
    */

    file = CreateFile
    (
        fileName,                   // 생성하거나 열 파일의 이름
        GENERIC_WRITE,              // 파일 접근 타임
        0,                          // 0 -> 공유 X -> 다른 객체 X
        NULL,                       // 상속 여부
        CREATE_ALWAYS,              // 새로운 파일 생성 -> 동일한 파일 존재 -> 덮어쓰기
        FILE_ATTRIBUTE_NORMAL,      // 파일에 대한 속성 값으로 일반적인 속성을 정의하지 않겠다.
        NULL                        // 형태에 대한 정의
    );

    // return 0 / while(1) / -1
    // INVALID_HANDLE_VALUE : 주로 초기화 사용이 된다. -> 일반적으로 -1로 정의한다.
    if (file == INVALID_HANDLE_VALUE)
    {
        MessageBox(_hWnd, "생성 파일 에러", "에러", MB_OK);
    }
    else
    {
        // 일반적인 형태
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
    // 8192 : 클라에서 사용하는 최상위 비트 -> 서버 -> 소켓 버퍼라고 부른다.
    // 어셈블러 -> byte(1 ~ 8) / word(1 ~ 16) / dword(4 ~ 32) / qword(8 ~ 64)
    // ㄴ 1비트 (이진법) -> 8비트 (1 바이트) -> 2바이트 (1 word)
    TCHAR* buf[8192];
    ZeroMemory(buf, sizeof(buf));

    HANDLE file;
    DWORD dwBytes;

    file = CreateFile
    (
        fileName,                   
        GENERIC_WRITE,              // 일반적인 형태로 읽어들이겠다.         
        0,                          
        NULL,                       
        OPEN_EXISTING,              // 파일이 존재할때만 연다.
        FILE_ATTRIBUTE_NORMAL,      
        NULL                        
    );

    if (file == INVALID_HANDLE_VALUE)
    {
        MessageBox(_hWnd, "생성 파일 에러", "에러", MB_OK);

        return "";
    }
    else
    {
        ReadFile(file, buf, 8192, &dwBytes, NULL);
        CloseHandle(file);
    }
    //// 공백을 고려해봐야 한다.
    //return string(buf);
}

// 핵심
string JsonSaveLoader::loadStringWidthFileStream(char* fileName)
{
    ifstream fileIn;

    fileIn.open(fileName, ios::in);

    /*
    ios::in -> 파일 개방(읽기만 가능한 상태로)
    ios::out -> 파일 개방(쓰기만 가능한 상태로)
    ios::ate -> 파일의 끝으로 파일 포인터 이동 시킨다.(파일을 개방할 때)
    ios::app -> 데이터 추가 (파일의 뒷쪽부터)
    ios::binary -> 바이너리 모드로 개방
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
        MessageBox(_hWnd, "데이터가 없다", "경고", MB_OK);
        return NULL;
    }

    Json::Reader reader;
    Json::Value root;

    // parsing (파싱) : 특정 문서를 읽어 들여서 이를 다른 프로그램이나 서브 루틴이 사용할 수 있는 내부 표현 방식으로 변환해 주는 것
    // parse : 파싱을 하는 프로세서
    bool parsingRet = reader.parse(jsonStr, root);
    return Json::Value();
}

JsonSaveLoader::JsonSaveLoader()
{
}

JsonSaveLoader::~JsonSaveLoader()
{
}
