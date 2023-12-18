#include "TextureField.h"
#include <glad/glad.h>

TextureField::TextureField(int format, int width, int height, int depth) {
	glGenTextures(1, &this->ID);

	this->bind();

	float *data = new float[width * height * depth];
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			for (int k = 0; k < depth; k++) {
				data[i * width + j * height + k * depth] = j;
			}
		}
	}

	glTexImage3D(GL_TEXTURE_3D, 0, format, width, height, depth, 0, GL_RED, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	this->unbind();

	delete[] data;
}

void TextureField::bind(GLenum texture) const {
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_3D, this->ID);
}
void TextureField::unbind(GLenum texture) const {
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_3D, 0);
}
unsigned int TextureField::getID() const {
	return this->ID;
}