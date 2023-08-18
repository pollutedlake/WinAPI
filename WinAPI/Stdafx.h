// stdafx.h : ���� ��������� ���� ��������� �ʴ� ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������ ��� �ִ� ���� �����Դϴ�.

#pragma once
// ��� ����
#pragma warning(disable : 4005)
// 4005 : DXGI �� �׷��� �������̽����� ��ũ�� �����Ͽ� ��µǴ� ���

/*
�� Stdafx

- MS�� ���־� ��Ʃ����� �̿��Ͽ� ������Ʈ�� ����� �����Ǵ� Ŭ�����̴�.
�� �� ģ���� �ǹ��ϴ� �ٴ� ǥ�� ���ø����̼� �����ӿ�ũ�� Ʋ

- MS���� �����ڵ��� �ɷ� ����� ���� ������ PCH ����
�� ���� ���̴� �������� ������� �̸� ������ �صξ� ���� �ٽ� ���������� �ʰ� ����ϰ� �ȴ�.

- ���߿� �ʱ� ���� �ܰ迡���� �� �ʿ伺�� �� �������� ��� ������ ũ�Ⱑ Ŀ���ų� ���� ���� ������ Ȱ�뵵 �� ȿ���� �޻�¡��
*/

// SDKDDKVER.h�� ���α׷����� ������ OS�� ���� or ���̺귯���� ���� Windows ������� �ڵ忡 ���Ե� �Լ� / ��� ���� �����ϴµ� ��� �Ѵ�.
#include<SDKDDKVER.h>

//#include "targetver.h"					// OS�� �°� �ڵ带 ��ȯ����
// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// ��GDI+�� ����Ϸ��� ������Ͽ��� �����;� �Ѵ�.
//#include <ole2.h>
#define WIN32_LEAN_AND_MEAN
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

// ���̺귯�� �߰�
#pragma comment (lib, "msimg32.lib")

// Windows ��� ����
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
// stdlib: C����� ǥ�� ���̺귯�� �Լ��� ��� ����
#include <stdlib.h>
// C���� �޸� �Ҵ��� �� ����Ѵ�.
#include <malloc.h>
// �޸� ���� ��� ����
// ��memset / memcpy�� ����ϴ� �������
#include <memory.h>
/*
�� ���ڿ� ��

- �����쿡�� ����� ���ڿ� ��� ����(����) �� (TextOut, DrawText, wsprintf ���)
�� �⺻������ �����ڵ�

MBCS(��Ƽ ����Ʈ ĳ���� ��)

- ������ ����ϴ� ��Ƽ����Ʈ ������ ���ڿ��� ���Ѵ�.
- ��Ƽ����Ʈ �ڵ�� ���� ���� �ƽ�Ű �ڵ忡 ���ԵǴ� ���ڴ� 1����Ʈ�� ǥ���ϰ�
  ���Ե��� �ʴ� ���ڴ� 2����Ʈ�� ó���Ѵ�.

WBCS(���̵� ����Ʈ ĳ���� ��)

- ��� ���ڸ� 2����Ʈ�� ó���ϸ� �����ڵ� ����̴�.

�� �����ڵ�� ��Ƽ����Ʈ�� ���

- VS������ ���߽� ��Ƽ / �����ڵ带 ���� �⺻������ ������ ����� �Ѵ�.

- �����ڵ��� ��쿡�� ���ڿ��� ����ǥ�� ���ΰ� �� �տ� L�� �ٿ��� (L"") �̶�� ǥ���Ѵ�.

- ��Ƽ����Ʈ ���� ��쿡�� �׳� ""�� ����ϸ� �ȴ�.

- �����ڵ�� ���ߵ� ���α׷��� ��Ƽ����Ʈ�� �̽��Ϸ��� �̵� ���ڿ��� ǥ�� ����� �ٽ� ������� �ϱ� ������ �ſ� �����ϴ�.
�� �׷��� _T��ũ�θ� ����ؾ� �Ѵ�.

- ���ڿ��� ����ǥ�� ���ΰ� �����ڵ忡�� ����� "L" ��� "_T"�� ����ϸ� ��ũ�ΰ� �˾Ƽ� ���� ȯ�濡 �°� ġȯ�� �ش�.
*/
#include <tchar.h>
// stdio : ǥ�� ����� ��� ����
#include <stdio.h>
#include <time.h>

