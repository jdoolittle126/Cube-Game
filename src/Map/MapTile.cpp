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

void MapTile::update(float delta, GLuint programID) {
	GameObject::update(delta, programID);
}
void MapTile::display(float delta, GLuint programID) {
	if(drawing) {
		GameObject::display(delta, programID);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLuint textureID  = glGetUniformLocation(programID, "sampler");
		GLuint matrixAttributePosition = glGetUniformLocation(programID, "mat_model_view");
		glUniformMatrix4fv(matrixAttributePosition, 1, GL_FALSE, &mat_transform[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glUniform1i(textureID, 0);

	    glBindBuffer(GL_ARRAY_BUFFER, debug_vboId);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, debug_eboId);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
	}

}
