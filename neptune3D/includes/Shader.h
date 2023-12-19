#pragma once
#include <glad/glad.h>
#include <glm.hpp>

#include <string>

#include "ResourceManager.h"

class Shader {
private:
	unsigned int ID;

public:
	Shader(const char* vertPath, const char* fragPath);
	Shader(const char* vertPath, const char* geomPath, const char* fragPath);
	~Shader();

	void use() const;

	// SET UNIFORMS
	void setUniform(const char* name, int value) const; //Samplers and integers, and booleans
	void setUniform(const char* name, float value) const; //Floats
	void setUniform(const char* name, float v1, float v2) const; //Float vector
	void setUniform(const char* name, unsigned int v1, unsigned int v2) const; //Int vector
	void setUniform(const char* name, float v1, float v2, float v3) const;
	void setUniform(const char* name, glm::vec3& vec) const; // 3 Float vector
	void setUniform(const char* name, glm::mat4& mat) const; // Mat 4

	unsigned int getID() const; //Returns the ID corresponding with this shader

private:
	unsigned int compileGLSL(const char* filePath, GLenum shaderType) const;
};