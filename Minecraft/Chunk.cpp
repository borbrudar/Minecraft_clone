#include "Chunk.h"

void Chunk::loadChunk(Shader shader, int & chunkNumber, int chunkMult)
{
	//initialize blocks
	blocks.resize(chunkVolume);
	for (int i = 0; i < chunkVolume; i++) {
		blocks[i].loadBlock(shader, tex);
	}
	model = glm::mat4(1.f);
	//initialize the model matrix multipliers (different for each chunk)
	modelX = (chunkNumber % chunkMult);
	modelZ = floor(chunkNumber / chunkMult);
	this->chunkNumber = chunkNumber;
	chunkNumber++;

	//set chunkMult
	this->chunkMult = chunkMult;
}

void Chunk::drawChunk(Shader shader)
{
	//a guide for drawing them blocks
	//model[3][0 - x axis, 1 - y ax., 2 - z ax.; + = right,up,back; - = left,down,front] = 1 (1 block);

	//draw all them blocks
	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
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
