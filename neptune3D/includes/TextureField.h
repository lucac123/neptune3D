#pragma once
#include <glad/glad.h>

class TextureField
{
private:
	unsigned int ID;

public:
	TextureField(int format, int width, int height, int depth);

	void bind(GLenum texture = GL_TEXTURE0) const;
	void unbind(GLenum texture = GL_TEXTURE0) const;

	unsigned int getID() const; //Returns ID corresponding with this texture
};

