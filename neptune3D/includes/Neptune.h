#pragma once
#include "FrameBuffer.h"
#include "Volume.h"
#include "Shader.h"
#include "FrameBuffer.h"
#include <glm.hpp>

#include <iostream>

class Neptune {
private:
	unsigned int emptyVertexArray;

	Volume *fluidVolume;
	FrameBuffer* framebuffer;

	// Shaders
	Shader* addForceShader, *advectShader, *jacobiShader, *divergenceShader, *subtractGradientShader, *copyShader;
	Shader* addSubstanceShader;

	// Field data
	TextureField* velocity, * velocityOut;
	TextureField* pressure, * pressureOut;
	TextureField* velocityDivergence;

	TextureField* substance, * substanceOut;

	// Simulation options
	float cellSize, viscosity;
	int resolution;
public:
	Neptune(int resolution, float cellSize = 1.0f, float viscosity = 0.0001f);
	~Neptune();
	void timeStep(float deltaTime);

	Volume *getVolume();

private:
	void generateTextureFields();
	void generateShaders();

	void velocityStep(float deltaTime);
	void substanceStep(float deltaTime);

	void addForce(TextureField* inputField, TextureField* outputField, float deltaTime, glm::vec3 forcePos, glm::vec3 force = glm::vec3(0.0f, 10.0f, 0.0f), float forceRadius = 100.0f);
	void advect(TextureField* inputField, TextureField* outputField, float deltaTime);
	void diffuse(TextureField* inputField, TextureField* outputField, float deltaTime);
	void project(TextureField* inputField, TextureField* outputField, float deltaTime);
	void copy(TextureField* field1, TextureField* field2);

	void calculateDivergence(TextureField* inputField);
	void calculatePressure();
	void calculateBoundary();

	void addSubstance(TextureField* inputField, TextureField* outputField, float deltaTime, glm::vec3 position, float amount = 10.0f, float radius = 100.0f);
	void transport(TextureField* inputField, TextureField* transportField, TextureField *outptuField, float deltaTime);
	void dissipate(TextureField* inputField, TextureField* outputField, float deltaTime);
};