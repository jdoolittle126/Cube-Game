#pragma once

#include "../Core/Dependancies/Libraries.h"
#include "../Utils/OBJ_Loader.h"

class Model {
public:
	std::vector<glm::vec3> model_verts, model_normals;
	std::vector<glm::vec2> model_uvs;
	std::vector<unsigned int> model_indices;
	GLuint vboId, eboId, uvboId, nboId, textureId;


	void create_obj_buffer(std::string path);
	GLuint build_vbo();
	GLuint build_ebo();
	GLuint build_uvbo();
	GLuint build_nbo();
	cube_bound get_bounds();



	Model(std::string obj_path, std::string bmp_path) {
		create_obj_buffer(obj_path);
		textureId = build_texture(bmp_path, GL_TEXTURE_2D);
		vboId = build_vbo();
		eboId = build_ebo();
		uvboId = build_uvbo();
		nboId = build_nbo();

	}

};
