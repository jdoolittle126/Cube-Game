#include "Model.h"
#include "../Utils/OBJ_Loader.h"

GLuint Model::create_data_buffer(std::string path)
{
	objl::Loader Loader;
	bool loadout = Loader.LoadFile(path);

	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++)
	{
		objl::Mesh curMesh = Loader.LoadedMeshes[i];
		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++)
		{
			model_verts.push_back(glm::vec4(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z, 1.0f));
			//model_uvs.push_back(glm::vec4(curMesh.TCoords[j].X, curMesh.TCoords[j].Y, 0.0f, 1.0f));
			model_normals.push_back(glm::vec4(curMesh.Vertices[j].Normal.X, curMesh.Vertices[j].Normal.Y, curMesh.Vertices[j].Normal.Z, 1.0f));
		}
	}

	if(loadout) {
		std::cout << "Success" << std::endl;
	} else {
		std::cout << "Fail" << std::endl;
	}

    GLuint vboId;

    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * model_verts.size(), &model_verts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vboId;
}
