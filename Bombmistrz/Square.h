#pragma once
#include "Vertex.h"
#include <vector>

class Square {

protected:
	Vertex2f xy1; //wierzcholek gorny lewy
	Vertex2f xy3; //wierzcholek dolny prawy
	Vertex3f color; //kolor kazdego wierzcholka

	Vertex2f xy2; //wierzcholek gorny prawy
	Vertex2f xy4; //wierzcholek dolny lewy
	float side; //bok kwadratu
public:
	Square(Vertex2f, Vertex2f, Vertex3f);
	~Square();

	std::vector<float> giveFloatVec();
};

