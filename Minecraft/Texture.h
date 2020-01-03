#pragma once
#include <stb_image.h>
#include <string>
#include <vector>

class Texture {
public:
//function that loads up the texture
	void loadTexture(std::vector<std::string> string) {
		for (int i = 0; i < 2; i++) {
			stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
			data[i] = stbi_load(string[i].c_str(), &width[i], &height[i], &nrChannels[i], 0);
		}
	}
//variables
	unsigned char *data[2];
	int width[2],height[2], nrChannels[2];
};
