#pragma once
#include "FrameBuffer.h"
#include "Volume.h"
#include "Shader.h"
#include "FrameBuffer.h"

#include <iostream>

class Neptune {
private:
	unsigned int emptyVertexArray;

	Volume *fluidVolume;
	FrameBuffer* framebuffer;

	// Shaders
	Shader* addForceShader, *advectShader, *diffuseShader, *copyShader;

	// Field data
	TextureField* velocity, * velocityOut;
	TextureField* pressure, * pressureOut;
	TextureField* velocityDivergence;

	TextureField* substance, * substanceOut;

	int resolution;
public:
	Neptune(int resolution);
	~Neptune();
	void timeStep(float deltaTime);

	Volume *getVolume();

private:
	void generateTextureFields();
	void generateShaders();

	void velocityStep(float deltaTime);
	void substanceStep(float deltaTime);

	void addForce(TextureField *inputField, TextureField *outputField, float deltaTime);
	void advect(TextureField* inputField, TextureField* outputField, float deltaTime);
	void diffuse(TextureField* inputField, TextureField* outputField, float deltaTime);
	void project(TextureField* inputField, TextureField* outputField, float deltaTime);
	void copy(TextureField* field1, TextureField* field2);
};