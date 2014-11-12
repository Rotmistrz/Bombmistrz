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

Square::Square(float __x1, float __y1, float __x3, float __y3) {
	xy1.x = __x1;
	xy1.y = __y1;
	xy3.x = __x3;
	xy3.y = __y3;
	color.x = 0.0f;
	color.y = 1.0f;
	color.z = 1.0f;

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