#include "Player.h"

Player::Player(
	Vertex2f __xy1,
	Vertex2f __xy3,
	Vertex3f __col)
: Square(__xy1, __xy3, __col) {
	
	translate.x = .0f;
	translate.y = .0f;
}

Player::~Player() {
}
