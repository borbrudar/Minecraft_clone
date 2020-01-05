#pragma once
#include "Biome.h"
#include <random>

struct Structure {
	Structure() {
		for (int i = 0; i < 6; i++) {
			ice.push_back(Block());
			ice[i].type = block_type::type::ice;
		}
	}
	void setIceStructure(int x, int y, int z) {
		ice[0].x = x; ice[0].y = y + 1; ice[0].z = z;
		ice[1].x = x; ice[1].y = y + 2; ice[1].z = z;
		ice[2].x = x + 1; ice[2].y = y + 1; ice[2].z = z;
		ice[3].x = x - 1; ice[3].y = y + 1; ice[3].z = z;
		ice[4].x = x; ice[4].y = y + 1; ice[4].z = z + 1;
		ice[5].x = x; ice[5].y = y + 1; ice[5].z = z - 1;
	}
	std::vector<Block> ice;
};

class Snow_Biome : public Biome {
public:
	void drawBiome(Shader shader, Block_Heavy &data, glm::mat4 model);
	void setBiomeData(int chunkSize, int modelX, int modelZ,int modelY, std::vector<int> &heights, std::vector<Block> &blocks);
	std::vector<Structure> icy;
	std::vector<glm::vec3> positions;
};