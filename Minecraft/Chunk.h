#pragma once
#include <vector>
#include "Block.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>

class Chunk {
public:
//constructors
	Chunk() = default;
//functions
	void loadChunk(Shader shader, int &chunkNumber, int chunkMult, int chunkSize, Block_Heavy& data);
	void drawChunk(Shader shader, int chunkSize);
	void hideBlocks(int chunkSize);
//variables
	std::vector<Block> blocks;
	int chunkNumber;
	glm::mat4 model;
	int modelX = 0, modelZ = 0;
	std::vector<int> heights;

//chunk mesh
	/*std::vector<glm::vec3> vertices;
	void buildMesh();
	void loadMesh(Shader shader);
	Texture texture;

	std::vector<glm::vec3> PX_POS{
		glm::vec3(0.5f,  0.5f,  0.5f),
		glm::vec3(0.5f,  0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f, -0.5f),
		glm::vec3(0.5f, -0.5f,  0.5f),
		glm::vec3(0.5f,  0.5f,  0.5f)
	};
	std::vector<glm::vec3> NX_POS = {

			glm::vec3(-0.5f,0.5f,-0.5f),
			glm::vec3(-0.5f,-0.5f,-0.5f),
			glm::vec3(-0.5f,-0.5f,0.5f),
			glm::vec3(-0.5f,-0.5f,0.5f),
			glm::vec3(-0.5f,0.5f,0.5f),
			glm::vec3(-0.5f,0.5f,-0.5f)

	};
	std::vector<glm::vec3> PY_POS = {

			glm::vec3(-0.5f,0.5f,0.5f),
			glm::vec3(-0.5f,0.5f,-0.5f),
			glm::vec3(0.5f,0.5f,-0.5f),
			glm::vec3(0.5f,0.5f,-0.5f),
			glm::vec3(0.5f,0.5f,0.5f),
			glm::vec3(-0.5f,0.5f,0.5f)

	};
	std::vector<glm::vec3> NY_POS = {

			glm::vec3(-0.5f,-0.5f,0.5f),
			glm::vec3(-0.5f,-0.5f,-0.5f),
			glm::vec3(0.5f,-0.5f,-0.5f),
			glm::vec3(0.5f,-0.5f,-0.5f),
			glm::vec3(0.5f,-0.5f,0.5f),
			glm::vec3(-0.5f,-0.5f,0.5f)

	};
	std::vector<glm::vec3> PZ_POS = {

			glm::vec3(-0.5f,0.5f,0.5f),
			glm::vec3(-0.5f,-0.5f,0.5f),
			glm::vec3(0.5f,-0.5f,0.5f),
			glm::vec3(0.5f,-0.5f,0.5f),
			glm::vec3(0.5f,0.5f,0.5f),
			glm::vec3(-0.5f,0.5f,0.5f)

	};
	std::vector<glm::vec3> NZ_POS = {


glm::vec3(-0.5f,0.5f,-0.5f),
			glm::vec3(-0.5f,-0.5f,-0.5f),
			glm::vec3(0.5f,-0.5f,-0.5f),
			glm::vec3(0.5f,-0.5f,-0.5f),
			glm::vec3(0.5f,0.5f,-0.5f),
			glm::vec3(-0.5f,0.5f,-0.5f)

	};

	unsigned int VAO, VBO, texture0;*/
};