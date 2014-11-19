#include "Player.h"

Player::Player(
	Vertex2f __xy1,
	Vertex2f __xy3,
	Vertex3f __col)
: Square(__xy1, __xy3, __col) {
	
	translate.x = .0f;
	translate.y = .0f;

	width = height = 1;
	normSpeedX = normSpeedY = 1.0f;
}

Player::Player(
	Vertex2f __xy1,
	float __side,
	Vertex3f __col,
	uint __w,
	uint __h,
	Map* __map_ptr)
	: Square(__xy1, __side, __col, __w, __h), mapPtr(__map_ptr) {

	translate.x = .0f;
	translate.y = .0f;

	width = __w;;
	height = __h;
	normSpeedX = normSpeedY = 1.0f;
	//szerokosc ekranu jest wieksza wiec jezeli dt_speed bedzie taki sam dla ruchu w gore/dol
	//i ruchu w prawo/lewo to w prawo/lewo obiekt bedzie sie szybciej poruszal.
	//powodem tego jest fakt, ze szerokosc bedzie takze na przedziale <-1,1> i jakas mala odleglosc po wysokosci
	//bedzie troszeczke wieksza odlegloscia w pikselach dla szerokosc.
	if (__w > __h)
		normSpeedX = static_cast<float>(__h) / static_cast<float>(__w);
	else
	if (__h > __w)
		normSpeedY = static_cast<float>(__w) / static_cast<float>(__h);
}

Player::~Player() {
}
