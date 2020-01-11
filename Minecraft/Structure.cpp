#include "Structure.h"

void Structure::setStructureData(structureType type)
{
	this->type = type;
	switch (type)
	{
	case structureType::oak_tree:
		for (int i = 0; i < 5; i++) {
			part1.push_back(Block());
			part1[i].type = block_type::type::tree;

			part2.push_back(Block());
			part2[i].type = block_type::type::leaf;
		}
		break;
	case structureType::birch_tree:
		for (int i = 0; i < 5; i++) {
			part1.push_back(Block());
			part1[i].type = block_type::type::birchtree;

			part2.push_back(Block());
			part2[i].type = block_type::type::leaf;
		}
		break;
	case structureType::taiga_tree:
		for (int i = 0; i < 10; i++) {
			part1.push_back(Block());
			part1[i].type = block_type::type::taigatree;

			if (i != 9) {
				part2.push_back(Block());
				part2[i].type = block_type::type::taigaleaf;
			}
		}
		break;
	case structureType::ice_struct:
		for (int i = 0; i < 6; i++) {
			part1.push_back(Block());
			part1[i].type = block_type::type::ice;
		}
		break;
	case structureType::cactus:
		for (int i = 0; i < 4; i++) {
			part1.push_back(Block());
			part1[i].type = block_type::type::cactus;
		}
		break;
	default:
		break;
	}

}

void Structure::setStructure(int x, int y, int z)
{
	switch (type)
	{
	case structureType::oak_tree:
		part2[0].x = x; part2[0].y = y + 1; part2[0].z = z;
		part2[1].x = x + 1; part2[1].y = y; part2[1].z = z;
		part2[2].x = x - 1; part2[2].y = y; part2[2].z = z;
		part2[3].x = x; part2[3].y = y; part2[3].z = z + 1;
		part2[4].x = x; part2[4].y = y; part2[4].z = z - 1;
		break;
	case structureType::birch_tree:
		part2[0].x = x; part2[0].y = y + 1; part2[0].z = z;
		part2[1].x = x + 1; part2[1].y = y; part2[1].z = z;
		part2[2].x = x - 1; part2[2].y = y; part2[2].z = z;
		part2[3].x = x; part2[3].y = y; part2[3].z = z + 1;
		part2[4].x = x; part2[4].y = y; part2[4].z = z - 1;
		break;
	case structureType::taiga_tree:
		part2[0].x = x; part2[0].y = y + 1; part2[0].z = z;
		part2[1].x = x + 1; part2[1].y = y; part2[1].z = z;
		part2[2].x = x - 1; part2[2].y = y; part2[2].z = z;
		part2[3].x = x; part2[3].y = y; part2[3].z = z + 1;
		part2[4].x = x; part2[4].y = y; part2[4].z = z - 1;

		part2[5].x = x + 1; part2[5].y = y - 4; part2[5].z = z;
		part2[6].x = x - 1; part2[6].y = y - 4; part2[6].z = z;
		part2[7].x = x; part2[7].y = y - 4; part2[7].z = z + 1;
		part2[8].x = x; part2[8].y = y - 4; part2[8].z = z - 1;
		break;
	case structureType::ice_struct:
		part1[0].x = x; part1[0].y = y + 1; part1[0].z = z;
		part1[1].x = x + 1; part1[1].y = y; part1[1].z = z;
		part1[2].x = x - 1; part1[2].y = y; part1[2].z = z;
		part1[3].x = x; part1[3].y = y; part1[3].z = z + 1;
		part1[4].x = x; part1[4].y = y; part1[4].z = z - 1;
		break;
	default:
		break;
	}

}
