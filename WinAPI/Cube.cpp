#include "stdafx.h"
#include "Cube.h"

HRESULT Cube::init(void)
{
	_camera.FOV = PI / 1.2f;
	_camera.distance = (WINSIZE_Y / 2) / tan(_camera.FOV / 2.0f);
	_camera.pan = PI / 2.f;
	_camera.tilt = 0.f;
	_points[0] = Vector3D(0, 0, 0);
	_points[1] = Vector3D(0, 0, 40);
	_points[2] = Vector3D(00, 40, 00);
	_points[3] = Vector3D(00, 40, 40);
	_points[4] = Vector3D(40, 00, 00);
	_points[5] = Vector3D(40, 00, 40);
	_points[6] = Vector3D(40, 40, 40);
	_points[7] = Vector3D(40, 40, 00);
	/*for (int i = 0; i < 50; i++)
	{
		_grid[i]._z = 0;
		_grid[i]._x = -400;
		_grid[i]._y = -400 + 40 * i;
	}
	for (int i = 50; i < 100; i++)
	{
		_grid[i]._z = 0;
		_grid[i]._x = 400;
		_grid[i]._y = -400 + 40 * i;
	}*/
	_camera.position = Vector3D(20, -100, 20);
	return S_OK;
}

void Cube::release(void)
{
}

void Cube::update(void)
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_camera.tilt -= 0.1f;
		_camera.position._z = 120 * sin(-_camera.tilt);
		_camera.position._y = 120 * cos(-_camera.tilt);
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_camera.tilt += 0.1f;
		_camera.position._z = 120 * sin(-_camera.tilt);
		_camera.position._y = 120 * cos(-_camera.tilt);
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_camera.pan -= 0.1f;
		_camera.position._y = 120 * sin(-_camera.tilt);
		_camera.position._x = 120 * cos(-_camera.tilt);
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_camera.pan += 0.1f;
		_camera.position._y = 120 * sin(-_camera.tilt);
		_camera.position._x = 120 * cos(-_camera.tilt);
	}
	for (int i = 0; i < 8; i++)
	{
		_worldToCamera[i]._x = cos(_camera.pan)*(_points[i]._x - _camera.position._x) + sin(_camera.pan) * (_points[i]._y - _camera.position._y);
		_worldToCamera[i]._y = -sin(_camera.pan) * sin(_camera.tilt) * (_points[i]._x - _camera.position._x) + cos(_camera.pan) * sin(_camera.tilt) * (_points[i]._y - _camera.position._y)
		 + (-cos(_camera.tilt)) * (_points[i]._z - _camera.position._z);
		_worldToCamera[i]._z = -sin(_camera.pan) * cos(_camera.tilt) + cos(_camera.pan) * cos(_camera.tilt) * (_points[i]._y - _camera.position._y) + sin(_camera.tilt) * (_points[i]._z - _camera.position._z);
	}
    for (int i = 0; i < 8; i++)
    {
        _projectedPoints[i].x = _camera.distance * (_worldToCamera[i]._x / _worldToCamera[i]._z) + WINSIZE_X / 2;
        _projectedPoints[i].y = _camera.distance * (_worldToCamera[i]._y / _worldToCamera[i]._z) + WINSIZE_Y / 2;
    }
	//for (int i = 0; i < 100; i++)
	//{
	//	_worldToCameraGrid[i]._x = cos(_camera.pan) * (_grid[i]._x - _camera.position._x) + sin(_camera.pan) * (_grid[i]._y - _camera.position._y);
	//	_worldToCameraGrid[i]._y = -sin(_camera.pan) * sin(_camera.tilt) * (_grid[i]._x - _camera.position._x) + cos(_camera.pan) * sin(_camera.tilt) * (_grid[i]._y - _camera.position._y)
	//		+ (-cos(_camera.tilt)) * (_grid[i]._z - _camera.position._z);
	//	_worldToCameraGrid[i]._z = -sin(_camera.pan) * cos(_camera.tilt) + cos(_camera.pan) * cos(_camera.tilt) * (_grid[i]._y - _camera.position._y) + sin(_camera.tilt) * (_grid[i]._z - _camera.position._z);
	//}
	//for (int i = 0; i < 100; i++)
	//{
	//	_projectedGrid[i].x = _camera.distance * (_worldToCameraGrid[i]._x / _worldToCameraGrid[i]._z) + WINSIZE_X / 2;
	//	_projectedGrid[i].y = _camera.distance * (_worldToCameraGrid[i]._y / _worldToCameraGrid[i]._z) + WINSIZE_Y / 2;
	//}
}

void Cube::render(void)
{
	HPEN myPen = CreatePen(CW_DEFAULT, 1, RGB(255, 255, 255));
	HPEN gridPen = CreatePen(CW_DEFAULT, 1, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(getMemDC(), myPen);
	LineMake(getMemDC(), _projectedPoints[0].x, _projectedPoints[0].y, _projectedPoints[1].x, _projectedPoints[1].y);
	LineMake(getMemDC(), _projectedPoints[0].x, _projectedPoints[0].y, _projectedPoints[2].x, _projectedPoints[2].y);
	LineMake(getMemDC(), _projectedPoints[0].x, _projectedPoints[0].y, _projectedPoints[4].x, _projectedPoints[4].y);
	LineMake(getMemDC(), _projectedPoints[1].x, _projectedPoints[1].y, _projectedPoints[3].x, _projectedPoints[3].y);
	LineMake(getMemDC(), _projectedPoints[1].x, _projectedPoints[1].y, _projectedPoints[5].x, _projectedPoints[5].y);
	LineMake(getMemDC(), _projectedPoints[2].x, _projectedPoints[2].y, _projectedPoints[3].x, _projectedPoints[3].y);
	LineMake(getMemDC(), _projectedPoints[2].x, _projectedPoints[2].y, _projectedPoints[7].x, _projectedPoints[7].y);
	LineMake(getMemDC(), _projectedPoints[3].x, _projectedPoints[3].y, _projectedPoints[6].x, _projectedPoints[6].y);
	LineMake(getMemDC(), _projectedPoints[4].x, _projectedPoints[4].y, _projectedPoints[5].x, _projectedPoints[5].y);
	LineMake(getMemDC(), _projectedPoints[4].x, _projectedPoints[4].y, _projectedPoints[7].x, _projectedPoints[7].y);
	LineMake(getMemDC(), _projectedPoints[5].x, _projectedPoints[5].y, _projectedPoints[6].x, _projectedPoints[6].y);
	LineMake(getMemDC(), _projectedPoints[6].x, _projectedPoints[6].y, _projectedPoints[7].x, _projectedPoints[7].y);
	SelectObject(getMemDC(), gridPen);
	/*for (int i = 0; i < 50; i++)
	{
		LineMake(getMemDC(), _projectedGrid[i].x, _projectedGrid[i].y, _projectedGrid[50 + i].x, _projectedGrid[50 + i].y);
	}*/
	SelectObject(getMemDC(), oldPen);
	DeleteObject(myPen);
}

void Cube::rotate()
{
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
