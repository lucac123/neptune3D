#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera {
private:
	// Position attributes
	glm::vec3 target, position, front, up, right;

	// Spherical angles;
	float distance, phi, theta;

	// Options
	float speed, zoom, sensitivity, aspectRatio;

public:
	Camera(glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f), float distance = 3.0f, float phi = glm::radians(45.0f), float theta = glm::radians(45.0f), float aspectRatio = 1920.0f/1080.0f);

	glm::mat4 getViewMatrix();
	float getZoom();
	float getAspectRatio();

	void move(float deltaX, float deltaY);
	void pan(float deltaX, float deltaY);

private:
	void update_vectors();
};