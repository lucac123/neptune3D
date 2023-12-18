#pragma once
#include<vector>
#include<glm.hpp>
#include "Neptune.h"
#include "Aura.h"
#include "Camera.h"

class Scene {
private:
	glm::vec4 *backgroundColor;

	Neptune *neptune;
	Aura *aura;

	Camera* camera;
public:
	Scene();
	~Scene();


	void timeStep(float deltaTime);
	void render();
};