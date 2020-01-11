#pragma once
#include "Shader.h"
#include <GLFW/glfw3.h>

class Light {
public:
	void update(Shader shader) {
		lightPos.x = 18;
		lightPos.z = abs(std::sin(glfwGetTime() / 8)) * 36; // * is number of blocks
		lightPos.y = 50 * std::sin(glfwGetTime() / 4);      // / has to be 2x on z than y

		if (lightPos.y < 0) lightColor = glm::vec3(0, 0, 0);
		else lightColor = glm::vec3(1, 1, 1);

		shader.setVec3("lightColor", lightColor);
		shader.setVec3("lightPos", lightPos);
	}
private:
	glm::vec3 lightColor;
	glm::vec3 lightPos = glm::vec3(15,10,15);
};