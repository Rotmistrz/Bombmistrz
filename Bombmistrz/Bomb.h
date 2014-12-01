#pragma once
#include "Header.h"
#include "Square.h"

class Bomb: public Square {
	//czas w jakim po uruchomieniu bomby, wybuchnie ona
	float timeToExplosion = .0f;
	float explosionTime = 3.0f; // w sekundach
	//przesuniecie wzgledem pozycji wejsciowej
	bool active = false;
	Vertex2f uniform;
public:
	//konstruktor wywolujacy konstruktor klasy Square
	//arg1: x1
	//arg2: y1
	//arg3: x3
	//arg4: y3
	Bomb(float, float, float, float);
	Bomb(Vertex2f, float, Vertex3f, uint, uint);
	virtual ~Bomb();

	//resetuje bombe i przesuniecie
	inline void reset() {
		timeToExplosion = .0f;
		uniform = .0f;
	}

	//dodaje czas do aktualnego czasu pozostalego do wybuchu
	inline bool updateTime(float __dt) {
		if (active == false)
			return false;

		timeToExplosion += __dt;
		if (timeToExplosion > explosionTime) {
			reset();
			active = false;
			return true;
		}
		return false;
	}

	//ustawia aktualne przesuniecie wzgledem pozycji wejsciowej
	inline void set(float __x, float __y) {
		uniform.x = __x;
		uniform.y = __y;
	}

	//ustawia aktualne przesuniecie wzgledem pozycji wejsciowej, tylko za pomoca struktury Vertex2f
	inline void set(Vertex2f __v) {
		uniform = __v;
	}

	inline Vertex2f getUniform() {
		return uniform;
	}

	bool isActive() {
		return active;
	}

	void setActive() {
		active = true;
	}

	void disActive() {
		active = false;
	}

	void setExplosionTime(float __time) {
		explosionTime = __time;
	}

	inline float getExplosionTime() {
		return explosionTime;
	}
};

