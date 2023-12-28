#include "Scene.h"
#include "Neptune.h"
#include "Aura.h"
#include "Camera.h"
#include <glad/glad.h>
#include <iostream>

Scene::Scene() {
	this->neptune = new Neptune(128);
	this->aura = new Aura();
	this->backgroundColor = new glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);

	this->camera = new Camera();
}

Scene::~Scene() {
	delete this->neptune;
	delete this->aura;
	delete this->backgroundColor;

	delete this->camera;
}

Camera* Scene::getCamera() {
	return this->camera;
}

void Scene::timeStep(float deltaTime) {
	this->neptune->timeStep(deltaTime);
}

void Scene::render() {
	glClearColor(this->backgroundColor->x, this->backgroundColor->y, this->backgroundColor->z, this->backgroundColor->w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, 1920, 1080);
	this->aura->render(this->camera, this->neptune->getVolume());
}