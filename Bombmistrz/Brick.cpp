#include "Brick.h"

Brick::Brick(Vertex2f __v1, Vertex2f __v2, Vertex3f __col)
: Square(__v1, __v2, __col) {
}

Brick::Brick(float __x1, float __y1, float __x3, float __y3)
: Square(__x1, __y1, __x3, __y3) {
	texX.x = .0f;	
	texX.y = .0f;
	texY.x = 1.0f;
	texY.y = .0f;
	texZ.x = 1.0f;
	texZ.y = 1.0f;
	texT.x = .0f;
	texT.y = 1.0f;
}
 
Brick::~Brick() {
}
