#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Utils/stb_image.h"

GLuint TextureManager::test_load_texture(std::string path, bool alpha) {
	int width, height, bpp;
	stbi_set_flip_vertically_on_load(true);
    uint8_t * image = stbi_load(path.c_str(), &width, &height, &bpp, (alpha) ? 4 : 3);

	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, (alpha) ? GL_RGBA : GL_RGB, width, height, 0, (alpha) ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, image);
	stbi_image_free(image);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}
