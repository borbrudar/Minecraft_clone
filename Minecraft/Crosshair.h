#pragma once
#include "Texture.h"
#include "Shader.h"
#include <string>

class Crosshair {
public:
	Crosshair() {
		//load the crosshair
		std::vector<std::string> string = { "textures/crosshair.png" };
		tex.loadTexture(string, 1);
	}
	void loadCrosshair(Shader shader);
	void drawCrosshair(Shader shader);
private:
	Texture tex;
	unsigned int VAO, VBO, texture;
	float vertices[30]{
		-0.03f, -0.03f,  .0f,    0.0f, 0.0f,
		 0.03f, -0.03f,  .0f,    1.0f, 0.0f,
	  	 0.03f,  0.03f,  .0f,    1.0f, 1.0f,
		 0.03f,  0.03f,  .0f,    1.0f, 1.0f,
		-0.03f,  0.03f,  .0f,    0.0f, 1.0f,
		-0.03f, -0.03f,  .0f,    0.0f, 0.0f
	};
};