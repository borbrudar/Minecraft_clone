#pragma once
#include <stb_image.h>


class Texture {
public:
//constructor that loads up the default texture
	Texture() {
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		data = stbi_load("textures/grass.jpg", &width, &height, &nrChannels, 0);
	}
//variables
	unsigned char *data;
	int width, height, nrChannels;
};
