#pragma once

#include "Libraries.h"

class Model {
public:
	std::vector<glm::vec4> model_verts, model_uvs, model_normals;
	GLuint id;


	GLuint create_data_buffer(std::string path);


	Model(std::string path) {
		id = create_data_buffer(path);
	}

};
