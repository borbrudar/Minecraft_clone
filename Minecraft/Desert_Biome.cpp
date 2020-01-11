#include "Desert_Biome.h"

void Desert_Biome::drawBiome(Shader shader, Block_Heavy & data, glm::mat4 model)
{
	for (int i = 0; i < cacti.size(); i++) {
		for (int j = 0; j < cacti[i].part1.size(); j++) {
			model[3][0] = cacti[i].part1[j].x;
			model[3][1] = cacti[i].part1[j].y;
			model[3][2] = cacti[i].part1[j].z;
			shader.setMat4("model", model);

			cacti[i].part1[j].draw(shader, data);

		}
	}
}

void Desert_Biome::setBiomeData(int chunkSize, int modelX, int modelZ,int modelY, std::vector<int>& heights, std::vector<Block>& blocks)
{
	//set the water blocks
	int lowestBlock = 10000;
	for (int x = 0; x < chunkSize; x++) {
		for (int z = 0; z < chunkSize; z++) {
			if (heights[x + (chunkSize * z)] < lowestBlock) lowestBlock = heights[x + (chunkSize * z)];
		}
	}
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int> water(0, 2);

	// I don't like sand. It's course, rough and irritating and it gets everywhere...
	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				blocks[x + chunkSize * (y + (z * chunkSize))].type = block_type::type::sand;

				//water kinda
				if ((y == lowestBlock) && (water(engine) == 0)) 
					blocks[x + chunkSize * (y + (z * chunkSize))].type = block_type::type::water;
			}
		}
	}

	//load the cacti positions
	std::uniform_int_distribution<int> pos(0, chunkSize - 1);
	cacti.resize(3);

	for (int i = 0; i < cacti.size(); i++) {
		cacti[i].setStructureData(structureType::cactus);
		int x = pos(engine), z = pos(engine);
		for (int j = 0; j < cacti[i].part1.size(); j++) {
			cacti[i].part1[j].x = x + (modelX * chunkSize);
			cacti[i].part1[j].z = z + (modelZ * chunkSize);
			cacti[i].part1[j].y = heights[x + (z * chunkSize)] + modelY + j;
		}
	}

}