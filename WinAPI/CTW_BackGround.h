#pragma once

class CTW_BackGround
{
private:
	GImage* _backGround;
	RECT _rc[7];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(HDC memDC);
	void render(HDC memDC, HDC hdc);

	RECT* getRect() {return _rc; }

	CTW_BackGround() {}
	~CTW_BackGround() {}
};

