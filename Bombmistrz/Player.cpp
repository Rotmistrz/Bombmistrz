#include "Player.h"

Player::Player(
	Vertex2f __xy1,
	Vertex2f __xy3,
	Vertex3f __col)
: Square(__xy1, __xy3, __col) {
	
	translate.x = .0f;
	translate.y = .0f;
}

Player::Player(
	Vertex2f __xy1,
	float __side,
	Vertex3f __col,
	uint __w,
	uint __h)
	: Square(__xy1, __side, __col, __w, __h) {

	translate.x = .0f;
	translate.y = .0f;
}

Player::~Player() {
}
