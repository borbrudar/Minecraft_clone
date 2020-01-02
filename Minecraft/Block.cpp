#include "Block.h"

void Block::draw(Shader shader, Block_Heavy &data)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, data.texture0);
	shader.use();
	// render box
	glBindVertexArray(data.VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
