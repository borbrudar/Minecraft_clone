#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Block_Heavy.h"


class block_type {
public:
	enum class type {
		dirt,
		stone,
		tree,
		leaf,
		sand,
		cactus, 
		water, 
		snow, 
		ice
	};
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
	block_type::type type = block_type::type::tree;
};