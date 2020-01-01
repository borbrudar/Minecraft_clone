#pragma once
#include "Chunk.h"
#include <PerlinNoise.hpp>
#include "Block_Heavy.h"

class World {
public:
	//constructors
	World(int numberOfChunks, Shader shader) : numberOfChunks(numberOfChunks) {
		chunks.resize(numberOfChunks);
		chunkMult = sqrt(chunkSize);

		//load da chunks
		for (int i = 0; i < chunks.size(); i++) chunks[i].loadChunk(shader, chunkNumber, chunkMult, chunkSize, megaBlock);

		//generate the height map
		generateHeightMap();

		std::default_random_engine engine;
		std::uniform_real_distribution<float> dist(0.01f, 0.1f);
		add = dist(engine);

	};
	//functions
	void drawWorld(Shader shader);
private:
	void loadChunks(Shader shader);
	void generateHeightMap();
	float map(float x, float start1, float stop1, float start2, float stop2);
//variables
public:
	std::vector<Chunk> chunks;
	int numberOfChunks, chunkNumber = 0, chunkMult;
	int chunkSize = 8, chunkArea = chunkSize * chunkSize, chunkVolume = chunkArea * chunkSize;
	Block_Heavy megaBlock;
private:
	std::vector<int> heights;
	siv::PerlinNoise noiseMap;
	float add;
	
};