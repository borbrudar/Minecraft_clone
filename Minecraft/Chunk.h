#pragma once
#include <vector>
#include "Block.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Chunk {
public:
	Chunk(Shader shader) {
		blocks.resize(chunkVolume);
		for (int i = 0; i < chunkVolume ; i++) {
			blocks[i].loadBlock(shader, tex);
		}
	}
	void drawChunk(Shader shader, glm::mat4 model);
//varibles
	std::vector<Block> blocks;
	const int chunkSize = 16, chunkArea = chunkSize * chunkSize, chunkVolume = chunkArea * chunkSize;
	Texture tex;
};