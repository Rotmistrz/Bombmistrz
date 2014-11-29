#pragma once
#include <assert.h>
#include "Vertex.h"
#include <vector>

typedef unsigned int uint;
class Square {

protected:
	Vertex2f xy1; //wierzcholek gorny lewy
	Vertex2f xy3; //wierzcholek dolny prawy
	Vertex3f color; //kolor kazdego wierzcholka

	Vertex2f xy2; //wierzcholek gorny prawy
	Vertex2f xy4; //wierzcholek dolny lewy
	float side; //bok kwadratu

	Vertex2f texX, texY, texZ, texT;

	// prywatna metoda ustawiajaca polozenie tekstury w kwadracie. Tekstury ktora bedzie przydzielona w obiekcie klasy Game
	void setTexture();
public:
	/*
	* arg1: lewy gorny wierzcholek kwadratu w formacie mieszczacy sie w przedziale <-1,1>
	* arg2: prawy dolny rog wierzcholka kwadratu
	* arg3: kolor kwadratu w formacie rgb
	*/
	Square(Vertex2f, Vertex2f, Vertex3f);

	/*
	* arg1: wspolrzedna x lewego gornego wierzcholka kwadratu w przedziale <-1,1>
	* arg2: wspolrzedna y lewego gornego wierzcholka kwadratu
	* arg3: wspolrzedna x prawego dolnego wierzcholka kwadratu
	* arg4: wspolrzedna y prawego dolnego wierzcholka kwadratu
	*/
	Square(float, float, float, float);
	
	/*
	* arg1: polozenie lewego gornego wierzcholka kwadratu w przedzialcze x = <0, wysokosc> ; y = <0, szerokosc> 
	* arg2: dlugosc boku kwadratu
	* arg3: kolor kwadratu
	* arg4: szerokosc okna aplikacji
	* arg5: wysokosc okna aplikacji
	*/
	Square(Vertex2f, float, Vertex3f, uint, uint);
	virtual ~Square();

	/*
	* return: zwraca std::vector<float> uporzadkowanych liczb gotowych do przekopiowania do buffora na karcie graficznej
	* w zdefiniowanym layout'cie
	*/
	std::vector<float> giveFloatVec();
};

