#include "PlayerManager.h"

const GLchar* vertexSource =
"#version 150 core\n"
"in vec2 position;"
"in vec3 color;"
"out vec3 Color;"
"uniform vec2 translation;"
"void main() {"
"   Color = color;"
"   gl_Position = vec4(position.x+translation.x, position.y+translation.y, 0.0, 1.0);"
"}";
const GLchar* fragmentSource =
"#version 150 core\n"
"in vec3 Color;"
"out vec4 outColor;"
"void main() {"
"   outColor = vec4(Color, 1.0);"
"}";

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
	//tworze vertex shader i kompiluje
	 vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	//frag + kompilacja
	 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
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