#include <GL\glew.h>
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>


Texture::Texture(const std::string & fileName)
{
	int width, height, numComponents;
	unsigned char* image = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (image == NULL)
		std::cerr << "Error: Can not load image" << std::endl;

	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	stbi_image_free(image);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_Texture);
}

void Texture::bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}
