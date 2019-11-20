#pragma once

#include "Manager.h"


//TODO Texture atlas

class TextureManager : Manager {
private:
	std::map<std::string, GLuint> textures;

	GLuint build_texture(std::string path, bool alpha);

public:
	TextureManager() {

	}
	~TextureManager() {

	}


	GLuint test_load_texture(std::string path, bool alpha);
	void create_texture(std::string reference_name, std::string path, bool alpha);
	GLuint get_texture(std::string reference_name);


};
