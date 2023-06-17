#pragma once
class Clay
{
private:
	POINT position;
	int type;
	POINT dir;
	BOOL isHit;
	int vertexN;
	POINT vertexes[8];

public:
	void setPosition(POINT _position) {position = _position;}
	POINT getPosition() {return position;}
	void setDir(POINT _dir) {dir = _dir;}
	POINT getDir() {return dir;}
	BOOL getIsHit() {return isHit;}
	void setIsHit(BOOL _isHit) {isHit = _isHit;}
	int getType() {return type;}
	POINT* getVertexes() { return vertexes; }
	int getVertexN() { return vertexN; }
	BOOL isHitted(POINT pt);

	void move();
	Clay(int _type, POINT _position, POINT _dir, BOOL _isHit);
	~Clay();
};

