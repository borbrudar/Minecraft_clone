#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Camera.h"

class State {
public:
	virtual void draw(Shader shader) = 0;
	virtual void processInput(GLFWwindow *window, Camera &camera, float deltaTime) = 0;
};