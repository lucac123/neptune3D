#pragma once
#include "FrameBuffer.h"
#include "Volume.h"
#include <iostream>

class Neptune {
private:
	Volume *fluidVolume;
public:
	Neptune();
	~Neptune();
	void timeStep(float deltaTime);

	Volume *getVolume();
};