#include "Model.h"
#include "../Utils/OBJ_Loader.h"

void Model::create_data_buffer(std::string path)
{
	objl::Loader Loader;
	bool loadout = Loader.LoadFile(path);

	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];

		for (unsigned int a = 0; a < curMesh.Indices.size(); a++)
		{
			model_indices.push_back(curMesh.Indices[a]);
		}

		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			model_verts.push_back(glm::vec3(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z));
			//model_uvs.push_back(glm::vec2(curMesh.Vertices[j].TextureCoordinate.X, curMesh.Vertices[j].TextureCoordinate.Y));
			//model_normals.push_back(glm::vec3(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z));
			}

	}

	if(loadout) {
		std::cout << "Success" << std::endl;
	} else {
		std::cout << "Fail" << std::endl;
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * model_verts.size(), &model_verts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}