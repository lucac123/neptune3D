#include "Neptune.h"
#include "Volume.h"

Neptune::Neptune() {
	this->fluidVolume = new Volume();
}
Neptune::~Neptune() {
	delete this->fluidVolume;
}

void Neptune::timeStep(float deltaTime) {
	
}

Volume *Neptune::getVolume() {
	return this->fluidVolume;
}