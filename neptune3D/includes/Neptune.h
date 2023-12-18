#pragma once
#include "FrameBuffer.h"
#include "Volume.h"
#include <iostream>

class Neptune {
private:
	Volume *fluidVolume;
	TextureField* volumeField;
public:
	Neptune();
	~Neptune();
	void timeStep(float deltaTime);

	Volume *getVolume();
};