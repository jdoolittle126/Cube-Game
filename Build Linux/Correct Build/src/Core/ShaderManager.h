#pragma once
#include "Libraries.h"

class ShaderManager {
private:
	std::map<std::string, GLuint> shaders;
	GLuint build_shader(std::string fragment_loc, std::string vertex_loc);

public:
	ShaderManager() {

	}

	void create_shader(std::string reference_name, std::string fragment_loc, std::string vertex_loc);
	GLuint use_shader(std::string reference_name);
	std::map<std::string, GLuint> get_shaders();


};
