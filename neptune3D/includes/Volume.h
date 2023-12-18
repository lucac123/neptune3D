#pragma once
#include "Entity.h"
#include "TextureField.h"

class Volume : Entity {
private:
	TextureField *densityField;
	unsigned int domainVertexArray, domainVertexBuffer;

public:
	Volume(TextureField *densityField);
	~Volume();

	TextureField* getDensityField();
	void setDensityField(TextureField* densityField);

	void bind();
};