#pragma once

#include "Manager.h"

class TextureManager : Manager {
private:
	std::map<std::string, GLuint> textures;
	GLuint build_texture(std::string texture_loc);

public:
	TextureManager() {

	}
	~TextureManager() {

	}




};
