#pragma once
#include "Header.h"
#include "Square.h"

class Player: public Square {
	GLuint playerTexId;
	sf::Image imgData;
public:
	Vertex2f translate;
	float speed = 0.5;
	/*
	* arg1 = wierzcholek p1
	* arg2 = wierzcholek p3
	* arg3 = kolor - rgb - float
	* arg4 = dlugosc boku kwadratu
	*/
	Player(Vertex2f, Vertex2f, Vertex3f);
	~Player();

	inline void setSpeed(float __s) {
		speed = __s;
	}
	inline float getSpeed() {
		return speed; 
	}

	//ruch
	inline void moveRight(float __dt) {
		translate.x += __dt * speed;
	}
	inline void moveLeft(float __dt) {
		translate.x -= __dt * speed;
	}
	inline void moveUp(float __dt) {
		translate.y += __dt * speed;
	}
	inline void moveDown(float __dt) {
		translate.y -= __dt * speed;
	}
	inline Vertex2f getTranslation() {
		return translate;
	}
};

