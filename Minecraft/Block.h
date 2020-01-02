#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Block_Heavy.h"


enum class block_type {
	air,
	dirt
};

class Block {
public:
	//draw's the block 
	void draw(Shader shader, Block_Heavy &data);
public:
	//pos and if not visible, it wont draw
	bool isVisible = true;
	int x, y, z;
	//block type
	block_type type = block_type::dirt;
};