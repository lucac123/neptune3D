#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Scene.h"
#include "Neptune.h"

const unsigned short WIN_WIDTH = 1920;
const unsigned short WIN_HEIGHT = 1080;

int main() {
	/** WINDOW SETUP **/
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Neptune", nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	/** OPENGL FUNCTION POINTER SETUP **/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Didn't get GLAD. Got mad. Failed to load OpenGL function pointers" << std::endl;
		return -1;
	}

	/** CREATE SCENE **/
	Scene scene = Scene();

	/** RENDER LOOP **/
	float lastFrame = static_cast<float>(glfwGetTime());
	float deltaTime = 0;
	while (!glfwWindowShouldClose(window)) {
		// time step
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Delegate rendering to Scene object
		scene.render();
		scene.timeStep(deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "Done rendering" << std::endl;

	return 0;
}