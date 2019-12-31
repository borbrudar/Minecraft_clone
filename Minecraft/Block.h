#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"

#include <string>

enum class block_type {
	air,
	dirt
};

class Block {
public:
	//default constructor and function that loads up the grass texture
	Block() = default;
	Block(Shader shader, Texture &texture) {
		loadBlock(shader, texture);
	}
	void loadBlock(Shader shader, Texture &texture);
	//passes shader to model's draw function
	void draw(Shader shader);
	void act(Shader shader);
public:
	bool isVisible = true;
private:
	//vertex and buffer object
	unsigned int VAO, VBO;
	//textures
	unsigned int texture0;
	//optimization and block type
	block_type type = block_type::dirt;
};