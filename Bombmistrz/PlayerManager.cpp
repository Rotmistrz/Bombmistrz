#include "PlayerManager.h"

PlayerManager::PlayerManager(std::vector<Player>* __vec) {
	vec = new std::vector<Player>(*__vec);

	for (auto itr = vec->begin(); itr != vec->end(); ++itr) {
		std::vector<float> _tmp = itr->giveFloatVec();
		for (auto itr2 = _tmp.begin(); itr2 != _tmp.end(); ++itr2) {
			corVec.push_back(*itr2);
		}
	}
}

PlayerManager::~PlayerManager() {
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

Player* PlayerManager::getPlayer(uint __number)	{
	assert(__number > 0);
	uint i = 0;
	for (; i < vec->size(); i++) {
		if (i == __number - 1)
			return &((*vec)[i]);
	}

	return nullptr;
}