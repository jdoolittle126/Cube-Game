#include "UniqueMapTile.h"

GLuint UniqueMapTile::textureId;
GLuint UniqueMapTile::vboId;
GLuint UniqueMapTile::eboId;
GLuint UniqueMapTile::nboId;

void UniqueMapTile::build_static_members(GLuint i_textureId) {
	UniqueMapTile::textureId = i_textureId;

			GLfloat base_vert[] = {
									0.5,0.5,-0.5,
									-0.5,0.5,-0.5,
									-0.5,0.5,0.5,
									0.5,0.5,0.5,
									0.5,-0.5,0.5,
									0.5,0.5,0.5,
									-0.5,0.5,0.5,
									-0.5,-0.5,0.5,
									-0.5,-0.5,0.5,
									-0.5,0.5,0.5,
									-0.5,0.5,-0.5,
									-0.5,-0.5,-0.5,
									-0.5,-0.5,-0.5,
									0.5,-0.5,-0.5,
									0.5,-0.5,0.5,
									-0.5,-0.5,0.5,
									0.5,-0.5,-0.5,
									0.5,0.5,-0.5,
									0.5,0.5,0.5,
									0.5,-0.5,0.5,
									-0.5,-0.5,-0.5,
									-0.5,0.5,-0.5,
									0.5,0.5,-0.5,
									0.5,-0.5,-0.5
							};

							GLfloat base_norm[] = {
									0,1,0,
									0,1,0,
									0,1,0,
									0,1,0,
									0,0,1,
									0,0,1,
									0,0,1,
									0,0,1,
									-1,0,0,
									-1,0,0,
									-1,0,0,
									-1,0,0,
									0,-1,0,
									0,-1,0,
									0,-1,0,
									0,-1,0,
									1,0,0,
									1,0,0,
									1,0,0,
									1,0,0,
									0,0,-1,
									0,0,-1,
									0,0,-1,
									0,0,-1
							};

							GLint base_indicies[] = {
								0,1,3,1,2,3,
								4,5,7,5,6,7,
								8,9,11,9,10,11,
								12,13,15,13,14,15,
								16,17,19,17,18,19,
								20,21,23,21,22,23
							};


							glGenBuffers(1, &vboId);
							glBindBuffer(GL_ARRAY_BUFFER, vboId);
							glBufferData(GL_ARRAY_BUFFER, 3 * 25 * sizeof(GLfloat), &base_vert[0], GL_STATIC_DRAW);
							glBindBuffer(GL_ARRAY_BUFFER, 0);

							glGenBuffers(1, &eboId);
							glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
							glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLint), &base_indicies[0], GL_STATIC_DRAW);
							glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

							glGenBuffers(1, &nboId);
							glBindBuffer(GL_ARRAY_BUFFER, nboId);
							glBufferData(GL_ARRAY_BUFFER, 3 * 24 * sizeof(GLfloat), &base_norm[0], GL_STATIC_DRAW);
							glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void UniqueMapTile::destroy_static_members() {
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &eboId);
	glDeleteBuffers(1, &nboId);
}
