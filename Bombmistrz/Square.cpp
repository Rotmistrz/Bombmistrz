#include "Square.h"

Square::Square(
	Vertex2f __xy1,
	Vertex2f __xy3,
	Vertex3f __col)
	: xy1(__xy1), xy3(__xy3), color(__col) {

	//obliczanie przekatnej kwadratu. Dzieki czmeu ebdziemy mieli mozliwosc policzenia jego bok
	float d =
		sqrt((xy3.x - xy1.x)*(xy3.x - xy1.x) + (xy3.y - xy1.y)*(xy3.y - xy1.y));
	side = (sqrt(2) * d) / 2;

	xy2.x = xy1.x + side;
	xy2.y = xy1.y;
	xy4.x = xy1.x;
	xy4.y = xy3.y;
}

Square::~Square() {
}

std::vector<float> Square::giveFloatVec() {
	return
		std::vector<float> {

		xy1.x, xy1.y, color.x, color.y, color.z,
		xy2.x, xy2.y, color.x, color.y, color.z,
		xy3.x, xy3.y, color.x, color.y, color.z,
		xy4.x, xy4.y, color.x, color.y, color.z,
	};
}