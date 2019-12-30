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
	Chunk() = default;
	Chunk(Shader shader, int &chunkNumber, int chunkMult){
		loadChunk(shader, chunkNumber, chunkMult);
	}
	void loadChunk(Shader shader, int &chunkNumber, int chunkMult);
	void drawChunk(Shader shader);
//varibles
	std::vector<Block> blocks;
	const int chunkSize = 4, chunkArea = chunkSize * chunkSize, chunkVolume = chunkArea * chunkSize;
	int chunkMult, chunkNumber;
	Texture tex;
	glm::mat4 model;
	int modelX = 0, modelZ = 0;
};