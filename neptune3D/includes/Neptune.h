#pragma once
#include "FrameBuffer.h"
#include "Volume.h"
#include "Shader.h"
#include "FrameBuffer.h"

#include <iostream>

class Neptune {
private:
	Volume *fluidVolume;
	TextureField* volumeField;
	Shader* neptuneShader;
	FrameBuffer* framebuffer;

	int resolution;
public:
	Neptune(int resolution);
	~Neptune();
	void timeStep(float deltaTime);

	Volume *getVolume();
};