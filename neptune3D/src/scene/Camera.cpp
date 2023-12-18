#include "Camera.h"

Camera::Camera(glm::vec3 target, float distance, float phi, float theta, float aspectRatio)
	: target(target), distance(distance), phi(phi), theta(theta), up(glm::vec3(0, 1, 0)), speed(2.5f), zoom(45.0f), sensitivity(0.01f), aspectRatio(aspectRatio) {
	update_vectors();
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(this->position, this->position + this->front, this->up);
}

float Camera::getZoom() {
	return this->zoom;
}

float Camera::getAspectRatio() {
	return this->aspectRatio;
}

void Camera::move(float deltaX, float deltaY) {

}

void Camera::pan(float deltaX, float deltaY) {
	deltaX *= this->sensitivity;
	deltaY *= this->sensitivity;

	this->theta -= deltaX;
	this->phi += deltaY;

	update_vectors();
}

void Camera::update_vectors() {
	this->position.x = this->distance * sin(this->phi) * sin(this->theta);
	this->position.y = this->distance * cos(this->phi);
	this->position.z = this->distance * sin(this->phi) * cos(this->theta);
	this->front = glm::normalize(this->target - this->position);

	this->right.x = cos(this->theta);
	this->right.z = -sin(this->theta);
	this->right.y = 0;

	this->up = glm::cross(this->right, this->front);
}