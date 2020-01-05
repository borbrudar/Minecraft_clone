#include "Forest_Biome.h"

void Forest_Biome::drawBiome(Shader shader, Block_Heavy & data, glm::mat4 model)
{
	//draw the trees
	for (int i = 0; i < trees.size(); i++) {
		for (int j = 0; j < trees[i].trunk.size(); j++) {
			int x = trees[i].trunk[j].x, y = trees[i].trunk[j].y, z = trees[i].trunk[j].z;
			model[3][0] = x;
			model[3][1] = y;
			model[3][2] = z;
			shader.setMat4("model", model);

			trees[i].trunk[j].draw(shader, data);

			if (j == (trees[i].trunk.size() - 1)) {
				trees[i].setTreeTop(x, y, z);
				for (int k = 0; k < trees[i].treeTop.size(); k++) {
					model[3][0] = trees[i].treeTop[k].x;
					model[3][1] = trees[i].treeTop[k].y;
					model[3][2] = trees[i].treeTop[k].z;
					shader.setMat4("model", model);

					trees[i].treeTop[k].draw(shader, data);
				}
			}
		}
	}
}

void Forest_Biome::setBiomeData(int chunkSize, int modelX, int modelZ, int modelY, std::vector<int> &heights, std::vector<Block> &blocks)
{
	//choose random block type for the surface
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int> dist(0, 1);

	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				blocks[x + chunkSize * (y + (z * chunkSize))].type = (block_type::type) (dist(engine));
			}
		}
	}

	//load the tree positions
	std::uniform_int_distribution<int> pos(0, chunkSize - 1);
	trees.resize(3);

	for (int i = 0; i < trees.size(); i++) {
		int x = pos(engine), z = pos(engine);
		for (int j = 0; j < trees[i].trunk.size(); j++) {
			trees[i].trunk[j].x = x + (modelX * chunkSize);
			trees[i].trunk[j].z = z + (modelZ * chunkSize);
			trees[i].trunk[j].y = heights[x + (z * chunkSize)] + modelY + j;
		}
	}
}
