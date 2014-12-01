#include "Bomb.h"

Bomb::Bomb(float __x1, float __y1, float __x3, float __y3)
: Square(__x1, __y1, __x3, __y3) {
	uniform = .0f;
}

Bomb::Bomb(Vertex2f __point, float __side, Vertex3f __color, uint __w, uint __h)
: Square(__point, __side, __color, __w, __h) {
	uniform = .0f;
}

Bomb::~Bomb() {
}
