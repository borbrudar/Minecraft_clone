#pragma once
#include "Shader.h"
#include"Block_Heavy.h"

class Biome {
public:
	virtual void drawBiome(Shader shader, Block_Heavy &data, glm::mat4 model) = 0;
	virtual void setBiomeData(int chunkSize, int modelX, int modelZ, std::vector<int> &heights, std::vector<Block> &blocks) = 0;
};


