#pragma once
#include "Vertex.h"
#include <vector>

typedef unsigned int uint;
class Square {

protected:
	Vertex2f xy1; //wierzcholek gorny lewy
	Vertex2f xy3; //wierzcholek dolny prawy
	Vertex3f color; //kolor kazdego wierzcholka

	Vertex2f xy2; //wierzcholek gorny prawy
	Vertex2f xy4; //wierzcholek dolny lewy
	float side; //bok kwadratu

	Vertex2f texX, texY, texZ, texT;
	void setTexture();
public:
	Square(Vertex2f, Vertex2f, Vertex3f);
	Square(float, float, float, float);
	Square(Vertex2f, float, Vertex3f, uint, uint);
	~Square();

	std::vector<float> giveFloatVec();
};

