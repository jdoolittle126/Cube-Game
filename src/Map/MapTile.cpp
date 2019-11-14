#include "MapTile.h"


void MapTile::set_collidable(bool v) {
	collidable = v;
}

void MapTile::set_drawing(bool v) {
	drawing = v;
}

bool MapTile::is_collidable() {
	return collidable;
}

bool MapTile::is_drawing() {
	return drawing;
}

void MapTile::update(float delta) {
	GameObject::update(delta);
}
void MapTile::display(float delta, ShaderManager & shader_manager) {
	if(drawing) {
		GLuint programID = shader_manager.use_shader("WorldObj");

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLuint matrixAttributePosition = glGetUniformLocation(programID, "mat_model_view");
		glUniformMatrix4fv(matrixAttributePosition, 1, GL_FALSE, &mat_transform[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ref_tile->getTextureId());
		glUniform1i(glGetUniformLocation(programID, "sampler"), 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ref_tile->getEboId());

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, ref_tile->getVboId());
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, ref_tile->getUvboId());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, ref_tile->getNboId());
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		GameObject::display(delta, shader_manager);
	}

}
