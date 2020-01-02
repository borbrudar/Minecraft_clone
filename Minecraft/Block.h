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
	//default constructor and function that loads up the grass texture
	Block() = default;
	//passes shader to model's draw function
	void draw(Shader shader, Block_Heavy &data);
public:
	bool isVisible = true;
	int x, y, z;
private:
	//block type
	block_type type = block_type::dirt;
};