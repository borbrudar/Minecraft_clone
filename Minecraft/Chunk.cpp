#include "Chunk.h"

void Chunk::loadChunk(Shader shader, int & chunkNumber, int chunkMult, int chunkSize)
{ 
	
	int chunkVolume = chunkSize * chunkSize * chunkSize;
	int chunkArea = chunkSize * chunkSize;
	//initialize blocks
	blocks.resize(chunkVolume);
	//set if visible
	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				if (heights[x + (z * chunkSize)] == y) {
					//position shit
					blocks[x + chunkSize * (y + (z * chunkSize))].x = x + (modelX * chunkSize);
					blocks[x + chunkSize * (y + (z * chunkSize))].y = y + modelY;
					blocks[x + chunkSize * (y + (z * chunkSize))].z = z + (modelZ * chunkSize);
				}
				else {
					blocks[x + chunkSize * (y + (chunkSize * z))].isVisible = false;
				}
			}

		}
	}

	hideBlocks(chunkSize);
	model = glm::mat4(1.f);

	//initialize the model matrix multipliers (different for each chunk)
	modelX = (int)(chunkNumber % chunkMult);
	modelZ = floor(chunkNumber / chunkMult);
	modelY = -chunkSize;
	this->chunkNumber = chunkNumber;
	chunkNumber++;
}

void Chunk::drawChunk(Shader shader, int chunkSize, Block_Heavy &data)
{

	//a guide for transformin them blocks
	//model[3][0 - x axis, 1 - y ax., 2 - z ax.; + = right,up,back; - = left,down,front] = 1 (1 block);

	//flatten 3d array into 1d with:
	//flat[x + width * (y + depth * z)]

	//draw all them blocks
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
	
	
}

void Chunk::hideBlocks(int chunkSize)
{
	//hide unnecessary blocks
	for (unsigned int i = 0; i < blocks.size(); i++) {
		Block b1 = blocks[i];
		//check in every direction
		bool px = false, py = false, pz = false, nx = false, ny = false, nz = false;
		for (unsigned int j = 0; j < blocks.size(); j++) {
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

		if (px && py && pz && nx && ny && nz) blocks[i].isVisible = false;
		
	}
}
