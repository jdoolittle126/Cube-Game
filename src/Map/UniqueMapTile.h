#pragma once

#include "../Core/Dependancies/Libraries.h"

class UniqueMapTile {
private:
	GLuint uvboId;
	int tex_x, tex_y;

public:
	static constexpr GLfloat uv_unit = 0.083333f;
	static GLuint vboId, eboId, nboId, textureId;

	UniqueMapTile(int i_tex_x, int i_tex_y) {
		tex_x = i_tex_x;
		tex_y = i_tex_y;

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
				 uv_mod[2], uv_mod[1],
				 uv_mod[2], uv_mod[1],
				 uv_mod[2], uv_mod[3],
				 uv_mod[0], uv_mod[3],
				 uv_mod[0], uv_mod[1],
				 uv_mod[2], uv_mod[3],
				 uv_mod[2], uv_mod[1],
				 uv_mod[0], uv_mod[3],
				 uv_mod[2], uv_mod[3],
				 uv_mod[2], uv_mod[1],
				 uv_mod[0], uv_mod[3],
				 uv_mod[0], uv_mod[1],
				 uv_mod[0], uv_mod[1]
		 };

		glGenBuffers(1, &uvboId);
		glBindBuffer(GL_ARRAY_BUFFER, uvboId);
		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), &base_uv[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	~UniqueMapTile() {
		glDeleteBuffers(1, &uvboId);
	}

	GLuint getUvboId() {
		return uvboId;
	}

	static void build_static_members(GLuint i_textureId);
	static void destroy_static_members();

};
