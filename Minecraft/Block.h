#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"
#include "Block_Heavy.h"

#include <string>

enum class block_type {
	air,
	dirt
};

class Block {
public:
	//constructor  
	Block() = default;
	//function that loads up the grass texture
	void loadBlock(Shader shader, Block_Heavy& data);
	//passes shader to model's draw function
	void draw(Shader shader);
	void act(Shader shader);
public:
	bool isVisible = true;
	//block type
	block_type type = block_type::dirt;
	//other shit idc tbh
	glm::mat4 model = glm::mat4(1.f);
	int x, y, z;
private:
	//vertex and buffer object
	unsigned int VAO, VBO;
	//textures
	unsigned int texture0;
};