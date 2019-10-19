#pragma once

#include "Libraries.h"

class Model {
public:
	std::vector<glm::vec3> model_verts, model_normals;
	std::vector<glm::vec2> model_uvs;
	std::vector<unsigned int> model_indices;
	GLuint vboId, eboId;


	void create_data_buffer(std::string path);
	GLuint build_vbo();
	GLuint build_ebo();


	Model(std::string path) {
		create_data_buffer(path);
		vboId = build_vbo();
		eboId = build_ebo();

	}

};
