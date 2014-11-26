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
	uint numberOfRows = 0;
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

	inline uint getNumberOfRows() {
		return numberOfRows;
	}

	inline float get_aX() {
		return aX;
	}

	inline float get_aY() {
		return aY;
	}

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
		assert(__point <= 1.0f);
		assert(__point >= -1.0f);

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

	inline bool isBrick(uint __col, uint __row) {
		assert(__row * numberOfRows + __col < vec.size());
		if (vec[__row * numberOfRows + __col] != nullptr)
			return true;
		return false;
	}
//	bool loadMap(const std::string&);
};

