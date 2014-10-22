#include "PlayerManager.h"

const GLchar* vertexSource =
"#version 150 core\n"
"in vec2 position;"
"in vec3 color;"
"out vec3 Color;"
"void main() {"
"   Color = color;"
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
//	glDeleteBuffers(1, &vertexBufferId);
}

void PlayerManager::genVertexBuffer() {
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertexBufferId);

	GLfloat vertices[] = {
		-0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f, 0.0f
	};

	GLfloat* vec1 = new GLfloat[15];
	uint i = 0;
	std::cout << "\n\n";
	for (auto itr = corVec.begin(); itr != corVec.end(); ++itr) {
		if (i == 15)
			break;
		vec1[i] = *itr;
		std::cout << vec1[i] << "\n";
		vertices[i] = vec1[i];
		++i;
	}

	std::cout << "\n\n";

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(corVec[0])*corVec.size() , &corVec[0], GL_STATIC_DRAW);
}

void PlayerManager::LoadAndcompileShaders() {
	// Create and compile the vertex shader
	 vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile the fragment shader
	 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// Link the vertex and fragment shader into a shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	
}

void PlayerManager::setLayout() {
	 posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

	 colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	
}
void PlayerManager::draw() {
	glDrawArrays(GL_POLYGON, 0, 4);
}