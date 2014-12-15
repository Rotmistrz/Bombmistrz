#include "PlayerManager.h"

//konstruktor przypisujacy vektor graczy do vektora graczy wewnatrz klasy
//nastepnie konstruktor tworzy vektor gotowy do umieszczenia w buforze.
//tzn wszystkie parametry kazdego gracza: polozenie, kolor, polozenie tekstury
PlayerManager::PlayerManager(std::vector<Player>* __vec) {
	vec = new std::vector<Player>(*__vec);

	for (auto itr = vec->begin(); itr != vec->end(); ++itr) {
		std::vector<float> _tmp = itr->giveFloatVec();
		for (auto itr2 = _tmp.begin(); itr2 != _tmp.end(); ++itr2) {
			corVec.push_back(*itr2);
		}
	}
}

//konstruktor przenoszacy
PlayerManager::PlayerManager(std::vector<Player>&& __vec) {
	vec = new std::vector<Player>(__vec);

	for (auto itr = vec->begin(); itr != vec->end(); ++itr) {
		activePlayers.push_back(true);
		std::vector<float> _tmp = itr->giveFloatVec();
		for (auto itr2 = _tmp.begin(); itr2 != _tmp.end(); ++itr2) {
			corVec.push_back(*itr2);
		}
	}

	assert(vec->size() == activePlayers.size());
}

PlayerManager::~PlayerManager() {
/*	glDeleteBuffers(1, &vertexBufferId);

	glUseProgram(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader); */
	delete vec;
}


Player* PlayerManager::getPlayer(uint __number)	{
	assert(__number > 0);
	uint i = 0;
	for (; i < vec->size(); i++) {
		if (i == __number - 1)
			return &((*vec)[i]);
	}

	return nullptr;
}

std::vector<int> PlayerManager::isPlayers(int __row, int __col) {
	int _player_number = 1;
	std::vector<int> _result_vec;
	for (auto& p : *vec) {
		Vertex4f _v = p.getPosInRowsCols();
		if ((_v.x == __row && _v.z == __col) ||
			(_v.x == __row && _v.t == __col) ||
			(_v.y == __row && _v.z == __col) ||
			(_v.y == __row && _v.t == __col)) {
			_result_vec.push_back(_player_number);
			++_player_number;
		}
	}

	return _result_vec;
}

void PlayerManager::removePlayer(int __i) {
	assert(__i > 0 && __i <= activePlayers.size());
	activePlayers[__i - 1] = false;
}

/*
GLchar* PlayerManager::loadShader(
	const std::string& __file_name, 
	uint& __size) {

	//stworzenie strumienia wejscia
	std::ifstream _input_file;
	//otwarcie pliku o nazwie __file_name
	_input_file.open(__file_name);
	//sprawdzenie czy mozna otworzyc plik
	if (!_input_file.is_open())
		return nullptr;

	bool first = true;
	std::string _result("");
	while (!_input_file.eof()) {
		std::string _temp("");
		std::getline(_input_file, _temp);
		//wczytaj linie. Nastepnie dodaj do lancucha wyjsciowego
		//rob tak az nie dojdziesz do konca pliku
		_result += _temp;
		_result += "\n";

		//obsluga podstawowych bledow
		if (_input_file.bad()) {
			std::cerr << "wystapil blad sprzetowy!";
			return nullptr;
		}
		if (_input_file.fail()) {
			std::cerr << "blad podczas wczytywania!";
			return nullptr;
		}
	}

	//zmien stringa na wskaznik na chary i zwroc go w argumencie
	GLchar* _res_tab = new GLchar[_result.size()];
	for (uint i = 0; i < _result.size(); i++)
		_res_tab[i] = _result[i];

	__size = _result.size();
	return _res_tab;
}

void PlayerManager::genVertexBuffer() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//tworze bufor na kordynaty graczy
	glGenBuffers(1, &vertexBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	//bufor typu tablica
	//wielkosc
	//wskaznik na 1 element
	//statyczne rysowanie
	glBufferData(GL_ARRAY_BUFFER, sizeof(corVec[0])*corVec.size() , &corVec[0], GL_STATIC_DRAW);
}

void PlayerManager::LoadAndcompileShaders() {
	if (!(vertSource = loadShader("vertexShaderPlayer.vert", sizeVS)))
		std::cerr << "Nie mozna wczytac vertex shadera!\n";
	if (!(fragSource = loadShader("fragmentShaderPlayer.frag", sizeFS)))
		std::cerr << "Nie mozna wczytac fragment shadera!\n";

	//tworze vertex shader i kompiluje
	 vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertSource, NULL);
	glCompileShader(vertexShader);

	//frag + kompilacja
	 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, NULL);
	glCompileShader(fragmentShader);


	//testujemy czy sie skompilowalo etc
	auto _to_file = [](GLchar* __tab, GLuint __size, std::string __name)->bool {
		std::ofstream _file;
		_file.open(__name);

		if (!_file.is_open()) {
			MessageBox(0, "Nie mozna utworzyc pliku zapisu info log shadera !", 0, 0);
			return false;
		}

		for (uint i = 0; i < __size; i++) {
			_file << __tab[i];
			_file.flush();
		}

		_file.close();
		return true;
	};

	GLint _v_status, _f_status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &_v_status);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &_f_status);

	//info log kompilacji	
	GLchar _v_buffer[512];
	glGetShaderInfoLog(vertexShader, 512, NULL, _v_buffer);
	GLchar _f_buffer[512];
	glGetShaderInfoLog(fragmentShader, 512, NULL, _f_buffer);

	_to_file(_f_buffer, 512, "fragLog.txt");
	_to_file(_v_buffer, 512, "vertexLog.txt");
	if (!_v_status)
		MessageBox(0, "Nie mozna skompilowac vertex shadera!", 0, 0);
	if (!_f_status)
		MessageBox(0, "Nie mozna skompilowac fragment shadera!", 0, 0);

	//tworze caly program shaderowy + link + use
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

void PlayerManager::setLayout() {
	//layout
	 posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	//2 wartosci to pozycja + skok co 5
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	//3 wartosci to kolor + skok co 5, przesuniecie 2 w stosunku do pierwszego elementu
	 colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	_uniform_vec2 = glGetUniformLocation(shaderProgram, "translation");
}

void PlayerManager::draw(uint __number) {
	//numer gracza musi byc wiekszy niz 0 !
	assert(__number > 0);
	Vertex2f _uniform;
	
	_uniform = (*vec)[__number - 1].translate;
	glUniform2f(_uniform_vec2, _uniform.x, _uniform.y);
	_uniform.x = .0f;
	_uniform.y = .0f;
	
	glDrawArrays(
		GL_POLYGON, 
		4 * (__number-1), 
		4);
}

void PlayerManager::drawAll() {
	//renderuje wszystkich graczy na scenie
	for (uint i = 0; i < vec->size(); i++) {
		glDrawArrays(
			GL_POLYGON,
			4 * i,
			4);
	}
}
*/
