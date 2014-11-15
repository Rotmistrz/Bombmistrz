#pragma once
#include "Square.h"

class Brick: public Square {
public:
	Brick(Vertex2f, Vertex2f, Vertex3f);
	Brick(float, float, float, float);
	~Brick();
};

