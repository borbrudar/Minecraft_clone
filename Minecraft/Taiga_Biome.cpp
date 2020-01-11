#include "Taiga_Biome.h"

void Taiga_Biome::drawBiome(Shader shader, Block_Heavy & data, glm::mat4 model)
{
	//draw the trees
	for (int i = 0; i < trees.size(); i++) {
		for (int j = 0; j < trees[i].part1.size(); j++) {
			int x = trees[i].part1[j].x, y = trees[i].part1[j].y, z = trees[i].part1[j].z;
			model[3][0] = x;
			model[3][1] = y;
			model[3][2] = z;
			shader.setMat4("model", model);

			trees[i].part1[j].draw(shader, data);

			if (j == (trees[i].part1.size() - 1)) {
				trees[i].setStructure(x, y, z);
				for (int k = 0; k < trees[i].part2.size(); k++) {
					model[3][0] = trees[i].part2[k].x;
					model[3][1] = trees[i].part2[k].y;
					model[3][2] = trees[i].part2[k].z;
					shader.setMat4("model", model);

					trees[i].part2[k].draw(shader, data);
				}
			}
		}
	}
}

void Taiga_Biome::setBiomeData(int chunkSize, int modelX, int modelZ, int modelY, std::vector<int>& heights, std::vector<Block>& blocks)
{
	//dirt/stone for the surface
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int> dist(0, 1);

	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				int temp = dist(engine);
				if(temp == 0) blocks[x + chunkSize * (y + (z * chunkSize))].type = block_type::type::dirt;
				if(temp == 1) blocks[x + chunkSize * (y + (z * chunkSize))].type = block_type::type::stone;
			}
		}
	}

	//load the tree positions
	std::uniform_int_distribution<int> pos(0, chunkSize - 1);
	trees.resize(3);

	for (int i = 0; i < trees.size(); i++) {
		trees[i].setStructureData(structureType::taiga_tree);
		int x = pos(engine), z = pos(engine);
		for (int j = 0; j < trees[i].part1.size(); j++) {
			trees[i].part1[j].x = x + (modelX * chunkSize);
			trees[i].part1[j].z = z + (modelZ * chunkSize);
			trees[i].part1[j].y = heights[x + (z * chunkSize)] + modelY + j;
		}
	}
}
