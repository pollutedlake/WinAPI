#pragma once
#include "GameNode.h"

struct Vector3D
{
	float _x;
	float _y;
	float _z;
	Vector3D() {}
	Vector3D(float x, float y, float z) {_x = x; _y = y; _z = z;}
};
struct Vector4 {
	float _x;
	float _y;
	float _z;
	float _w;
	Vector4() {}
	Vector4(float x, float y, float z, float w) { _x = x; _y = y; _z = z; _w = w; }
};

struct Matrix4x4 {
	Vector4 _firstRow;
	Vector4 _secondRow;
	Vector4 _thirdRow;
	Vector4 _fourthRow;
	Matrix4x4() {}
	Matrix4x4(Vector4 firstRow, Vector4 secondRow, Vector4 thirdRow, Vector4 fourthRow) { _firstRow = firstRow; _secondRow = secondRow; _thirdRow = thirdRow; _fourthRow = fourthRow; }
};

struct Camera
{
	Vector3D position;
	float pan;
	float tilt;
	float FOV;
	float distance;
};

class Cube : public GameNode
{
private:
	Vector3D _points[8];
	Vector3D _grid[80];
	Vector3D _projectedGrid[80];
	Vector3D _worldToCamera[8];
	Vector3D _worldToCameraGrid[80];
	Camera _camera;
	Vector3D _projectedPoints[8];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void rotate();

	Vector3D worldToCamera(Vector3D worldPoint);
	Vector3D projectionTransform(Vector3D cameraPoint);

	Matrix4x4 getProjectionMatrix();

	Cube() {}
	virtual ~Cube() {}
};

