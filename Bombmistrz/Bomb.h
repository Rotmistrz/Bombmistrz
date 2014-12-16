#pragma once
#include "Header.h"
#include "Square.h"
#include "Map.h"
#include "PlayerManager.h"

typedef std::shared_ptr<PlayerManager> spointerPM;
class Bomb: public Square {
	//czas w jakim po uruchomieniu bomby, wybuchnie ona
	float timeToExplosion = .0f;
	float explosionTime = 3.0f; // w sekundach
	//przesuniecie wzgledem pozycji wejsciowej
	bool active = false;
	Vertex2f uniform;

	uint power = 2;
	std::shared_ptr<Map> map;
	spointerPM pm;
public:
	//konstruktor wywolujacy konstruktor klasy Square
	//arg1: x1
	//arg2: y1
	//arg3: x3
	//arg4: y3
	Bomb(float, float, float, float, const std::shared_ptr<Map>&, const spointerPM&);
	Bomb(Vertex2f, float, Vertex3f, uint, uint, const std::shared_ptr<Map>&, const spointerPM&);
	virtual ~Bomb();

	//resetuje bombe i przesuniecie
	inline void reset() {
		timeToExplosion = .0f; // == 0.0f;
		uniform = .0f;
	}

	//dodaje czas do aktualnego czasu pozostalego do wybuchu
	inline bool updateTime(float __dt) {
		if (active == false)
			return false;

		timeToExplosion += __dt;
		//eksplozja!
		if (timeToExplosion > explosionTime) {
			active = false;

			Vertex2f _center = getCenter();
			uint _col = map->getPosInCols(uniform.x + side_w / 2.0f);
			uint _row = map->getPosInRows(uniform.y - side_h / 2.0f);
			int _left_edge = static_cast<int>(_col) - static_cast<int>(power);
			int _right_edge = static_cast<int>(_col) + static_cast<int>(power);
			int _up_edge = static_cast<int>(_row) + static_cast<int>(power);
			int _down_edge = static_cast<int>(_row) - static_cast<int>(power);
/*
			for (int i = _left_edge; i <= _right_edge; i++) {
				map->removeElement(_row, i);
				auto _players_in_area = pm->isPlayers(_row, i);
				if (_players_in_area.size() != 0) {
					for (auto i_ : _players_in_area) {
						pm->removePlayer(i_);
					}
				}
			}*/

			//zmienna ktora wykrywa, czy juz cegielka stanela na drodze ognia
			//jezeli tak to ogien nie moze byc dalej prowadzony
			bool _removed = false;
			//od srodka do lewego konca zasiegu
			for (int i = _col; i >= _left_edge; i--) {
				if (!_removed){
					if (map->removeElement(_row, i)) {
						_removed = true;
					}
				}
				
				auto _players_in_area = pm->isPlayers(_row, i);
				if (_players_in_area.size() != 0) {
					for (auto i_ : _players_in_area) {
						pm->removePlayer(i_);
					}
				}
			}
			_removed = false;
			//od srodka do prawego konca zasiegu
			for (int i = _col; i <= _right_edge; i++) {
				if (!_removed){
					if (map->removeElement(_row, i)){
						_removed = true;
					}
				}

				auto _players_in_area = pm->isPlayers(_row, i);
				if (_players_in_area.size() != 0) {
					for (auto i_ : _players_in_area) {
						pm->removePlayer(i_);
					}
				}
			}
			_removed = false;


			//od srodka do dolnego konca zasiegu
			for (int i = _row; i >= _down_edge; i--) {
				if (!_removed) {
					if (map->removeElement(i, _col)) {
						_removed = true;
					}
				}

				auto _players_in_area = pm->isPlayers(i, _col);
				if (_players_in_area.size() != 0) {
					for (auto i_ : _players_in_area) {
						pm->removePlayer(i_);
					}
				}
			}
			_removed = false;

			//od srodka do gornego konca zasiegu
			for (int i = _row; i <= _up_edge; i++) {
				if (!_removed) {
					if (map->removeElement(i, _col)) {
						_removed = true;
					}
				}

				auto _players_in_area = pm->isPlayers(i, _col);
				if (_players_in_area.size() != 0) {
					for (auto i_ : _players_in_area) {
						pm->removePlayer(i_);
					}
				}
			}
			_removed = false;

/*
			for (int i = _down_edge; i <= _up_edge; i++) {
				map->removeElement(i, _col);
				auto _players_in_area = pm->isPlayers(i, _col);
				if (_players_in_area.size() != 0) {
					for (auto i_ : _players_in_area) {
						pm->removePlayer(i_);
					}
				}
			}*/

			reset();
			return true;
		}
		return false;
	}

	//ustawia aktualne przesuniecie wzgledem pozycji wejsciowej
	inline void set(float __x, float __y) {
		Vertex2f _in{ __x + side_w / 2.0f, __y - side_h / 2.0f};
		uniform = map->getXY1ofTheNearestBrick(_in);
//		uniform.x = __x;
//		uniform.y = __y;
	}

	//ustawia aktualne przesuniecie wzgledem pozycji wejsciowej, tylko za pomoca struktury Vertex2f
	inline void set(Vertex2f __v) {
		Vertex2f _in = __v;
		_in.x += side_w / 2.0f;
		_in.y -= side_h / 2.0f;
//		uniform = __v;
		uniform = map->getXY1ofTheNearestBrick(_in);
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

