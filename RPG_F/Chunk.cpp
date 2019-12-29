#include "Chunk.h"

void Chunk::drawChunk(Shader shader, glm::mat4 model)
{
	//a guide for drawing them blocks
	//model[3][0 - x axis, 1 - y ax., 2 - z ax.; + = right,up,back; - = left,down,front] = 1 (1 block);

	//draw all them blocks
	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				//apply transformation 
				model[3][0] = x;
				model[3][1] = y;
				model[3][2] = z;
				//pass transformation to the shader and draw
				shader.setMat4("model", model);
				blocks[x * y * z].draw(shader);
			}
		}
	}

}
