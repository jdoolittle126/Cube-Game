#include "WorldObject.h"
#include "Libraries.h"

//SHADER ISSUES W TEXTURE
//MAY BE THE SOURCE OF SECOND BLOCK NOT HAVING DEBUG BOX

 void WorldObject::build_bounds(){
		bbverts.clear();
		float s_x, s_y, s_z;
		cube_bound b;
		b = model.at(current_model)->get_bounds();
		s_x = (b.x1 - b.x2) / 2.0f;
		s_y = (b.y1 - b.y2) / 2.0f;
		s_z = (b.z1 - b.z2) / 2.0f;
		bbverts.push_back(glm::vec3(-s_x, s_y, s_z));
		bbverts.push_back(glm::vec3(-s_x, s_y, -s_z));
		bbverts.push_back(glm::vec3(s_x, s_y, -s_z));
		bbverts.push_back(glm::vec3(s_x, s_y, s_z));
		bbverts.push_back(glm::vec3(-s_x, -s_y, s_z));
		bbverts.push_back(glm::vec3(-s_x, -s_y, -s_z));
		bbverts.push_back(glm::vec3(s_x, -s_y, -s_z));
		bbverts.push_back(glm::vec3(s_x, -s_y, s_z));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		GameObject::build_debug();
	}

void WorldObject::update(float delta, GLuint programID) {
	GameObject::update(delta, programID);

	if(animated) {
		delta_arg += delta;
		if(delta_arg >= 0.25f) {
			delta_arg -= 0.25f;
			if(current_model == signed(model.size() - 1)) current_model = 0;
			else current_model++;
		}
	}

}

void WorldObject::display(float delta, GLuint programID) {
		GameObject::display(delta, programID);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLuint textureID  = glGetUniformLocation(programID, "sampler");
		GLuint matrixAttributePosition = glGetUniformLocation(programID, "mat_model_view");
		glUniformMatrix4fv(matrixAttributePosition, 1, GL_FALSE, &mat_transform[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, model.at(current_model)->textureId);
		glUniform1i(textureID, 0);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.at(current_model)->eboId);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, model.at(current_model)->vboId);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, model.at(current_model)->uvboId);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, model.at(current_model)->nboId);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawElements(GL_TRIANGLES, model.at(current_model)->model_indices.size(), GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);


}
