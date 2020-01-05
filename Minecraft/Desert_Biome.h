#pragma once
#include "Biome.h"
#include "Block.h"
#include <random>

struct Cactus {
	Cactus() {
		for (int i = 0; i < 4; i++) {
			trunk.push_back(Block());
			trunk[i].type = block_type::type::cactus;
		}
	}
	std::vector<Block> trunk;
};

class Desert_Biome : public Biome {
public:
	void drawBiome(Shader shader, Block_Heavy &data, glm::mat4 model);
	void setBiomeData(int chunkSize, int modelX, int modelZ,int modelY, std::vector<int> &heights, std::vector<Block> &blocks);
	std::vector<Cactus> cacti;
};

