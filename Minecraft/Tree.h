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
		}
	}
//variables
	std::vector<Block> trunk;
};