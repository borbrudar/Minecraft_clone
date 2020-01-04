#include "Chunk.h"

void Chunk::loadChunk(Shader shader, int & chunkNumber, int chunkMult, int chunkSize)
{ 
	//helper variables
	int chunkVolume = chunkSize * chunkSize * chunkSize;
	int chunkArea = chunkSize * chunkSize;
	//resize the block vector
	blocks.resize(chunkVolume);

	//initialize the model matrix and matrix multipliers
	model = glm::mat4(1.f);
	modelX = (int)(chunkNumber % chunkMult);
	modelZ = floor(chunkNumber / chunkMult);
	modelY = -chunkSize;

	//set some variables
	this->chunkNumber = chunkNumber;
	chunkNumber++;

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

}

void Chunk::drawChunk(Shader shader, int chunkSize, Block_Heavy &data)
{

	//a guide for transformin them blocks
	//model[3][0 - x axis, 1 - y ax., 2 - z ax.; + = right,up,back; - = left,down,front] = 1 (1 block);

	//flatten 3d array into 1d with:
	//flat[x + width * (y + depth * z)]

	//draw all them visible blocks
	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				if (blocks[x + chunkSize * (y + (z * chunkSize))].isVisible) {
					//apply transformation 
					model[3][0] = x + (modelX * chunkSize);
					model[3][1] = y + modelY;
					model[3][2] = z + (modelZ * chunkSize);
					//pass transformation to the shader and draw
					shader.setMat4("model", model);
					blocks[x + chunkSize * (y + (z * chunkSize))].draw(shader, data);
				}
			}
		}
	}
	for (int i = 0; i < trees.size(); i++) {
		for (int j = 0; j < trees[i].trunk.size(); j++) {
			model[3][0] = trees[i].trunk[j].x;
			model[3][1] = trees[i].trunk[j].y;
			model[3][2] = trees[i].trunk[j].z;
			shader.setMat4("model", model);

			trees[i].trunk[j].draw(shader, data);
		}
	}
}

//hides unnecessary blocks
void Chunk::hideBlocks(int chunkSize)
{

	//checks surrounding blocks, if there's one in every directions, this block becomes invisible
	for (unsigned int i = 0; i < blocks.size(); i++) {
		//block 1 and variables for each direction
		Block b1 = blocks[i];
		bool px = false, py = false, pz = false, nx = false, ny = false, nz = false;

		for (unsigned int j = 0; j < blocks.size(); j++) {
			//check
			Block b2 = blocks[j];
			if (b2.isVisible) {
				if ((b1.x + 1 == b2.x) && (b1.y == b2.y) && (b1.z == b2.z)) px = true;
				if ((b1.x - 1 == b2.x) && (b1.y == b2.y) && (b1.z == b2.z)) nx = true;
				if ((b1.y + 1 == b2.y) && (b1.x == b2.x) && (b1.z == b2.z)) py = true;
				if ((b1.y - 1 == b2.y) && (b1.x == b2.x) && (b1.z == b2.z)) ny = true;
				if ((b1.z + 1 == b2.z) && (b1.y == b2.y) && (b1.x == b2.x)) pz = true;
				if ((b1.z - 1 == b2.z) && (b1.y == b2.y) && (b1.x == b2.x)) nz = true;
			}
		}
		//set visibility
		if (px && py && pz && nx && ny && nz) blocks[i].isVisible = false;
	}
}

void Chunk::setVisible(int chunkSize)
{
	//set visibility according to height
	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				if (heights[x + (z * chunkSize)] == y) {
					//position shit
					blocks[x + chunkSize * (y + (z * chunkSize))].x = x + (modelX * chunkSize);
					blocks[x + chunkSize * (y + (z * chunkSize))].y = y + modelY;
					blocks[x + chunkSize * (y + (z * chunkSize))].z = z + (modelZ * chunkSize);
				}
				else blocks[x + chunkSize * (y + (chunkSize * z))].isVisible = false;
			}
		}
	}
	

	//load the tree positions
	std::random_device rd;
	std::default_random_engine engine(rd());
	std::uniform_int_distribution<int> pos(0, chunkSize - 1);
	trees.resize(5);

	for (int i = 0; i < trees.size(); i++) {
		int x = pos(engine), z = pos(engine);
		for (int j = 0; j < trees[i].trunk.size(); j++) {
			trees[i].trunk[j].x = x + (modelX * chunkSize);
			trees[i].trunk[j].z = z + (modelZ * chunkSize);
			trees[i].trunk[j].y = j - (chunkSize - heights[x + (z * chunkSize)]);
		}
	}
	//hide blocks (it does nothing for now)
	//hideBlocks(chunkSize);
}
