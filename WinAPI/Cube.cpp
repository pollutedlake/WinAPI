#include "stdafx.h"
#include "Cube.h"

HRESULT Cube::init(void)
{
	_camera.FOV = PI / 3.f;
	_camera.distance =  1.f / tan(_camera.FOV / 2);
	_camera.pan = 0.f;
	_camera.tilt = 0.f;

	_points[0] = Vector3D(-1, -1, -1);
	_points[1] = Vector3D(-1, -1, 1);
	_points[2] = Vector3D(-1, 1, -1);
	_points[3] = Vector3D(-1, 1, 1);
	_points[4] = Vector3D(1, 1, 1);
	_points[5] = Vector3D(1, 1, -1);
	_points[6] = Vector3D(1, -1, 1);
	_points[7] = Vector3D(1, -1, -1);
	_camera.position = Vector3D(0, -20, 0);
	for (int i = 0; i < 20; i++)
	{
		_grid[i] = Vector3D(-20, -20 + 2 *i, -1);
		_grid[i + 20] = Vector3D(20, -20 + 2 * i, -1);
		_grid[i + 40] = Vector3D(-20 + 2 * i, -20, -1);
		_grid[i + 60] = Vector3D(-20 + 2 * i, 20, -1);
	}
	return S_OK;
}

void Cube::release(void)
{
} 

void Cube::update(void)
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_camera.pan -= 0.01f;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_camera.pan += 0.01f;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_camera.tilt -= 0.01f;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_camera.tilt += 0.01f;
	}
	float _ry = cos(_camera.tilt) * -20;
	_camera.position._z = sin(_camera.tilt) * -20;
	_camera.position._y = _ry;
	float _rx = cos(_camera.pan) * _camera.position._x + (-sin(_camera.pan) * _camera.position._y);
	_camera.position._y = sin(_camera.pan) * _rx + cos(_camera.pan) * _camera.position._y;
	/*float _rx = -sin(_camera.pan) * -20;
	_camera.position._y = cos(_camera.pan) * -20;
	_camera.position._x = _rx;*/
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_camera.FOV -= 0.01f;
		_camera.distance = 1.f / tan(_camera.FOV / 2);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_camera.FOV += 0.01f;
		_camera.distance = 1.f / tan(_camera.FOV / 2);
	}
	for (int i = 0; i < 8; i++)
	{
		_worldToCamera[i] = worldToCamera(_points[i]);
	}
	for (int i = 0; i < 8; i++)
	{
		_projectedPoints[i] = projectionTransform(_worldToCamera[i]);
	}
	for (int i = 0; i < 80; i++)
	{
		_worldToCameraGrid[i] = worldToCamera(_grid[i]);
	}
	for (int i = 0; i < 80; i++)
	{
		_projectedGrid[i] = projectionTransform(_worldToCameraGrid[i]);
	}
}

