#include "Chunk.h"

void Chunk::loadChunk(Shader shader, int & chunkNumber, int chunkMult, int chunkSize, Texture tex)
{ 
	
	int chunkVolume = chunkSize * chunkSize * chunkSize;
	int chunkArea = chunkSize * chunkSize;
	//initialize blocks
	blocks.resize(chunkVolume);
	for (int i = 0; i < chunkVolume; i++) blocks[i].loadBlock(shader, tex);
	model = glm::mat4(1.f);

	//discard some for faster drawing (update when adding break/place mechanic)
	/*for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				if (y > 0 && y < 2) blocks[x * y * z].isVisible = false;
				if (x == 0 || x == (chunkSize - 1)) blocks[x * y * z].isVisible = true;
				if (z == 0 || z == (chunkSize - 1)) blocks[x * y * z].isVisible = true;
			}
		}
	}*/

	//initialize the model matrix multipliers (different for each chunk)
	modelX = (chunkNumber % chunkMult);
	modelZ = floor(chunkNumber / chunkMult);
	this->chunkNumber = chunkNumber;
	chunkNumber++;

	
}

void Chunk::drawChunk(Shader shader, int chunkSize)
{
	//a guide for drawing them blocks
	//model[3][0 - x axis, 1 - y ax., 2 - z ax.; + = right,up,back; - = left,down,front] = 1 (1 block);

	//draw all them blocks
	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				if (heights[x * z] > y && blocks[x * y * z].isVisible) {
					//apply transformation 
					model[3][0] = x + (modelX * chunkSize);
					model[3][1] = y;
					model[3][2] = z + (modelZ * chunkSize);
					//pass transformation to the shader and draw
					shader.setMat4("model", model);
					blocks[x * y * z].draw(shader);
				}
				
			}
		}
	}

}
