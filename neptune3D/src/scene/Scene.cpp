#include "Scene.h"
#include "Neptune.h"
#include "Aura.h"
#include "Camera.h"
#include <glad/glad.h>
#include <iostream>

Scene::Scene() {
	this->neptune = new Neptune();
	this->aura = new Aura();
	this->backgroundColor = new glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);

	this->camera = new Camera();
}

Scene::~Scene() {
	delete this->fluidComponent;
	delete this->volumeRenderer;
	delete this->backgroundColor;

	delete this->camera;
}

void Scene::timeStep(float deltaTime) {
	
}

void Scene::render() {
	glClearColor(this->backgroundColor->x, this->backgroundColor->y, this->backgroundColor->z, this->backgroundColor->w);
	glClear(GL_COLOR_BUFFER_BIT);

	this->aura->render(this->camera, this->neptune->getVolume());
}