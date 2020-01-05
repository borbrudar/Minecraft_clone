#pragma once
#include "Tree.h"
#include "Biome.h"
#include "Shader.h"
#include"Block_Heavy.h"
#include <random>

class Forest_Biome : public Biome {
public:
	void drawBiome(Shader shader, Block_Heavy &data, glm::mat4 model);
	void setBiomeData(int chunkSize, int modelX, int modelZ, std::vector<int> &heights, std::vector<Block> &blocks);
	std::vector<Tree> trees;
};