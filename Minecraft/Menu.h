#pragma once
#include "State.h"
#include "Camera.h"
#include "Texture.h"


class Menu : public State {
public:
	Menu(Shader shader) {
		std::vector<std::string> string;
		string.push_back("textures/menu.jpg");

		tex.loadTexture(string, string.size());

		loadMenu(shader);
	}
	void draw(Shader shader);
	void processInput(GLFWwindow *window, Camera &camera, float deltaTime) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	};
	void loadMenu(Shader shader);

	//variables
	float vertices[30]{
		-1.f, -1.f,  0.5f,  0.0f, 0.0f,
		1.f, -1.f,  0.5f,  1.0f, 0.0f,
		1.f,  1.f,  0.5f,  1.0f, 1.0f,
		1.f,  1.f,  0.5f,  1.0f, 1.0f,
		-1.f,  1.f,  0.5f,  0.0f, 1.0f,
		-1.f, -1.f,  0.5f,  0.0f, 0.0f
	};
	Texture tex;
	//vertex and buffer object; texture (change also in texture.h)
	unsigned int VAO, VBO, texture;
};