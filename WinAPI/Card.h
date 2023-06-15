#pragma once
class Card
{
private:
	int centerX;
	int centerY;
	BOOL open = FALSE;
	int width;
	int height;
	HBRUSH cardColor;

public:
	RECT getRect() { return RectMakeCenter(centerX, centerY, width, height); }
	void openCard() { open = true; }
	void reverseCard() { open = false; }
	void setOpen(BOOL _open) { open = _open; }
	BOOL getOpen() { return open; }
	HBRUSH getCardColor() { return cardColor; }
	BOOL clickCard(POINT _pt);
	
	Card(int _left, int _top, int _right, int _bottom, HBRUSH _cardColor);
	~Card();
};

