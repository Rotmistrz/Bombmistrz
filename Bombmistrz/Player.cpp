#include "Player.h"

Player::Player(
	Vertex2f __xy1,
	Vertex2f __xy3,
	Vertex3f __col,
	float __side)
: xy1(__xy1), xy3(__xy3), color(__col), side(__side) {
	xy2.x = xy1.x + side;
	xy2.y = xy1.y;
	xy4.x = xy1.x;
	xy4.y = xy3.y;
}

Player::~Player() {
}
