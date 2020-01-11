#include "Snow_Biome.h"

void Snow_Biome::drawBiome(Shader shader, Block_Heavy & data, glm::mat4 model)
{
	//draw the part1 structures 
	for (int i = 0; i < icy.size(); i++) {
		icy[i].setStructure(positions[i].x, positions[i].y + 1, positions[i].z);
		
		for (int j = 0; j < icy[i].part1.size(); j++) {
			int x = icy[i].part1[j].x, y = icy[i].part1[j].y, z = icy[i].part1[j].z;
			model[3][0] = x;
			model[3][1] = y;
			model[3][2] = z;
			shader.setMat4("model", model);

			icy[i].part1[j].draw(shader, data);
		}
	}
}

void Snow_Biome::setBiomeData(int chunkSize, int modelX, int modelZ,int modelY, std::vector<int>& heights, std::vector<Block>& blocks)
{
	//snowy surface yay
	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				blocks[x + chunkSize * (y + (z * chunkSize))].type = block_type::type::snow;
			}
		}
	}

	//load the part1 structures positions
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int> pos(1, chunkSize - 1);
	icy.resize(3);
	positions.resize(3);

	for (int i = 0; i < icy.size(); i++) {
		icy[i].setStructureData(structureType::ice_struct);
		int x = pos(engine), z = pos(engine);
		positions[i].x = x + (modelX * chunkSize);
		positions[i].z = z + (modelZ * chunkSize);
		positions[i].y = heights[x + (z * chunkSize)] + modelY;
	}
}
