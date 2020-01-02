#include "Chunk.h"

void Chunk::loadChunk(Shader shader, int & chunkNumber, int chunkMult, int chunkSize, Block_Heavy& data)
{ 
	
	int chunkVolume = chunkSize * chunkSize * chunkSize;
	int chunkArea = chunkSize * chunkSize;
	//initialize blocks
	blocks.resize(chunkVolume);
	//just a lil optimization
	for (int x = 0; x < chunkSize; x++) {
		for (int y = 0; y < chunkSize; y++) {
			for (int z = 0; z < chunkSize; z++) {
				if (heights[x + (z * chunkSize)] == y) {
					//position shit
					blocks[x + chunkSize * (y + (z * chunkSize))].x = x + (modelX * chunkSize);
					blocks[x + chunkSize * (y + (z * chunkSize))].y = y;
					blocks[x + chunkSize * (y + (z * chunkSize))].z = z + (modelZ * chunkSize);
				}
				else {
					blocks[x + chunkSize * (y + (chunkSize * z))].isVisible = false;
				}
			}

		}
	}

	hideBlocks(chunkSize);
	for (int i = 0; i < chunkVolume; i++) if (blocks[i].isVisible) { blocks[i].loadBlock(shader, data); }
	model = glm::mat4(1.f);

	//initialize the model matrix multipliers (different for each chunk)
	modelX = (chunkNumber % chunkMult);
	modelZ = floor(chunkNumber / chunkMult);
	this->chunkNumber = chunkNumber;
	chunkNumber++;


}

void Chunk::drawChunk(Shader shader, int chunkSize)
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
					model[3][1] = y;
					model[3][2] = z + (modelZ * chunkSize);
					//pass transformation to the shader and draw
					shader.setMat4("model", model);
					blocks[x + chunkSize * (y + (z * chunkSize))].draw(shader);
				}
			}
		}
	}
	
	
}

void Chunk::hideBlocks(int chunkSize)
{
	//hide unnecessary blocks
	for (int i = 0; i < blocks.size(); i++) {
		Block b1 = blocks[i];
		//check in every direction
		bool px = false, py = false, pz = false, nx = false, ny = false, nz = false;
		for (int j = 0; j < blocks.size(); j++) {
			Block b2 = blocks[j];
			if (b2.isVisible) {
				if ((b1.x + 1 == b2.x) && (b1.y == b2.y) && (b1.z == b2.z)) px = true;
				if ((b1.x - 1 == b2.x) && (b1.y == b2.y) && (b1.z == b2.z)) nx = true;
				if ((b1.y + 1 == b2.y) && (b1.x == b2.x) && (b1.z == b2.z)) py = true;
				if ((b1.y - 1 == b2.y) && (b1.x == b2.x) && (b1.z == b2.z)) ny = true;
				if ((b1.z + 1 == b2.z) && (b1.y == b2.y) && (b1.x == b2.x)) pz = true;
				if ((b1.z - 1 == b2.z) && (b1.y == b2.y) && (b1.x == b2.x)) nz = true;
			}
			//check if outside the array, in which case it shouldnt be activated
			/*if ((b1.x + 1) == chunkSize) px = 0;
			if (b1.x == 0) nx = 0;
			if ((b1.y + 1) == chunkSize) py = 0;
			if (b1.y == 0) ny = 0;
			if ((b1.z + 1) == chunkSize) pz = 0;
			if (b1.z == 0) nz = 0;*/

		}

		if (px && py && pz && nx && ny && nz) blocks[i].isVisible = false;
		
	}
}


//mesh stuff you fucked up
/*void Chunk::buildMesh()
{
	//loop thru the blocks n build da mesh
	for (int i = 0; i < blocks.size(); i++) {
		Block b1 = blocks[i];
		bool px = 0, py = 0, pz = 0, nx = 0, ny = 0, nz = 0;
		for (int j = 0; j < blocks.size(); j++) {
			Block b2 = blocks[j];
			//px
			if (((b1.x + 1) == b2.x) && (b1.y == b2.y) && (b1.z == b2.z)) px = 1;
			//py
			if (((b1.y + 1) == b2.y) && (b1.x == b2.x) && (b1.z == b2.z)) py = 1;
			//pz
			if (((b1.z + 1) == b2.z) && (b1.y == b2.y) && (b1.x == b2.x)) pz = 1;
			//nx
			if (((b1.x - 1) == b2.x) && (b1.y == b2.y) && (b1.z == b2.z)) nx = 1;
			//ny
			if (((b1.y - 1) == b2.y) && (b1.x == b2.x) && (b1.z == b2.z)) ny = 1;
			//nz
			if (((b1.z - 1) == b2.z) && (b1.y == b2.y) && (b1.x == b2.x)) nz = 1;
		}
		if (!px) for (int k = 0; k < 6; k++) vertices.push_back(glm::vec3(PX_POS[k].x + b1.x, PX_POS[k].y + b1.y, PX_POS[k].z + b1.z));
		if (!py) for (int k = 0; k < 6; k++) vertices.push_back(glm::vec3(PY_POS[k].x + b1.x, PY_POS[k].y + b1.y, PY_POS[k].z + b1.z));
		if (!pz) for (int k = 0; k < 6; k++) vertices.push_back(glm::vec3(PZ_POS[k].x + b1.x, PZ_POS[k].y + b1.y, PZ_POS[k].z + b1.z));
		if (!nx) for (int k = 0; k < 6; k++) vertices.push_back(glm::vec3(NX_POS[k].x + b1.x, NX_POS[k].y + b1.y, NX_POS[k].z + b1.z));
		if (!ny) for (int k = 0; k < 6; k++) vertices.push_back(glm::vec3(NY_POS[k].x + b1.x, NY_POS[k].y + b1.y, NY_POS[k].z + b1.z));
		if (!nz) for (int k = 0; k < 6; k++) vertices.push_back(glm::vec3(NZ_POS[k].x + b1.x, NZ_POS[k].y + b1.y, NZ_POS[k].z + b1.z));

	}

	//for (int i = 0; i < vertices.size(); i++) std::cout << vertices[i].z << " ";
    
}

void Chunk::loadMesh(Shader shader)
{
	//bind array objects and shit
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices.front(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//load the motherfucking texture
	// ---------
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	if (texture.data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.width, texture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	
	shader.use();
	shader.setInt("texture0", 0);
}*/