//! C++ ��Ÿ�� ��� ����
#include <iostream>
/*
- C++11���� �߰��� �ð� ���� ���̺귯��(STL)
�� ���� C ��Ÿ�ӿ��� �����ϴ� time �Լ����� �پ��� / Ȯ��� ��� �����Ѵ�.
�� ���� : ���е��� ����. (���� �и� �� ����)
�� time �Լ��� �� ������ ���� ������ �����ϱ� ������ ���е��� ������ �� �ִ�.
�� OS�� ���������� ������ �Ѵ�.

*/
#include <chrono>
#include <random>
#include <memory>
#include <vector>
#include<map>
#include<string.h>
// ���� ģ����
#include <algorithm>
// �Լ� �����͸� ����ó�� �߰� ���� �� �ִ�.
// �� bind : Ư�� ���ڿ� ���ؼ��� �Լ��� �����Ű�� ���� �� / Ư�� ���ڿ� Ư�� �Լ��� ���� ���� ��
// �� �Լ� ������ -> �̺�Ʈ -> ��������Ʈ -> �׼� Ʈ���� / ������ ����(������ ���ν���)
#include <functional>
// unordered_map : Hash �ڷᱸ��
// �� �Ϲ��� ��Ȳ���� map���� �˻��ӵ��� �� ������.
// �� �˻� �ӵ��� ���� ������ �ߺ��� �����͸� ������� �ʱ� ������
// �� ��, ���� �����Ͱ� ���� �� (key), �ؽ� �浹�� �߻��� ������ ����� ������ ���� ���ϰ� �߻��Ѵ�.
#include <unordered_map>
// cassert : C++ ���α׷����� ��� -> �� ����
#include<cassert>
// bitset : ��Ʈ ������ ���� ���� ������ �ִ� �Լ��� �����ϴ� STL
// �� reset(), set, flip(), all(), any(), size() ���....
#include<bitset>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;
//using std::vector;
//using std::bitset;
//using std::pair;
//using std::map;
//using std::string;
//using std::cout;
//using std::make_pair;

/*
//! D2D/D3D �������
#include <D2D1.h>
#include <d2d1helper.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <d3d11shader.h>
#include <dinput.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

ID2D1Factory* _ID2DFactory = nullptr;
ID2D1HwndRenderTarget* _ID2DRanderTarget = nullptr;*/

// # ����� ���� ��� ���� #
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "TimeManager.h"
#include "EventManager.h"
#include"Utils.h"

// # �̱��� #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define EVENTMANAGER EventManager::getSingleton()

// # ��ũ�� # (������â �ʱ�ȭ)
#define WINNAME					(LPTSTR)(TEXT("WindowsAPI"))
#define WINSTART_X				400
#define WINSTART_Y				100
#define WINSIZE_X				1280
#define WINSIZE_Y				800

#define PI                       3.141592
// WS_CAPTION : Ÿ��Ʋ�ٸ� ������ ���� �ɼ�
// WS_SYSMENU : ���� ǥ���ٿ� ��Ʈ�� �޴� ���� â
#define WINSTYLE				WS_CAPTION | WS_SYSMENU

// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

// # ���� ���� #
// extern Ű����� �ٸ� ��� / cpp���� ������ �����ؼ� ���� ���� ����Ѵ�.
// �� ��ü
// �⺻������ ���� ������ Ű���带 �����ص� �⺻������ externȭ �Ǵ� ��찡 ����.
// static�� ���� �߿� static �Ӽ��� ������ �� ������ extern�� �ѹ� �����ϸ� �ٲ� �� ����.
extern HINSTANCE				_hInstance;
extern HWND						_hWnd;
// X ��ǥ��  Y ��ǥ�� ����� ��ǥ�� ������ �� ����� �Ѵ�.
extern POINT					_ptMouse;
// extern ID2D1HwndRenderTarget* _ID2DRanderTarget = nullptr;  Ŭ���� ������ ��� nullptr�� �ƴ϶� ��ü�� ��Ȯ�� �������� externȭ�ȴ�.
