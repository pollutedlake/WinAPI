#pragma once

class SceneManager;

class Scene
{
	// ��� ���� ����
	// friend�� �����ִ� ��ü�鿡�Ը� ������ ����
	/*
	friend : �� �״�� ģ��
	�� ������ ��� ���� / ȿ������ ������ ������ �� ���� �����Ѵ�.
	�� ���(����)�� ģ��(����)�� ����
	�� ���� ���� �������� ������ ���� �ʴ´�.
		�� private���� ��� ������ �����ϱ� ������ �� ���� ȿ���� ������ �� �ݴ��� ���ġ Ű����

	- Ŭ���� + �Լ�
	�� �����̳� / ����(�Լ�)

	- friend�� �ܹ���

	- friend �Ӽ��� ����� Y / N ?
	�� N : friend�� �ܹ����̱� ������ ����� �ȵȴ�. ����� �����
	*/
	friend SceneManager;
private:

	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void exit() = 0;

protected:
	

public:

	Scene();
	virtual ~Scene();
};

