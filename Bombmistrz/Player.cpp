#include "Player.h"

Player::Player(
	Vertex2f __xy1,
	Vertex2f __xy3,
	Vertex3f __col)
: xy1(__xy1), xy3(__xy3), color(__col) {
	float d = 
		sqrt((xy3.x - xy1.x)*(xy3.x - xy1.x) + (xy3.y - xy1.y)*(xy3.y - xy1.y));
	side = (sqrt(2) * d) / 2;

	xy2.x = xy1.x + side;
	xy2.y = xy1.y;
	xy4.x = xy1.x;
	xy4.y = xy3.y;
}

Player::~Player() {
}

std::vector<float> Player::giveFloatVec() {
	return 
		std::vector<float> {
			xy1.x, xy1.y, color.x, color.y, color.z,
			xy2.x, xy2.y, color.x, color.y, color.z,
			xy3.x, xy3.y, color.x, color.y, color.z,
			xy4.x, xy4.y, color.x, color.y, color.z,
		};
}

void Player::moveRight(clock_t& __actual_t) {
	clock_t delta = clock() - __actual_t;
	delta = delta * speed;
	translate.x += static_cast<float>(delta);
}

void Player::moveLeft(clock_t& __actual_t) {
	clock_t delta = clock() - __actual_t;
	delta = delta * speed;
	translate.x -= static_cast<float>(delta);
}

void Player::moveUp(clock_t& __actual_t) {
	clock_t delta = clock() - __actual_t;
	delta = delta * speed;
	translate.y += static_cast<float>(delta);
}

void Player::moveDown(clock_t& __actual_t) {
	clock_t delta = clock() - __actual_t;
	delta = delta * speed;
	translate.y -= static_cast<float>(delta);
}
