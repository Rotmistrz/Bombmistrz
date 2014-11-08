#include "Game.h"

Game::Game(PlayerManager* __players, Map* __map)
: playerManager(__players), map(__map) {
	if (playerManager == nullptr)
		MessageBox(0, "wskaznik na obiekt PlayerManager jest rowny NULL. Zaladuj ponownie obiekt!", 0, 0);
	if (map == nullptr)
		MessageBox(0, "wskaznik na obiekt Map jest rowny NULL. Zaladuj ponownie obiekt!", 0, 0);
}

Game::Game() {
}

Game::~Game() {
	glDeleteBuffers(1, &vertexBufferId);

	glUseProgram(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Game::genVertexBuffer() {
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
	uint _full_size = 0;
	if (playerManager && map)
		_full_size = playerManager->GetSizeInBytes() + map->GetSizeInBytes();
	else
	if (map != nullptr)
		_full_size = map->GetSizeInBytes();
	else
		_full_size = playerManager->GetSizeInBytes();

	glBufferData(
		GL_ARRAY_BUFFER,
		_full_size,
		nullptr,
		GL_STATIC_DRAW);

	if (playerManager != nullptr) {
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0, //offset
			playerManager->GetSizeInBytes(), //wielkosc
			playerManager->getFirstTabElement()); //wskaznik na 1 element
	}
	if (map != nullptr) {
		glBufferSubData(
			GL_ARRAY_BUFFER,
			playerManager->GetSizeInBytes(),
			map->GetSizeInBytes(),
			map->getFirstTabElement());
	}
}

GLchar* Game::loadShader(
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

void Game::LoadAndcompileShaders() {
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

void Game::setLayout() {
	//layout
	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	//2 wartosci to pozycja + skok co 5
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
	//3 wartosci to kolor + skok co 5, przesuniecie 2 w stosunku do pierwszego elementu
	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	uniformPlayers = glGetUniformLocation(shaderProgram, "translation");
}

void Game::draw(uint __number) {
	//numer gracza musi byc wiekszy niz 0 !
	assert(__number > 0);
	Vertex2f _uniform;

	_uniform = playerManager->getPlayer(__number)->translate;
	glUniform2f(uniformPlayers, _uniform.x, _uniform.y);
	_uniform.x = .0f;
	_uniform.y = .0f;

	glDrawArrays(
		GL_POLYGON,
		4 * (__number - 1),
		4);
}

void Game::drawAll() {
	//renderuje wszystkich graczy na scenie
	/*
	for (uint i = 0; i < playerManager->getSize(); i++) {
		glDrawArrays(
			GL_POLYGON,
			4 * i,
			4);
	}*/

	if (playerManager != nullptr) {
		for (uint i = 1; i <= playerManager->getSize(); i++)
			draw(i);
	}
	if (map != nullptr) {
		Vertex2f _uniform{ .0f, .0f };
		glUniform2f(uniformPlayers, _uniform.x, _uniform.y);

		uint _offset = playerManager->getSize() * 4;
		for (uint i = 0; i < map->getSize(); i++) {
			glDrawArrays(
				GL_POLYGON,
				4 * i + _offset,
				4);
		}
	}
}
