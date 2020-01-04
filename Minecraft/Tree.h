#pragma once
#include "Block.h"
#include <vector>

class Tree {
public:
//constructor
	Tree() {
		for (int i = 0; i < 5; i++) {
			trunk.push_back(Block());
			trunk[i].type == block_type::type::tree;

			treeTop.push_back(Block());
			treeTop[i].type = block_type::type::leaf;
		}
	}
//functions
	void setTreeTop(int x, int y, int z);
//variables
	std::vector<Block> trunk;
	std::vector<Block> treeTop;
};