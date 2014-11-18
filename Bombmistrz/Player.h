#pragma once
#include "Header.h"
#include "Square.h"

class Player: public Square {
	GLuint playerTexId;
	sf::Image imgData;

	float old = .0f;
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
	Player(Vertex2f, float, Vertex3f, uint, uint);
	~Player();

	inline void setSpeed(float __s) {
		speed = __s;
	}
	inline float getSpeed() {
		return speed; 
	}

	//ruch
	inline void moveRight(float __dt) {
		//zapamietaj starej wartosci przesuniecia
		old = translate.x;
		//aktualizacja o nowe dt przesuniecia
		translate.x += __dt * speed;
		//jezeli przesuniecie wykracza poza obszar gry to przywroc stare przesuniecie
		if (translate.x + xy2.x > 1.0f)
			translate.x = old;
	}
	inline void moveLeft(float __dt) {
		old = translate.x;
		translate.x -= __dt * speed;
		if (translate.x + xy1.x < -1.0f)
			translate.x = old;
	}
	inline void moveUp(float __dt) {
		old = translate.y;
		translate.y += __dt * speed;
		if (translate.y + xy1.y > 1.0f)
			translate.y = old;
	}
	inline void moveDown(float __dt) {
		old = translate.y;
		translate.y -= __dt * speed;
		if (translate.y + xy3.y < -1.0f)
			translate.y = old;
	}
	inline Vertex2f getTranslation() {
		return translate;
	}
};

