#pragma once
#include "Chunk.h"
#include <PerlinNoise.hpp>
#include "Block_Heavy.h"

class World {
public:
//constructors
	World(int numberOfChunks, Shader shader);
//functions
	//draws the world
	void drawWorld(Shader shader);
private:
	//needed at startup
	void loadChunks(Shader shader);
	void generateHeightMap();
	float map(float x, float start1, float stop1, float start2, float stop2);
//variables
private:
	//vector of chunks and heavy block - holds the intrinsic state of the blocks
	std::vector<Chunk> chunks;
	Block_Heavy megaBlock;
	//variables for perlin noise
	std::vector<int> heights;
	siv::PerlinNoise noiseMap;
	float add;
	//utuility variables
	int numberOfChunks, chunkNumber = 0, chunkMult;
	int chunkSize = 10, chunkArea = chunkSize * chunkSize, chunkVolume = chunkArea * chunkSize;
};