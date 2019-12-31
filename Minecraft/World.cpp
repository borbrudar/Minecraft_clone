#include "World.h"

void World::drawWorld(Shader shader)
{
	//draw the fucking chunks
	for (int i = 0; i < chunks.size(); i++) chunks[i].drawChunk(shader, chunkSize);
}

void World::loadChunks(Shader shader)
{
	//load the fucking chunks
	for (int i = 0; i < chunks.size(); i++) chunks[i].loadChunk(shader, chunkNumber, chunkMult, chunkSize, tex);
}

void World::generateHeightMap()
{
	//generate the map
	int worldSize = chunkArea * numberOfChunks;
	heights.resize(worldSize);

	for (int x = 0; x < (chunkSize * chunkMult); x++) {
		for (int y = 0; y < (chunkSize * chunkMult); y++) {
			float temp = floor(map(abs(noiseMap.noise(x + add, y + add, 0.0)), 0, 0.8, (chunkSize / 4) * 3 - 1, chunkSize ));
			heights[x + (y * chunkSize * chunkMult)] = temp;
			add += 0.0723f;
		}
	}
	//pass the map to every chunk
	for (int i = 0; i < chunks.size(); i++) {
		chunks[i].heights.resize(chunkArea);
			for (int x = 0; x < chunkSize; x++) {
				for (int y = 0; y < chunkSize; y++) {
					float temp_x = chunkSize * chunks[i].modelX + x;
					float temp_y = chunkSize * chunks[i].modelZ + y;
					chunks[i].heights[x + (y * chunkSize)] = heights[temp_x + temp_y];
				}
			}
	}


}

float World::map(float x, float start1, float stop1, float start2, float stop2)
{
	return start2 + (stop2 - start2) * ((x - start1) / (stop1 - start1));
}
