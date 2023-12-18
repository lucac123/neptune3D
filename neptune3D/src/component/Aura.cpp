#include "Aura.h"
#include<iostream>

Aura::Aura() {
	this->shader = new Shader("C:/Users/lchac/source/repos/neptune3D/neptune3D/shaders/vert/aura.vert", "C:/Users/lchac/source/repos/neptune3D/neptune3D/shaders/frag/aura.frag");
}

Aura::~Aura() {
	delete this->shader;
}

void Aura::render(Camera* camera, Volume *volume) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	volume->bind();
	this->shader->use();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(camera->getZoom()), camera->getAspectRatio(), 0.1f, 100.0f);

	this->shader->setUniform("uModel", model);
	this->shader->setUniform("uView", view);
	this->shader->setUniform("uProjection", projection);

	glDrawArrays(GL_TRIANGLES, 0, 36);
}
