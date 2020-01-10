#pragma once
#include "Biome.h"
#include "Shader.h"
#include"Block_Heavy.h"
#include <random>

struct BirchTree {
public:
	//constructor
	BirchTree() {
		for (int i = 0; i < 5; i++) {
			trunk.push_back(Block());
			trunk[i].type = block_type::type::birchtree;

			treeTop.push_back(Block());
			treeTop[i].type = block_type::type::leaf;
		}
	}
	//functions
	void setTreeTop(int x, int y, int z) {
		treeTop[0].x = x; treeTop[0].y = y + 1; treeTop[0].z = z;
		treeTop[1].x = x + 1; treeTop[1].y = y; treeTop[1].z = z;
		treeTop[2].x = x - 1; treeTop[2].y = y; treeTop[2].z = z;
		treeTop[3].x = x; treeTop[3].y = y; treeTop[3].z = z + 1;
		treeTop[4].x = x; treeTop[4].y = y; treeTop[4].z = z - 1;
	};
	//variables
	std::vector<Block> trunk;
	std::vector<Block> treeTop;
};

class Birch_Biome : public Biome {
public:
	void drawBiome(Shader shader, Block_Heavy &data, glm::mat4 model);
	void setBiomeData(int chunkSize, int modelX, int modelZ, int modelY, std::vector<int> &heights, std::vector<Block> &blocks);
	std::vector<BirchTree> trees;
};