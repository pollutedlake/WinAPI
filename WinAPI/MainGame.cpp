#include "Stdafx.h"
#include "MainGame.h"
#include "ResourcesClass.h"
HRESULT MainGame::init(void)
{
	GameNode::init(true);
#if MAIN == CLASS
	_start = new StartScene;
	_start->init();

	_second = new SecondScene;
	_second->init();

	//_currentScene -> �õ��� �ȵǸ� �׳� ���� ��ü�� �ȵȴ� -> ���� ������ �ʿ䰡 ����
	_currentScene = _start;

	//assert: ���α׷��� �����Ŵ
	//C
	assert(_currentScene != nullptr, "MainGame �ʱ�ȭ �κп��� ��� ��Ʈ ���� �߻�");
	//C++
	//static_assert(): 


	/*
	��assert

	�������� ���� ���

	����� ��忡�� �����ϴ� ���� ����� �Լ�
	�������� ��忡���� �������� �ʴ´�.

	-assert �Լ��� �ɸ��� �Ǹ� ���� �߻� ��ġ / �� ���õ� ���� ������ �� �� �ִ�.
	   ��Expression -> false -> assert error

	��κ��� ������ true�϶��� ���������� assert�� false�϶� �����Ѵ�.
	���׷��� ������ �Ͼ�� �ȵǴ� ������ �ƴ϶� �� �Ͼ�� �ϴ� ������ ����ؾ� �Ѵ�.

	Ex) assert(A != NULL);
	   ��A�� NULL�� �ƴϸ� true �� ������ �ǹǷ� �н�
	   ��A�� NULL�� ������ false �� ������ �ǹǷ� assert error

	assert(): "C" -> ������ Ÿ���� ���� ���α׷��� ���� ��Ű�� ������ �ľ��ϰڴ�.
	static_assert(): "C++" -> ������ �߿� ������ �ľ�

	������ �߿� ������ Ȯ���ϱ� ���ؼ� ������� �־���� �Ѵ�.

	*/

#elif MAIN == ASSIGNMENT
	//_assignment = new CTW_Scene;			// ĳ���� ��¤��, �̴ϸ� ����
	//_assignment = new RacingGame;			// ���̰̽���
	//_assignment = new BlackHole;			// ��Ȧ
	//_assignment = new Cube;
	//_assignment = new TileMap;

	/*std::shared_ptr<Rocket> PlayerA = std::make_shared<Rocket>();
	std::shared_ptr<Rocket> PlayerB = PlayerA->get_shared_ptr();*/

	//PlayerA.use_count();
#elif MAIN == SHOOTINGGAME
	IMAGEMANAGER->addImage("���� ��", "Resources/Images/ShootingGame/ShootingBG.bmp", WINSIZE_X, WINSIZE_Y);
	_assignment = new Rocket;
	_em = new EnemyManager;
	_em->init();
	_assignment->init();
#endif
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
#if MAIN == CLASS
	SAFE_DELETE(_start);
	SAFE_DELETE(_second);

#elif MAIN == ASSIGNMENT
	_assignment->release();
	SAFE_DELETE(_assignment);
#elif MAIN == SHOOTINGGAME
	_assignment->release();
	_em->release();
	SAFE_DELETE(_assignment);
#endif
}

void MainGame::update(void)
{
	GameNode::update();
#if MAIN == CLASS
	_currentScene->update();

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))_currentScene = _second;
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))_currentScene = _start;

#elif MAIN == ASSIGNMENT
	_assignment ->update();
#elif MAIN == SHOOTINGGAME
	_assignment->update();
	_em->update();
#endif	

}

void MainGame::render(void)
{
	// PatBlt(): �簢�� �ȿ� ������ �귯���� ä��� �Լ�
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	// ========================================================
#if MAIN == CLASS
	_currentScene->render();
	TCHAR* fontName = TEXT("�޸ձ���");
	LPCWSTR test[] = {L"��\n��,", L"����\n", L"�ڻ����̾�\n������"};
	LPCWSTR test2 = L"��\n��";
	char* test3 = "��\n��";
	FONTMANAGER->drawText(getMemDC(), WINSIZE_X / 2, WINSIZE_Y / 2, fontName, 25, 500, test, sizeof(test) / sizeof(*test), NULL, RGB(0, 0, 255));

#elif MAIN == ASSIGNMENT
	_assignment->render();
#elif MAIN == SHOOTINGGAME
	IMAGEMANAGER->findImage("���� ��")->render(getMemDC());
	_assignment->render();
	_em->render();
#endif
	// ========================================================
	this->getBackBuffer()->render(getHDC());
}

/*
1. ��ȹ�� ����

2. ��ȹ�� �긴��

-����, ������

- ����
- ������Ʈ ��ǥ/�����ǵ�
- 00�帣�� 00������ ���۷������� ���� ����
- 0000�� ��̸� �������Ϸ� ��

- ���� �Ұ�
- ���Ӹ�, ���ӼҰ�, ����Ư¡
- �����ο�, ���� ����, ���� ���, ��� ��ų
- ���߰�ȹ(����)
- ���()

-���/ȸ��
- 00��� �ɷ� ȹ��
- ������, �����, ������ �κ�, �����н��� ����� ������ �ڷ�(����/��ũ/���� ��)
- ����/����� ������ �κ�

- �÷ο� ��Ʈ

- Ŭ���� ������

- ���� ����

- ���� ��
���־� ��Ʃ��� ���� ���伥���� �����������α׷�
15��~20��

����1. ĳ���� ���� �� ���

- �ʼ� : �̹��� -> ��� / ü�¹� / �÷��̾� (���, ����, ���), ��(���, ����, �ǰ�)

- �⺻ ������ ��������ó�� �� / ��� ��ġ
�� + ü�¹�

- �÷��̾�� ���� �� �� �� �� �ְ� ���� ���� �� �ǰ� ����� �����Ѵ�.
�� �� : ����ƺ�

- �÷��̾�� ��� ���� < - > ���� ���� On / Off ��ɸ� (�̵� X)

- ����, ���, �ǰ� ���� �߻��ϸ� ��Ȳ�� �´� ����� ȭ�鿡 ������ �Ѵ�.
�� ����, ������, ġ��Ÿ ��

- �������� ǥ���Ѵ�.
�������� �� �� ������ �غ���.
*/