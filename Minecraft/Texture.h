#pragma once
#include <stb_image.h>
#include <string>
#include <vector>


class Texture {
public:
//function that loads up the texture
	void loadTexture(std::vector<std::string> string, int size) {
		width.resize(size);
		height.resize(size);
		nrChannels.resize(size);
		data.resize(size);

		for (int i = 0; i < size; i++) {
			
			stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
			data[i] = stbi_load(string[i].c_str(), &width[i], &height[i], &nrChannels[i], 0);
		}
	}
//variables
	std::vector<unsigned char*> data;
	std::vector<int> width,height, nrChannels;
};
