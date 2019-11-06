#include "Model.h"
#include "../Utils/OBJ_Loader.h"

void Model::create_obj_buffer(std::string path) {
	objl::Loader Loader;
	bool loadout = Loader.LoadFile(path);
	int size = 0;

	for (unsigned int i = 0; i < Loader.LoadedMeshes.size(); i++) {
		objl::Mesh curMesh = Loader.LoadedMeshes[i];

		for (unsigned int a = 0; a < curMesh.Indices.size(); a++) {
			model_indices.push_back(curMesh.Indices[a] + size);
		}

		size += curMesh.Vertices.size();

		for (unsigned int j = 0; j < curMesh.Vertices.size(); j++) {
			model_verts.push_back(
					glm::vec3(curMesh.Vertices[j].Position.X,
							curMesh.Vertices[j].Position.Y,
							curMesh.Vertices[j].Position.Z));
			model_uvs.push_back(
					glm::vec2(curMesh.Vertices[j].TextureCoordinate.X,
							curMesh.Vertices[j].TextureCoordinate.Y));
			model_normals.push_back(
					glm::vec3(curMesh.Vertices[j].Normal.X,
							curMesh.Vertices[j].Normal.Y,
							curMesh.Vertices[j].Normal.Z));
		}

	}

	if (loadout) {
		std::cout << "Success" << std::endl;
	} else {
		std::cout << "Fail" << std::endl;
	}

}

GLuint Model::build_texture(std::string path) {

	// Data read from the header of the BMP file
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	// Actual RGB data
	unsigned char *data;

	// Open the file
	FILE *file = fopen(path.c_str(), "rb");
	if (!file) {
		getchar();
		return 0;
	}

	// Read the header, i.e. the 54 first bytes

	// If less than 54 bytes are read, problem
	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// A BMP files always begins with "BM"
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	// Make sure this is a 24bpp file
	if (*(int*) &(header[0x1E]) != 0) {
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}
	if (*(int*) &(header[0x1C]) != 24) {
		printf("Not a correct BMP file\n");
		fclose(file);
		return 0;
	}

	// Read the information about the image
	dataPos = *(int*) &(header[0x0A]);
	imageSize = *(int*) &(header[0x22]);
	width = *(int*) &(header[0x12]);
	height = *(int*) &(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0) imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0) dataPos = 54; // The BMP header is done that way

	// Create a buffer
	data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	// Everything is in memory now, the file can be closed.
	fclose(file);

	// Create one OpenGL texture
	GLuint texture;
	glGenTextures(1, &texture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR,
			GL_UNSIGNED_BYTE, data);

	// OpenGL has now copied the data. Free our own version
	delete[] data;

	// Poor filtering, or ...
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// ... nice trilinear filtering ...
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_LINEAR_MIPMAP_LINEAR);
	// ... which requires mipmaps. Generate them automatically.
	glGenerateMipmap (GL_TEXTURE_2D);

	// Return the ID of the texture we just created
	return texture;
}

GLuint Model::build_ebo() {
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			model_indices.size() * sizeof(unsigned int), &model_indices[0],
			GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return ebo;
}

GLuint Model::build_vbo() {
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, model_verts.size() * sizeof(glm::vec3),
			&model_verts[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vbo;
}

GLuint Model::build_uvbo() {
	GLuint uvbo;
	glGenBuffers(1, &uvbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	glBufferData(GL_ARRAY_BUFFER, model_uvs.size() * sizeof(glm::vec2),
			&model_uvs[0], GL_STATIC_DRAW);

	return uvbo;
}

GLuint Model::build_nbo() {
	GLuint nbo;
	glGenBuffers(1, &nbo);
	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glBufferData(GL_ARRAY_BUFFER, model_normals.size() * sizeof(glm::vec3),
			&model_normals[0], GL_STATIC_DRAW);

	return nbo;
}

cube_bound Model::get_bounds() {
	cube_bound b;
	bool flag = true;
	for (auto t : model_verts) {
		if (flag) {
			b.x1 = t.x;
			b.x2 = t.x;
			b.y1 = t.y;
			b.y2 = t.y;
			b.z1 = t.z;
			b.z2 = t.z;
			flag = false;
		}

		if (t.x > b.x1)
			b.x1 = t.x;
		else if (t.x < b.x2) b.x2 = t.x;
		if (t.y > b.y1)
			b.y1 = t.y;
		else if (t.y < b.y2) b.y2 = t.y;
		if (t.z > b.z1)
			b.z1 = t.z;
		else if (t.z < b.z2) b.z2 = t.z;
	}
	return b;

}
