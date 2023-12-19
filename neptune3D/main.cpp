#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Scene.h"
#include "Neptune.h"

enum SceneState {
	NORMAL,
	CAMERA_PAN
} state;

const unsigned short WIN_WIDTH = 1920;
const unsigned short WIN_HEIGHT = 1080;

Camera* sceneCamera = nullptr;
float cursorX, cursorY;
float cursorLastX, cursorLastY;

void cursorPosCallback(GLFWwindow* window, double x, double y);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

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

	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	glfwSetCursor(window, cursor);

	/** OPENGL FUNCTION POINTER SETUP **/
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Didn't get GLAD. Got mad. Failed to load OpenGL function pointers" << std::endl;
		return -1;
	}

	/** CREATE SCENE **/
	Scene scene = Scene();
	sceneCamera = scene.getCamera();

	/** RENDER LOOP **/
	float lastFrame = static_cast<float>(glfwGetTime());
	float deltaTime = 0;
	while (!glfwWindowShouldClose(window)) {
		// time step
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Delegate rendering to Scene object
		scene.timeStep(deltaTime);
		scene.render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	std::cout << "Done rendering" << std::endl;

	return 0;
}

void cursorPosCallback(GLFWwindow* window, double x, double y) {
	cursorX = x;
	cursorY = y;
	if (state == CAMERA_PAN) {
		sceneCamera->pan(cursorX - cursorLastX, cursorLastY-cursorY);
	}
	cursorLastX = cursorX;
	cursorLastY = cursorY;
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_1) {
		if (action == GLFW_PRESS && mods == GLFW_MOD_ALT) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			state = CAMERA_PAN;
		}
		else if (action == GLFW_RELEASE) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			state = NORMAL;
		}
	}
}