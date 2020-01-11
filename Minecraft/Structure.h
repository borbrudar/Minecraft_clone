#pragma once
#include <vector>
#include "Block.h"

enum class structureType {
	oak_tree,
	birch_tree,
	taiga_tree,
	ice_struct,
	cactus
};


class Structure {
public:
	//set function
	void setStructureData(structureType type);
	//part2 function
	void setStructure(int x, int y, int z);
	//variables
	std::vector<Block> part1;
	std::vector<Block> part2;
	structureType type;
};