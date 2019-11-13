#include "Model.h"
#include "../Utils/OBJ_Loader.h"

void Model::create_obj_buffer(std::string path)
{
	objl::Loader Loader;
	bool loadout = Loader.LoadFile(path);
	int size = 0;

	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];

		for (unsigned int a = 0; a < curMesh.Indices.size(); a++) {
			model_indices.push_back(curMesh.Indices[a] + size);
		}

		size += curMesh.Vertices.size();

		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++) {
			model_verts.push_back(glm::vec3(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z));
			model_uvs.push_back(glm::vec2(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y));
			model_normals.push_back(glm::vec3(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z));
		}


	}

	if(loadout) {

		std::cout << "Success\n";
	} else {
		std::cout << "Fail\n";
	}


}

GLuint Model::build_ebo() {
	 GLuint ebo;
	 glGenBuffers(1, &ebo);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, model_indices.size() * sizeof(unsigned int), &model_indices[0], GL_STATIC_DRAW);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	 return ebo;
}

GLuint Model::build_vbo() {
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, model_verts.size() * sizeof(glm::vec3), &model_verts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

GLuint Model::build_uvbo() {
	GLuint uvbo;
	glGenBuffers(1, &uvbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glBufferData(GL_ARRAY_BUFFER, model_uvs.size() * sizeof(glm::vec2), &model_uvs[0], GL_STATIC_DRAW);

	return uvbo;
}

GLuint Model::build_nbo() {
	GLuint nbo;
	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, model_normals.size() * sizeof(glm::vec3), &model_normals[0], GL_STATIC_DRAW);

	return nbo;
}

cube_bound Model::get_bounds() {
	cube_bound b;
	bool flag = true;
	for(auto t : model_verts){
		if(flag) {
			b.x1 = t.x;
			b.x2 = t.x;
			b.y1 = t.y;
			b.y2 = t.y;
			b.z1 = t.z;
			b.z2 = t.z;
			flag = false;
		}

		if(t.x > b.x1) b.x1 = t.x;
		else if(t.x < b.x2) b.x2 = t.x;
		if(t.y > b.y1) b.y1 = t.y;
		else if(t.y < b.y2) b.y2 = t.y;
		if(t.z > b.z1) b.z1 = t.z;
		else if(t.z < b.z2) b.z2 = t.z;
	}
	return b;

}
