#include "stdafx.h"
#include "Cube.h"

HRESULT Cube::init(void)
{
	_camera.FOV = PI / 2.0f;
	_camera.distance = (WINSIZE_Y / 2) / tan(_camera.FOV / 2);
	_points[0] = Vector3D(-20, -20, -20);
	_points[1] = Vector3D(-20, -20, 20);
	_points[2] = Vector3D(-20, 20, -20);
	_points[3] = Vector3D(-20, 20, 20);
	_points[4] = Vector3D(20, -20, -20);
	_points[5] = Vector3D(20, -20, 20);
	_points[6] = Vector3D(20, 20, 20);
	_points[7] = Vector3D(20, 20, -20);
	return S_OK;
}

void Cube::release(void)
{
}

void Cube::update(void)
{
	
}

void Cube::render(void)
{
	
}

void Cube::rotate()
{
}

//�������
Matrix4x4 Cube::getProjectionMatrix()
{
    //Xndc���� ���ϱ� ���� ��Ⱦ�� 
    static float invA = (float)WINSIZE_Y / (float)WINSIZE_X;
    //�������� �Ÿ�
    static float d = 1.f / tanf(_camera.FOV * 0.5f);
    //������ ī�޶��� �Ÿ�
    static float n = 5.5f;
    //������ ī�޶��� �Ÿ�
    static float f = 1000.f;
    //k�� l�� ���ϱ� ���Ѱ�(���ϱ⺸�� �������� ����� ũ�� ��� �̸� ������)
    float invNF = 1.f / (n - f);
    
    float k = f * invNF;
    float l = f * n * invNF;
    return Matrix4x4(
        Vector4::UnitX * invA * d,
        Vector4::UnitY * d,
        Vector4(0.f, 0.f, k, -1.f),
        Vector4(0.f, 0.f, l, 0.f));
}
