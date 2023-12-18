#include "Entity.h"

Entity::Entity() {
	this->position = new glm::vec3(0, 0, 0);
}

Entity::~Entity() {
	delete this->position;
}

glm::vec3 *Entity::getPosition() {
	return this->position;
}

void Entity::setPosition(glm::vec3 position) {
	delete this->position;
	this->position = new glm::vec3(position);
}