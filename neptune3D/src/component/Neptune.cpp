#include "Neptune.h"
#include "Volume.h"

Neptune::Neptune() {
	float *data = new float[128*128*128];
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			for (int k = 0; k < 128; k++) {
				data[i * 128 * 128 + j * 128 + k] = j;
			}
		}
	}
	this->volumeField = new TextureField(data, GL_R16F, 128, 128, 128);
	this->fluidVolume = new Volume(this->volumeField);

	//delete[] data;
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