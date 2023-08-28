#pragma once

template <typename InterfaceType>
inline void SafeRelease(InterfaceType** currentScene)
{
	if (*currentScene != nullptr)
	{
		(*currentScene)->Release();
		*currentScene = nullptr;
	}
}

template <typename InterfaceType>
inline InterfaceType SafeAcquire(InterfaceType* newObject)
{
	if (newObject != nullptr)
	{
		//너희가 붙이고 싶은 함수
		newObject->AddRef();
	}

	return newObject;
}

inline HRESULT ExceptionToResult()
{
	// try : 예외 발생에 대한 검사 범위
	try
	{
		// 이전 예외를 다시 던진다.
		throw;
	}

	// catch : try 블록에서 발생한 예외를 처리한다.
	// bad_alloc : 배열 오버플로우 / 동적 할당 Not alloc
	catch (std::bad_alloc&)
	{
		// 일단 값을 모르겠고 널 찍어서 프로그램 살리고 보자.
		return E_OUTOFMEMORY;
	}

	catch (...)
	{
		return E_FAIL;
	}
}

// 새로운 객체를 붙일 때 이전 객체를 해제
template <typename InterfaceType>
inline void SafeSet(InterfaceType** currentObject, InterfaceType* newObject)
{
	SafeAcquire(newObject);
	SafeRelease(&currentObject);
	currentObject = newObject;
}

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };
	return pt;
}

inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
{
	MoveToEx(hdc, startX, startY, NULL);
	LineTo(hdc, endX, endY);
}

inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };
	return rc;
}

inline void DrawRectMake(HDC hdc, RECT rc)
{
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };

	return rc;
}

inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
}

inline RECT CollisionAreaResizing(RECT rcDest, int width, int height)
{
	RECT rc = 
	{
		rcDest.left + width / 2,
		rcDest.top + height / 2,
		rcDest.right - width / 2,
		rcDest.bottom - height / 2
	};
	return rc;
}