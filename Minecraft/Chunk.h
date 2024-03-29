#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Block.h"
#include "Biome.h"
#include "Forest_Biome.h"
#include "Desert_Biome.h"
#include "Snow_Biome.h"
#include "Taiga_Biome.h"
#include "Birch_Biome.h"

#include <math.h>
#include <vector>
#include <random>
#include <memory>

class Chunk {
public:
//functions
	void loadChunk(Shader shader, int &chunkNumber, int chunkMult, int chunkSize);
	void drawChunk(Shader shader, Block_Heavy &data);
	void hideBlocks();
	void setVisible();
	void loadBiome();
//variables
	std::vector<Block> blocks;
	int chunkNumber, chunkSize;
	glm::mat4 model;
	int modelX = 0, modelZ = 0, modelY = 0;
	std::vector<int> heights;
	std::unique_ptr<Biome> biome = std::make_unique<Forest_Biome>();
};