void Cube::render(void)
{
	HPEN myPen = CreatePen(CW_DEFAULT, 1, RGB(255, 255, 255));
	HPEN gridPen = CreatePen(CW_DEFAULT, 1, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), gridPen);
	for (int i = 0; i < 20; i++)
	{
		LineMake(getMemDC(), WINSIZE_X / 2 + _projectedGrid[i]._x * 300, WINSIZE_Y / 2 + _projectedGrid[i]._y * 300, WINSIZE_X / 2 + _projectedGrid[i + 20]._x * 300, WINSIZE_Y / 2 + _projectedGrid[i + 20]._y * 300);
		LineMake(getMemDC(), WINSIZE_X / 2 + _projectedGrid[i + 40]._x * 300, WINSIZE_Y / 2 + _projectedGrid[i + 40]._y * 300, WINSIZE_X / 2 + _projectedGrid[i + 60]._x * 300, WINSIZE_Y / 2 + _projectedGrid[i + 60]._y * 300);
	}
	SelectObject(getMemDC(), myPen);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[0]._x * 300, WINSIZE_Y / 2 + _projectedPoints[0]._y * 300, WINSIZE_X / 2 + _projectedPoints[1]._x * 300, WINSIZE_Y / 2 + _projectedPoints[1]._y * 300);
  	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[0]._x * 300, WINSIZE_Y / 2 + _projectedPoints[0]._y * 300, WINSIZE_X / 2 + _projectedPoints[2]._x * 300, WINSIZE_Y / 2 + _projectedPoints[2]._y * 300);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[0]._x * 300, WINSIZE_Y / 2 + _projectedPoints[0]._y * 300, WINSIZE_X / 2 + _projectedPoints[7]._x * 300, WINSIZE_Y / 2 + _projectedPoints[7]._y * 300);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[1]._x * 300, WINSIZE_Y / 2 + _projectedPoints[1]._y * 300, WINSIZE_X / 2 + _projectedPoints[3]._x * 300, WINSIZE_Y / 2 + _projectedPoints[3]._y * 300);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[1]._x * 300, WINSIZE_Y / 2 + _projectedPoints[1]._y * 300, WINSIZE_X / 2 + _projectedPoints[6]._x * 300, WINSIZE_Y / 2 + _projectedPoints[6]._y * 300);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[2]._x * 300, WINSIZE_Y / 2 + _projectedPoints[2]._y * 300, WINSIZE_X / 2 + _projectedPoints[3]._x * 300, WINSIZE_Y / 2 + _projectedPoints[3]._y * 300);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[2]._x * 300, WINSIZE_Y / 2 + _projectedPoints[2]._y * 300, WINSIZE_X / 2 + _projectedPoints[5]._x * 300, WINSIZE_Y / 2 + _projectedPoints[5]._y * 300);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[3]._x * 300, WINSIZE_Y / 2 + _projectedPoints[3]._y * 300, WINSIZE_X / 2 + _projectedPoints[4]._x * 300, WINSIZE_Y / 2 + _projectedPoints[4]._y * 300);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[4]._x * 300, WINSIZE_Y / 2 + _projectedPoints[4]._y * 300, WINSIZE_X / 2 + _projectedPoints[5]._x * 300, WINSIZE_Y / 2 + _projectedPoints[5]._y * 300);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[4]._x * 300, WINSIZE_Y / 2 + _projectedPoints[4]._y * 300, WINSIZE_X / 2 + _projectedPoints[6]._x * 300, WINSIZE_Y / 2 + _projectedPoints[6]._y * 300);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[5]._x * 300, WINSIZE_Y / 2 + _projectedPoints[5]._y * 300, WINSIZE_X / 2 + _projectedPoints[7]._x * 300, WINSIZE_Y / 2 + _projectedPoints[7]._y * 300);
	LineMake(getMemDC(), WINSIZE_X / 2 + _projectedPoints[6]._x * 300, WINSIZE_Y / 2 + _projectedPoints[6]._y * 300, WINSIZE_X / 2 + _projectedPoints[7]._x * 300, WINSIZE_Y / 2 + _projectedPoints[7]._y * 300);
	SelectObject(getMemDC(), oldPen);
	DeleteObject(myPen);
}

void Cube::rotate()
{
}

Vector3D Cube::worldToCamera(Vector3D worldPoint)
{
	Vector3D cameraPoint;
	cameraPoint._x = cos(_camera.pan) * (worldPoint._x - _camera.position._x) + sin(_camera.pan) * (worldPoint._y - _camera.position._y);
	cameraPoint._y = -sin(_camera.pan) * sin(_camera.tilt) * (worldPoint._x - _camera.position._x) + 
					cos(_camera.pan) * sin(_camera.tilt) * (worldPoint._y - _camera.position._y) + 
					(-cos(_camera.tilt) * (worldPoint._z - _camera.position._z));
	cameraPoint._z = -sin(_camera.pan) * cos(_camera.tilt) * (worldPoint._x - _camera.position._x) +
		cos(_camera.pan) * cos(_camera.tilt) * (worldPoint._y - _camera.position._y) +
		sin(_camera.tilt) * (worldPoint._z - _camera.position._z);
	return cameraPoint;
}

Vector3D Cube::projectionTransform(Vector3D cameraPoint)
{
	Vector3D projectedPoint;
	projectedPoint._x = _camera.distance * cameraPoint._x/(cameraPoint._z + _camera.distance);
	projectedPoint._y = _camera.distance * cameraPoint._y/(cameraPoint._z + _camera.distance);
	projectedPoint._z = 1;
	return projectedPoint;
}

//투영행렬
Matrix4x4 Cube::getProjectionMatrix()
{
    //Xndc값을 구하기 위한 종횡비 
    static float invA = (float)WINSIZE_Y / (float)WINSIZE_X;
    //근평면과의 거리
    static float d = 1.f / tanf(_camera.FOV * 0.5f);
    //근평면과 카메라의 거리
    static float n = 5.5f;
    //원평면과 카메라의 거리
    static float f = 1000.f;
    //k와 l을 구하기 위한값(곱하기보다 나눗셈이 비용이 크게 드니 미리 나눠둠)
    float invNF = 1.f / (n - f);
    
    float k = f * invNF;
    float l = f * n * invNF;
    return Matrix4x4(
        Vector4(invA * d, 0, 0, 0),
        Vector4(0, d, 0, 0),
        Vector4(0.f, 0.f, k, -1.f),
        Vector4(0.f, 0.f, l, 0.f));
}
