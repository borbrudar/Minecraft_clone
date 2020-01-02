#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Block.h"

#include <math.h>
#include <vector>

class Chunk {
public:
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