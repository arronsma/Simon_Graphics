#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Texture {
public:
	Texture(std::string fileName, int TextureUnit) {
		int width, height, nrChannels;
		unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
		stbi_set_flip_vertically_on_load(true);
		unsigned texture_ID;
		glGenTextures(1, &texture_ID);
		glActiveTexture(TextureUnit);
		glBindTexture(GL_TEXTURE_2D, texture_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		int sourceFormat;
		switch (nrChannels)
		{
		case 3:
			sourceFormat = GL_RGB;
			break;
		case 4:
			sourceFormat = GL_RGBA;
			break;
		default:
			assert(false);
			break;
		}
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, sourceFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
};