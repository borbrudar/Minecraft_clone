#pragma once
#include "Biome.h"
#include <random>

struct TaigaTree {
public:
	//constructor
	TaigaTree() {
		for (int i = 0; i < 10; i++) {
			trunk.push_back(Block());
			trunk[i].type = block_type::type::taigatree;

			if (i != 9) {
				treeTop.push_back(Block());
				treeTop[i].type = block_type::type::taigaleaf;
			}
		}
	}
	//functions
	void setTreeTop(int x, int y, int z) {
		treeTop[0].x = x; treeTop[0].y = y + 1; treeTop[0].z = z;
		treeTop[1].x = x + 1; treeTop[1].y = y; treeTop[1].z = z;
		treeTop[2].x = x - 1; treeTop[2].y = y; treeTop[2].z = z;
		treeTop[3].x = x; treeTop[3].y = y; treeTop[3].z = z + 1;
		treeTop[4].x = x; treeTop[4].y = y; treeTop[4].z = z - 1;

		treeTop[5].x = x + 1; treeTop[5].y = y - 4; treeTop[5].z = z;
		treeTop[6].x = x - 1; treeTop[6].y = y - 4; treeTop[6].z = z;
		treeTop[7].x = x; treeTop[7].y = y - 4; treeTop[7].z = z + 1;
		treeTop[8].x = x; treeTop[8].y = y - 4; treeTop[8].z = z - 1;
	};
	//variables
	std::vector<Block> trunk;
	std::vector<Block> treeTop;
};

class Taiga_Biome : public Biome {
public:
	void drawBiome(Shader shader, Block_Heavy &data, glm::mat4 model);
	void setBiomeData(int chunkSize, int modelX, int modelZ, int modelY, std::vector<int> &heights, std::vector<Block> &blocks);

	std::vector<TaigaTree> trees;
};