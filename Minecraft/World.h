#pragma once
#include "Chunk.h"
#include "Camera.h"
#include "State.h"
#include <PerlinNoise.hpp>
#include "Block_Heavy.h"
class World : public State{
public:
//constructors
	World(int numberOfChunks, Shader shader);
//functions
	//draws the world
	void draw(Shader shader);
	void processInput(GLFWwindow *window, Camera &camera, float deltaTime);
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
	//utuility variables
	int numberOfChunks, chunkNumber = 0, chunkMult;
	int chunkSize = 9, chunkArea = chunkSize * chunkSize, chunkVolume = chunkArea * chunkSize;
};