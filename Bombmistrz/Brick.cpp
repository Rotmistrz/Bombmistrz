#include "Brick.h"

Brick::Brick(Vertex2f __v1, Vertex2f __v2, Vertex3f __col)
: Square(__v1, __v2, __col) {
}

Brick::Brick(float __x1, float __y1, float __x3, float __y3)
: Square(__x1, __y1, __x3, __y3) {
}
 
Brick::~Brick() {
}
