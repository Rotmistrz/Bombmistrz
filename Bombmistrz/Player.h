#pragma once
#include "Header.h"

struct Vertex2f {
	float x, y;
};

struct Vertex3f {
	float x, y, z;
};

struct Vertex4f {
	float x, y, z, t;
};

class Player {
public:

	//tymczasowe kordynaty jako kwadrat
	Vertex2f xy1;
	Vertex2f xy3;
	Vertex3f color;

	Vertex2f xy2;
	Vertex2f xy4;
	float side;

	Vertex2f translate;
	float speed = 10;
	/*
	* arg1 = wierzcholek p1
	* arg2 = wierzcholek p3
	* arg3 = kolor - rgb - float
	* arg4 = dlugosc boku kwadratu
	*/
	Player(Vertex2f, Vertex2f, Vertex3f);
	~Player();

	std::vector<float> giveFloatVec();

	//ruch
	void moveRight(clock_t&);
	void moveLeft(clock_t&);
	void moveUp(clock_t&);
	void moveDown(clock_t&);
	inline Vertex2f getTranslation() {
		return translate;
	}
};

