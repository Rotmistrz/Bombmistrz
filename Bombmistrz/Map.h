#pragma once
#include "Header.h"
#include "Brick.h"
#include <vector>

//uproszczenie typow
typedef std::shared_ptr<std::vector<std::vector<char>>> ptrVec2dChar;
typedef std::vector<std::vector<char>> vec2dChar;

class Map {
//	void loadBrick(const Brick&);
//	void loadBrick(Brick);
//	void loadBricksFromVector(const std::vector<Brick>&);
	
	//uchwyt do tekstury
	GLuint brickTextID;
	//obiekt do przechowywania pliku .img
	sf::Image imgData;

	//std::vector do wskaznikow na cegielki mapy
	std::vector<std::shared_ptr<Brick>> vec;
	//std::vector przechowywujacy mape w formie zdatnej do skopiowania na pamiec karty graficznej(bufora)
	std::vector<float> corVec;

	//szerokosc i wysokosc okienka aplikacji
	uint width, height;
	//liczba kolumn obliczana na bazie dlugosci boku cegielek
	uint numberOfCols = 0;
	//liczba wierszy
	uint numberElementsInRow = 0;
	//dlugosc boku kwadratu po osi x
	float aX = .0f;
	//dlugosc boku kwadratu po osi y
	float aY = .0f;

	//ustawia corVec
	void setCorVec();
public:

	//wczytywanie mapy w odpowiednim formacie z pliku tekstowego
	//zwraca dwuwymiarowy std::vector char'ow
	static ptrVec2dChar loadMapFromFile(const std::string&);
	
	/*
	* arg1: pobiera std::vector wskaznikow na bloczki
	*/
	Map(const std::vector<std::shared_ptr<Brick>> &);

	/*
	* arg1: szerokosc okienka aplikacji
	* arg2: wysokosc okienka aplikacji
	* arg3: pobiera dwuwymiarowy std::vector char'ow
	*/
	Map(uint, uint, const vec2dChar&);
	Map();
	~Map();
	
//	bool loadImageFromFile(const std::string&);
//	void bindAndUpload();
//	Brick* getBrick(uint);

	inline GLuint getCorSize() {
		return corVec.size();
	}

	inline GLuint getSize() {
		return vec.size();
	}

	inline GLuint GetSizeInBytes() {
		return corVec.size() * sizeof(float);
	}

	inline float* getFirstTabElement() {
		return &corVec[0];
	}

	inline float* getLastTabElement() {
		return &corVec[corVec.size() - 1];
	}

	inline uint getNumberOfCols() {
		return numberOfCols;
	}

	inline uint getNumberElementsInRow() {
		return numberElementsInRow;
	}

	inline float get_aX() {
		return aX;
	}

	inline float get_aY() {
		return aY;
	}

	/*
	* Wyszukuje kolumne w jakiej znajduje sie zadana wspolrzedna x'owa
	* arg1: wspolrzedna x w przestrzeni gry. Tzn <-1, 1>
	* return: zwraca kolumne w jakiej znajduje sie x
	*/
	inline uint getPosInCols(float __point) {
		//asercje zabezpieczajace przed wykroczeniem z mapy. Uwzgledniaja maly blad epsilon
		assert(__point <= 1.0f + 0.05f);
		assert(__point >= -1.0f - 0.05f);
		//lewy kraniec mapy
		float _edge = -1.0f;
		//numer kolumny
		uint _col = 0;
		//jezeli dochodzimy do prawego kranca przerwijmy petle
		while (_edge <= 1.0) {
			//sprawdzal czy punkt lezy w przedziale <_edge,_edge + aX>
			//jezeli znajduje sie tam to zwroc kolumne
			if (__point <= _edge + aX)
				return _col;

			//iteracja po kolumnie
			_col++;
			//przemieszczanie sie po mapie. Wielkosc przesuwana o szerokosc kolumny
			_edge += aX;
		}
		
		return 0;
	}

	inline uint getPosInRows(float __point) {
		assert(__point <= 1.0f + 0.05f);
		assert(__point >= -1.0f - 0.05f);

		float _edge = 1.0f;
		uint _row = 0;
		while (_edge >= -1.0) {
			if (__point >= _edge - aY)
				return _row;
			_row++;
			_edge -= aY;
		}

		return 0;
	}


	/*
	* arg1: vector2f przechowywujacy punkt w przestrzeni R2
	* funkcja wyszukuje najblizsza cegielke na planszy( tzn. kwadrat. Plansza jest podzielona na kwadraciki)
	* return: koordynaty lewego gornego rogu kwadratu
	*/
	Vertex2f getXY1ofTheNearestBrick(Vertex2f __v) {
		float _edge = 1.0f;
		Vertex2f _result_point;

		while (_edge >= -1.0) {
			if (__v.y >= _edge - aY) {
				_result_point.y = _edge;
				break;
			}
			_edge -= aY;
		}

		_edge = -1.0f;
		while (_edge <= 1.0) {
			if (__v.x <= _edge + aX) {
				_result_point.x = _edge;
				break;
			}
			_edge += aX;
		}

		return _result_point;
	}

	/*
	* funkcja pobiera kolumne i wiersz. Nastepnie sprawdza czy wskaznik dla danego koordynatu w wektorze cegielek
	* jest pusty
	* arg1: interesujaca nas kolumna
	* arg2: interesujacy nas wiersz
	* return: jezeli jest obiekt - cegla na planszy -> true, w przeciwnym wypadku false
	*/
	inline bool isBrick(uint __col, uint __row) {
		assert(__row * numberElementsInRow + __col < vec.size());
		if (vec[__row * numberElementsInRow + __col] != nullptr)
			return true;
		return false;
	}

	/*
	* funkcja usuwa bloczek znajdujacy sie w danym wierszu i kolumnie z vektora mapy
	* arg1: wiersz
	* arg2: kolumna
	*/
	bool removeElement(uint, uint);

	/*
	* funkcja stworzona do przegladania vectora vec, ale bez posredniego dostepu do niego w klasie.
	* zabezpieczona o wykrywanie niepoprawnych indeksow.
	* arg1: indeks w wektorze vec
	* return: jezeli wskaznik w wektorze vec wskazuje na jakas cegielke true, w przeciwnym razie false
	*/
	inline bool isNullPtr(int __i) {
		if (__i >= vec.size() || __i < 0)
			return true;

		if (vec[__i] == nullptr)
			return true;
		return false;
	}
//	bool loadMap(const std::string&);
};

