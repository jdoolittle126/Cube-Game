#pragma once

#include "../Core/Libraries.h"

class UniqueMapTile {
private:
	GLuint textureId, vboId, eboId, nboId, uvboId;
	int tex_x, tex_y;

public:

	UniqueMapTile(GLuint i_textureId, int i_tex_x, int i_tex_y) {
		textureId = i_textureId;
		tex_x = i_tex_x;
		tex_y = i_tex_y;

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

				GLfloat uv_unit = 0.083333;
				GLfloat uv_mod[4] = {
						uv_unit * tex_x,
						uv_unit * tex_y,
						uv_unit * tex_x + uv_unit,
						uv_unit * tex_y + uv_unit
				};

				 GLfloat base_uv[] = {
						 uv_mod[2], uv_mod[3],
						 uv_mod[0], uv_mod[3],
						 uv_mod[0], uv_mod[1],
						 uv_mod[2], uv_mod[1], //
						 uv_mod[2], uv_mod[1], //
						 uv_mod[2], uv_mod[3],
						 uv_mod[0], uv_mod[3],
						 uv_mod[0], uv_mod[1],
						 uv_mod[2], uv_mod[3],
						 uv_mod[2], uv_mod[1], //
						 uv_mod[0], uv_mod[3],
						 uv_mod[2], uv_mod[3],
						 uv_mod[2], uv_mod[1],
						 uv_mod[0], uv_mod[3],
						 uv_mod[0], uv_mod[1],
						 uv_mod[0], uv_mod[1]
				 };

				glGenBuffers(1, &vboId);
				glBindBuffer(GL_ARRAY_BUFFER, vboId);
				glBufferData(GL_ARRAY_BUFFER, 3 * 25 * sizeof(GLfloat), &base_vert[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glGenBuffers(1, &eboId);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 6 * sizeof(GLint), &base_indicies[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

				glGenBuffers(1, &nboId);
				glBindBuffer(GL_ARRAY_BUFFER, nboId);
				glBufferData(GL_ARRAY_BUFFER, 3 * 24 * sizeof(GLfloat), &base_norm[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glGenBuffers(1, &uvboId);
				glBindBuffer(GL_ARRAY_BUFFER, uvboId);
				glBufferData(GL_ARRAY_BUFFER, 2 * 16 * sizeof(GLfloat), &base_uv[0], GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	GLuint getTextureId() {
		return textureId;
	}
	GLuint getVboId() {
		return vboId;
	}
	GLuint getEboId() {
		return eboId;
	}
	GLuint getNboId() {
		return nboId;
	}
	GLuint getUvboId() {
		return uvboId;
	}


};
