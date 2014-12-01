#include "Game.h"

Game::Game(
	const std::shared_ptr<PlayerManager>& __players, 
	const std::shared_ptr<Map>& __map,
	const std::shared_ptr<BombManager>& __bombs,
	uint __w, 
	uint __h)
: width(__w), height(__h), playerManager(__players), map(__map) {
	if (playerManager == nullptr)
		MessageBox(0, "wskaznik na obiekt PlayerManager jest rowny NULL. Zaladuj ponownie obiekt!", 0, 0);
	if (map == nullptr)
		MessageBox(0, "wskaznik na obiekt Map jest rowny NULL. Zaladuj ponownie obiekt!", 0, 0);
	if (__bombs == nullptr)
		MessageBox(0, "wskaznik na obiekt BombManager jest rowny NULL. Zaladuj ponownie obiekt!", 0, 0);
	bombManager = __bombs;
		/*std::make_unique<BombManager>(BombManager(
		Vertex2f{ static_cast<float>(__w) / 2.0f, static_cast<float>(__h) / 2.0f }, 
		playerManager->getPlayer(1)->getSide(), 
		Vertex3f{ .0f, 1.0f, 1.0f }, 
		width, 
		height));*/
}

Game::Game(uint __w, uint __h)
: width(__w), height(__h) {
		/*std::make_unique<BombManager>(BombManager(
		Vertex2f{ .0f, .0f },
		playerManager->getPlayer(1)->getSide(),
		Vertex3f{ .0f, 1.0f, 1.0f },
		width,
		height));*/
}

Game::~Game() {
	glDeleteBuffers(1, &vertexBufferId);
	glDeleteBuffers(1, &bombBufferId);
	glDeleteTextures(2, texturesId);
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
//	GLuint vao;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);

	//tworze bufor na kordynaty graczy
	glGenBuffers(1, &bombBufferId);
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
	//tworzenie bufora typu GL_ARRAY_BUFFER, o pojemnosci graczy + mapy
	glBufferData(
		GL_ARRAY_BUFFER,
		_full_size,
		nullptr,
		GL_STATIC_DRAW);
	
	// przekazywanie wspolrzednych graczy + kolorow do bufora.
	if (playerManager != nullptr) {
		glBufferSubData(
			GL_ARRAY_BUFFER,
			0, //offset
			playerManager->GetSizeInBytes(), //wielkosc w bajtach
			playerManager->getFirstTabElement()); //wskaznik na 1 element
	}
	//to samo tylko z mapa
	if (map != nullptr) {
		glBufferSubData(
			GL_ARRAY_BUFFER,
			playerManager->GetSizeInBytes(),
			map->GetSizeInBytes(),
			map->getFirstTabElement());
	}

	//osobny bufor na koordynaty bomb etc.
	glBindBuffer(GL_ARRAY_BUFFER, bombBufferId);
	glBufferData(
		GL_ARRAY_BUFFER, 
		bombManager->GetSizeInBytes(), 
		bombManager->getFirstTabElement(), 
		GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
	const GLint _size_vs = sizeVS;
	const GLint _size_fs = sizeFS;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertSource, &_size_vs);	
	glCompileShader(vertexShader);

	//frag + kompilacja
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragSource, &_size_fs);
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
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//layout
	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	//2 wartosci to pozycja + skok co 5
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
	//3 wartosci to kolor + skok co 5, przesuniecie 2 w stosunku do pierwszego elementu
	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	texAttrib = glGetAttribLocation(shaderProgram, "texture");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	uniformPlayers = glGetUniformLocation(shaderProgram, "translation");
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/**************************************************/
	glBindBuffer(GL_ARRAY_BUFFER, bombBufferId);
	glGenVertexArrays(1, &bombVao);
	glBindVertexArray(bombVao);


	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	//2 wartosci to pozycja + skok co 5
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), 0);
	//3 wartosci to kolor + skok co 5, przesuniecie 2 w stosunku do pierwszego elementu
	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	texAttrib = glGetAttribLocation(shaderProgram, "texture");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));

	uniformBomb = glGetUniformLocation(shaderProgram, "translation");
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Game::bindAndUploadTex() {
	glGenTextures(3, texturesId);

//	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturesId[0]);
	bool _result = imgData.loadFromFile("images/Kafelki/SoftBlock2.png");
	
	if (!_result)
		MessageBox(0, "Nie mozna wczytac tekstury mapy!", 0, 0);
	
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		imgData.getSize().y,
		imgData.getSize().x,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgData.getPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_2D);

	/*********************************************/

//	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturesId[1]);
	bool _result_2 = imgData.loadFromFile("images/Ludzik/Bombmistrz - projekt ludzika.jpg");

	if (!_result_2)
		MessageBox(0, "Nie mozna wczytac tektrusty gracza!", 0, 0);
	//wczytanie jpg do bufora
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		imgData.getSize().y,
		imgData.getSize().x,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgData.getPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_2D);

	/*********************************************/

	glBindTexture(GL_TEXTURE_2D, texturesId[2]);
	bool _result_3 = imgData.loadFromFile("images/Kafelki/Bomb.png");

	if (!_result_3)
		MessageBox(0, "Nie mozna wczytac tektrusty gracza!", 0, 0);
	//wczytanie jpg do bufora
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		imgData.getSize().y,
		imgData.getSize().x,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgData.getPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glDisable(GL_TEXTURE_2D);
}

void Game::draw(uint __number) {
	//numer gracza musi byc wiekszy niz 0 !
	assert(__number > 0);
	Vertex2f _uniform;
	//pobieranie uniformu od gracza
	_uniform = playerManager->getPlayer(__number)->translate;
	//przekazywanie uniformu do vertex shadera - juz po aktualizacji
	//uniform - wektor przesuniecia gracza
	glUniform2f(uniformPlayers, _uniform.x, _uniform.y);
	_uniform.x = .0f;
	_uniform.y = .0f;

	glDrawArrays(
		GL_POLYGON,
		4 * (__number - 1),
		4);
}

void Game::drawBombs() {
	glBindTexture(GL_TEXTURE_2D, texturesId[2]);
	Vertex2f _uniform{ .0f, .0f };

	//petla iteruje po wszystkich bombach az natrafi na pierwsz nieaktywna. Oznacza to
	//,ze reszta dalszych bomb tez jest nieaktywna i mozna zakonczyc iteracje
	for (uint i = 0; i < bombManager->getSize(); i++) {
		auto _b = bombManager->getBomb(i);

		if (!_b->isActive())
			continue;

		//pobiera uniforma bomby
		_uniform = _b->getUniform();
		//update uniforma w shaderze

		glUniform2f(uniformBomb, _uniform.x, _uniform.y);

		//rendering
		glDrawArrays(
			GL_POLYGON,
			4 * i,
			4);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::drawPlayers() {
	glBindTexture(GL_TEXTURE_2D, texturesId[1]);
	if (playerManager != nullptr) {
		for (uint i = 1; i <= playerManager->getSize(); i++)
			draw(i);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::drawMap() {
	glBindTexture(GL_TEXTURE_2D, texturesId[0]);
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
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Game::drawAll() {
	glBindVertexArray(bombVao);
	drawBombs();
	glBindVertexArray(0);
	
	glBindVertexArray(vao);
	drawMap();
	drawPlayers();
	glBindVertexArray(0);
}

void Game::setBomb(Vertex2f __pos) {
	bombManager->setBomb(__pos);
}