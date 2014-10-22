#include "PlayerManager.h"

const GLchar* vertexSource =
"#version 150 core\n"
"in vec2 position;"
"in vec3 color;"
"out vec3 Color;"
"void main() {"
"Color = color;"
"   gl_Position = vec4(position, 0.0, 1.0);"
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
		corVec.push_back(itr->xy1.x);
		corVec.push_back(itr->xy1.y);
		corVec.push_back(itr->color.x);
		corVec.push_back(itr->color.y);
		corVec.push_back(itr->color.z);

		corVec.push_back(itr->xy2.x);
		corVec.push_back(itr->xy2.y);
		corVec.push_back(itr->color.x);
		corVec.push_back(itr->color.y);
		corVec.push_back(itr->color.z);

		corVec.push_back(itr->xy3.x);
		corVec.push_back(itr->xy3.y);
		corVec.push_back(itr->color.x);
		corVec.push_back(itr->color.y);
		corVec.push_back(itr->color.z);

		corVec.push_back(itr->xy4.x);
		corVec.push_back(itr->xy4.y);
		corVec.push_back(itr->color.x);
		corVec.push_back(itr->color.y);
		corVec.push_back(itr->color.z);
	}
	std::cout << corVec.size();
}

PlayerManager::~PlayerManager() {
	glDeleteBuffers(1, &vertexBufferId);
}

void PlayerManager::genVertexBuffer() {
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);


	float* tmp = new float[corVec.size()];
	uint i = 0;
	for (auto itr = corVec.begin(); itr != corVec.end(); ++itr) {
		tmp[i] = *itr;
		++i;
	}
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(float)*corVec.size(), 
		static_cast<const void*>(tmp), 
		GL_STATIC_DRAW);
	delete tmp;
}

void PlayerManager::LoadAndcompileShaders() {
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
}

void PlayerManager::setLayout() {
	posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);

	glVertexAttribPointer(
		posAttrib,
		2,
		GL_FLOAT, GL_FALSE,
		5 * sizeof(float),
		0);

	colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(
		colAttrib,
		3,
		GL_FLOAT, GL_FALSE,
		5 * sizeof(float),
		(void*)(2 * sizeof(float)));
}

void PlayerManager::draw() {
	glDrawArrays(GL_TRIANGLES, 0, 4);
}