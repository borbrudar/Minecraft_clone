#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Texture.h"
#include <vector>
#include <string>

class Block_Heavy {
public:
//functions
	Block_Heavy() {
		std::vector<std::string> textures;
		textures.push_back("textures/grass.jpg");
		textures.push_back("textures/stone.jpg");
		textures.push_back("textures/tree.jpg");
		textures.push_back("textures/leaf.jpg");
		textures.push_back("textures/sand.jpg");
		textures.push_back("textures/cactus.jpg");
		textures.push_back("textures/water.jpg");
		textures.push_back("textures/snow.jpg");
		textures.push_back("textures/ice.jpg");

		tex.loadTexture(textures, textures.size());

		texture.resize(textures.size());
	}
	//loads up the texture to vao
	void loadBlock(Shader shader);
//variables
	//cube vertices
	float vertices[288] = { // pos 3, tex 2, normal vec 3
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,    0.f, 0.f, -1.f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,	0.f, 0.f, -1.f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.f, 0.f, -1.f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.f, 0.f, -1.f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.f, 0.f, -1.f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	0.f, 0.f, -1.f,

	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.f, 0.f, 1.f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.f, 0.f, 1.f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	0.f, 0.f, 1.f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	0.f, 0.f, 1.f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,	0.f, 0.f, 1.f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.f, 0.f, 1.f,

	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	-1.f, 0.f, 0.f,
	   -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	-1.f, 0.f, 0.f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	-1.f, 0.f, 0.f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	-1.f, 0.f, 0.f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	-1.f, 0.f, 0.f,
	   -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	-1.f, 0.f, 0.f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	1.f, 0.f, 0.f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	1.f, 0.f, 0.f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	1.f, 0.f, 0.f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	1.f, 0.f, 0.f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	1.f, 0.f, 0.f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	1.f, 0.f, 0.f,

	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	0.f, -1.f, 0.f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,	0.f, -1.f, 0.f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.f, -1.f, 0.f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.f, -1.f, 0.f,
	   -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.f, -1.f, 0.f,
	   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	0.f, -1.f, 0.f,

	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.f, 1.f, 0.f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.f, 1.f, 0.f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.f, 1.f, 0.f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.f, 1.f, 0.f,
	   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,	0.f, 1.f, 0.f,
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.f, 1.f, 0.f
	};
	// textures load up
	Texture tex;
	//vertex and buffer object; texture (change also in texture.h)
	unsigned int VAO, VBO;
	std::vector<unsigned int> texture;
};