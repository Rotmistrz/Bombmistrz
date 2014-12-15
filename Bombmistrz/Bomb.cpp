#include "Bomb.h"

Bomb::Bomb(float __x1, float __y1, float __x3, float __y3, 
	const std::shared_ptr<Map>& __map, const spointerPM& __pm)
: Square(__x1, __y1, __x3, __y3), map(__map), pm(__pm) {
	uniform = .0f;

	assert(map != nullptr && pm != nullptr);
}

Bomb::Bomb(Vertex2f __point, float __side, Vertex3f __color, uint __w, uint __h, 
	const std::shared_ptr<Map>& __map, const spointerPM& __pm)
: Square(__point, __side, __color, __w, __h), map(__map), pm(__pm) {
	uniform = .0f;

	assert(map != nullptr && pm != nullptr);
}

Bomb::~Bomb() {
}
