#pragma once
#include "Biome.h"
#include <random>

class Taiga_Biome : public Biome {
public:
	void drawBiome(Shader shader, Block_Heavy &data, glm::mat4 model);
	void setBiomeData(int chunkSize, int modelX, int modelZ, int modelY, std::vector<int> &heights, std::vector<Block> &blocks);

	std::vector<Structure> trees;
};