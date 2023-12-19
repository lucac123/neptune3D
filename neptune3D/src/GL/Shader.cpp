#include "Shader.h"

Shader::Shader(const char* vertPath, const char* fragPath) {
	// Compiling shaders
	unsigned int vert = this->compileGLSL(vertPath, GL_VERTEX_SHADER);
	unsigned int frag = this->compileGLSL(fragPath, GL_FRAGMENT_SHADER);

	// Linking shaders into shader program

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vert);
	glAttachShader(this->ID, frag);
	glLinkProgram(this->ID);

	// Check for errors
	int success;
	char log[1024];
	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->ID, 1024, nullptr, log);
		std::cerr << "Failed to link compiled shaders " << vertPath << " and " << fragPath << std::endl << log << std::endl;
	}

	// Cleanup
	glDeleteShader(vert);
	glDeleteShader(frag);
}

Shader::Shader(const char* vertPath, const char* geomPath, const char* fragPath) {
	// Compiling shaders
	unsigned int vert = this->compileGLSL(vertPath, GL_VERTEX_SHADER);
	unsigned int geom = this->compileGLSL(geomPath, GL_GEOMETRY_SHADER);
	unsigned int frag = this->compileGLSL(fragPath, GL_FRAGMENT_SHADER);

	// Linking shaders into shader program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, vert);
	glAttachShader(this->ID, geom);
	glAttachShader(this->ID, frag);
	glLinkProgram(this->ID);

	// Check for errors
	int success;
	char log[1024];
	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->ID, 1024, nullptr, log);
		std::cerr << "Failed to link compiled shaders " << vertPath << ", " << geomPath << ", and " << fragPath << std::endl << log << std::endl;
	}

	// Cleanup
	glDeleteShader(vert);
	glDeleteShader(geom);
	glDeleteShader(frag);
}
Shader::~Shader() {
	glDeleteProgram(this->ID);
}

unsigned int Shader::getID() const {
	return this->ID;
}

void Shader::use() const {
	glUseProgram(this->ID);
}

void Shader::setUniform(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::setUniform(const char* name, float value) const {
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::setUniform(const char* name, float v1, float v2) const {
	glUniform2f(glGetUniformLocation(this->ID, name), v1, v2);
}
void Shader::setUniform(const char* name, unsigned int v1, unsigned int v2) const {
	glUniform2ui(glGetUniformLocation(this->ID, name), v1, v2);
}

void Shader::setUniform(const char* name, glm::vec3& vec) const {
	glUniform3f(glGetUniformLocation(this->ID, name), vec.x, vec.y, vec.z);
}

void Shader::setUniform(const char* name, float v1, float v2, float v3) const {
	glUniform3f(glGetUniformLocation(this->ID, name), v1, v2, v3);
}

void Shader::setUniform(const char* name, glm::mat4& mat) const {
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::compileGLSL(const char* filePath, GLenum shaderType) const {
	std::string *fileString = ResourceManager::readShader(filePath);
	const char* code = fileString->c_str();
	
	// Create and compile shader
	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);
	delete fileString;

	// Check errors
	int success;
	char log[1024];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 1024, nullptr, log);
		std::cerr << "Failed to compile " << filePath << std::endl << log << std::endl;
	}

	return shader;
}