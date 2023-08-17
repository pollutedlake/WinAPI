#pragma once

// ����ȭ ��Ű�� ���� ���� -> ������ ����� �����ϸ� ����.

// ��׸� 1���� ����
#define DEG_TO_RAD       0.017453f
#define PI               3.141592653f
#define PI_2             6.283185308f

/*
- �ݿø� ���� (Rounding Error)

- �ε��Ҽ��� �⺻������ �Ǽ��� ��Ȯ�ϰ� ǥ���ϴ°� �Ұ���
�� ������ ���������� �Ǽ��� ������ �ݸ鿡 �� �Ǽ��� ������ ��Ʈ�� ǥ���� �ؾ� �ϱ� ����
�� �׷��� ������ ��ǻ�ʹ� ��¿ �� ���� �ٻ簪���� ó���� �Ѵ�.

- �̰� �ε��Ҽ��� �ݿø� ����
�� ��ǻ�ʹ� �Ǽ��� �������� ���·� ����
�� �̷��� Ư¡ ������ ���� ������ �߻��ϰ� ������ ����� ���ؼ��� ������� �ݵ�� �ʿ��ϴ�.

- 2D ��ǥ�迡���� ü���� ��������� ���� �� ������ 3D������ ü���� Ȯ �Ǵ� �κ�

*/

// �Ǽ� -> ����
#define FLPAT_EPSILON    0.001f

/*
- C++ ĳ���� �����ڴ� 4����

1. reinterpret_cast
�� ������ ����ϸ� �����Ͱ� �޸𸮻� �迭�Ǵ� ������ �������� ���� �� �ִ�.
�� �̴� ���α׷��Ӱ� �ǵ��� ��Ȳ�� ��

*/


#define FLOAT_TO_INT(f1)		static_cast<int>(f1 + FLOAT_EPSIOLON)

// �� �Ǽ��� ������ ��
// �� ���⼭ ���� ���밪�� �Ҽ��� ���� ���밪 ��ȯ
#define FLOAT_EQUAL(f1,f2)      (fabs(f1-f2)<= FLOAT_EPSILON)

namespace MY_UTIL
{
	// ���� ���� �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);

	// ��ŸƮ -> ���� -> ���� ��������
	float getAngle(float startX, float startY, float endX, float endY);
}