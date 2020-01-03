#include "World.h"

World::World(int numberOfChunks, Shader shader) : numberOfChunks(numberOfChunks)
{
	//utility
	chunks.resize(numberOfChunks);
	chunkMult = (int)sqrt(numberOfChunks);

	std::default_random_engine engine;
	std::uniform_real_distribution<float> dist(0.1, 1);
	add = dist(engine);

	//load the texture(s)
	megaBlock.loadBlock(shader);

	//load da chunks 
	for (unsigned int i = 0; i < chunks.size(); i++) chunks[i].loadChunk(shader, chunkNumber, chunkMult, chunkSize);

	//generate the height map 
	generateHeightMap();

	//set visibily
	for (unsigned int i = 0; i < chunks.size(); i++) chunks[i].setVisible(chunkSize);
	
}

void World::drawWorld(Shader shader)
{
	//draw the fucking chunks
	for (unsigned int i = 0; i < chunks.size(); i++) chunks[i].drawChunk(shader, chunkSize, megaBlock);

}

void World::loadChunks(Shader shader)
{
	//load the fucking chunks
	for (unsigned int i = 0; i < chunks.size(); i++) chunks[i].loadChunk(shader, chunkNumber, chunkMult, chunkSize);

}

void World::generateHeightMap()
{
	//setup
	int worldSize = chunkArea * numberOfChunks;
	heights.resize(worldSize);
	
	//generate the map
	for (int x = 0; x < (chunkSize * chunkMult); x++) {
		for (int y = 0; y < (chunkSize * chunkMult); y++) {
			int temp = floor(map(abs(noiseMap.noise(x + add, y + add, 0.0)), 0, 1, (chunkSize / 4) * 3 - 1, chunkSize ));
			heights[x + (y * chunkSize * chunkMult)] = temp;
		}
	}
	//pass the map to every chunk
	for (int i = 0; i < chunks.size(); i++) {
		chunks[i].heights.resize(chunkArea);
			for (int x = 0; x < chunkSize; x++) {
				for (int z = 0; z < chunkSize; z++) {
					float temp_x = chunkSize * chunks[i].modelX + x;
					float temp_z = chunkSize * chunks[i].modelZ + z;
					chunks[i].heights[x + (z * chunkSize)] = heights[temp_x + temp_z];
				}
			}
	}

}

float World::map(float x, float start1, float stop1, float start2, float stop2)
{
	return start2 + (stop2 - start2) * ((x - start1) / (stop1 - start1));
}
