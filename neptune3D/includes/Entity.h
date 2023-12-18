#pragma once
#include <glm.hpp>

class Entity {
protected:
	glm::vec3 *position;
public:
	Entity();
	~Entity();

	glm::vec3 *getPosition();
	void setPosition(glm::vec3 position);
};