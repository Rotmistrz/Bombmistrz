#pragma once
#include "Header.h"
#include "Square.h"
#include "Map.h"

class Player: public Square {
	GLuint playerTexId;
	sf::Image imgData;

	//zmienna pomocnicza. Nie musze co chwile tworzyc nowego floata
	float old = .0f;
	//normalizacja predkosci do danej szerokosci. Wiecej w pliku doc.odt i komentarzach
	float normSpeedX, normSpeedY;
	//szerokosc okna
	uint width;
	//wysokosc okna
	uint height;
	uint col1, col2;
	uint row1, row2;
	Map* mapPtr;
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
	Player(Vertex2f, float, Vertex3f, uint, uint, Map*);
	~Player();

	inline void setSpeed(float __s) {
		speed = __s;
	}
	inline float getSpeed() {
		return speed; 
	}

	inline void setDimWindow(uint __w, uint __h) {
		width = __w;
		height = __h;

		normSpeedX = normSpeedY = 1.0f;
		if (__w > __h)
			normSpeedX = static_cast<float>(__h) / static_cast<float>(__w);
		else
		if (__h > __w)
			normSpeedY = static_cast<float>(__w) / static_cast<float>(__h);
	}

	//ruch
	inline void moveRight(float __dt) {
		//zapamietaj starej wartosci przesuniecia
		old = translate.x;
		//aktualizacja o nowe dt przesuniecia
		translate.x += __dt * speed * normSpeedX;
		//jezeli przesuniecie wykracza poza obszar gry to przywroc stare przesuniecie
//		translate.x = translate.x * height / width;
		if (translate.x + xy2.x > 1.0f) {
			translate.x = old;
			return;
		}

		//pobranie kolumny w jakiej znajduje sie gracz
		col1 = mapPtr->getPosInCols(translate.x + xy2.x);
		//pobranie wierszy w jakich znajduje sie gracz. Jezeli gracz jest w jednym wierszu(nie miedzy dwoma)
		//to row1 == row2
		row1 = mapPtr->getPosInRows(xy2.y + translate.y);
		row2 = mapPtr->getPosInRows(xy3.y + translate.y);
		//pobierana jest tylko jedna kolumna poniewaz interesuje nas tylko ta prawa. Powodem tego jest fakt, ze
		//kierujemy sie na prawo i mozemy zmienic nasza kolunne prawo + 1 na miejscu ktorej stoi juz bloczek

		//sprawdzamy czy w naszej nowej lokalizacj znajduje sie bloczek
		if (mapPtr->isBrick(col1, row1)) {
			translate.x = old;
		}
		else
		if (mapPtr->isBrick(col1, row2)) {
			translate.x = old;
		}
	}
	inline void moveLeft(float __dt) {
		old = translate.x;
		translate.x -= __dt * speed * normSpeedX;
//		translate.x = translate.x * height / width;
		if (translate.x + xy1.x < -1.0f) {
			translate.x = old;
			return;
		}

		col1 = mapPtr->getPosInCols(translate.x + xy1.x);
		row1 = mapPtr->getPosInRows(xy2.y + translate.y);
		row2 = mapPtr->getPosInRows(xy3.y + translate.y);

		if (mapPtr->isBrick(col1, row1)) {
			translate.x = old;
		}
		else
		if (mapPtr->isBrick(col1, row2)) {
			translate.x = old;
		}
	}
	inline void moveUp(float __dt) {
		old = translate.y;
		translate.y += __dt * speed * normSpeedY;
		if (translate.y + xy1.y > 1.0f) {
			translate.y = old;
			return;
		}

		row1 = mapPtr->getPosInRows(translate.y + xy1.y);
		col1 = mapPtr->getPosInCols(xy1.x + translate.x);
		col2 = mapPtr->getPosInCols(xy2.x + translate.x);

		if (mapPtr->isBrick(col1, row1)) {
			translate.y = old;
		}
		else
		if (mapPtr->isBrick(col2, row1)) {
			translate.y = old;
		}
	}
	inline void moveDown(float __dt) {
		old = translate.y;
		translate.y -= __dt * speed * normSpeedY;
		if (translate.y + xy3.y < -1.0f) {
			translate.y = old;
			return;
		}

		row1 = mapPtr->getPosInRows(translate.y + xy3.y);
		col1 = mapPtr->getPosInCols(xy1.x + translate.x);
		col2 = mapPtr->getPosInCols(xy2.x + translate.x);

		if (mapPtr->isBrick(col1, row1)) {
			translate.y = old;
		}
		else
		if (mapPtr->isBrick(col2, row1)) {
			translate.y = old;
		}
	}

	inline Vertex2f getTranslation() {
		return translate;
	}
};

