#pragma once
#include <vector>
#include "Block.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

class Chunk {
public:
//constructors
	Chunk() = default;
//functions
	void loadChunk(Shader shader, int &chunkNumber, int chunkMult, int chunkSize);
	void drawChunk(Shader shader, int chunkSize, Block_Heavy &data);
	void hideBlocks(int chunkSize);
//variables
	std::vector<Block> blocks;
	int chunkNumber;
	glm::mat4 model;
	int modelX = 0, modelZ = 0, modelY = 0;
	std::vector<int> heights;
};