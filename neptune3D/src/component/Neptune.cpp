#include "Neptune.h"
#include "Volume.h"

float* generateScalarField(int width, int height, int depth, float scale);

Neptune::Neptune() {
    float* data = generateScalarField(128, 128, 128, 1.0f);
	this->volumeField = new TextureField(data, GL_RGB, 128, 128, 128);
	this->fluidVolume = new Volume(this->volumeField);

	delete[] data;
}
Neptune::~Neptune() {
	delete this->fluidVolume;
	delete this->volumeField;
}

void Neptune::timeStep(float deltaTime) {
	
}

Volume *Neptune::getVolume() {
	return this->fluidVolume;
}


float* generateScalarField(int width, int height, int depth, float scale) {
    float* field = new float[height * width * depth * 3];
    float threshold = 0.3f;
    int index = 0;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            for (int k = 0; k < depth; k++) {
                field[index++] = i/128.0f;
                field[index++] = j/128.0f;
                field[index++] = k/128.0f;
            }
    return field;
}