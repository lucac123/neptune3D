#pragma once
#include "Entity.h"
#include "TextureField.h"

class Volume : Entity {
private:
	TextureField *densityField;
	unsigned int domainVertexArray, domainVertexBuffer;

public:
	Volume();
	~Volume();

	TextureField* getDensityField();
	TextureField* setDensityField(TextureField* densityField);
};