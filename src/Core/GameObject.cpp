#include "GameObject.h"
#include "Libraries.h"

float GameObject::get_scale_x(){
	return scale_x;
}

float GameObject::get_scale_y(){
	return scale_y;
}

float GameObject::get_scale_z(){
	return scale_z;
}

float GameObject::get_pos_x(){
	return pos_x;
}

float GameObject::get_pos_y(){
	return pos_y;
}

float GameObject::get_pos_z(){
	return pos_z;
}

float GameObject::get_yaw(){
	return pos_yaw;
}

float GameObject::get_pitch(){
	return pos_pitch;
}

float GameObject::get_roll(){
	return pos_roll;
}

void GameObject::set_scale_x(float n){
	scale_x = n;
}

void GameObject::set_scale_y(float n){
	scale_y = n;
}

void GameObject::set_scale_z(float n){
	scale_z = n;
}

void GameObject::set_pos_x(float n){
	pos_x = n;
}

void GameObject::set_pos_y(float n){
	pos_y = n;
}

void GameObject::set_pos_z(float n){
	pos_z = n;
}

void GameObject::set_pos_yaw(float n){
	pos_yaw = n;
}

void GameObject::set_pos_pitch(float n){
	pos_pitch = n;
}

void GameObject::set_pos_roll(float n){
	pos_roll = n;
}

void GameObject::build_translate(float x, float y, float z) {
	mat_translate = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

}

void GameObject::build_scale(float sx, float sy, float sz) {
	mat_scale = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz));
}

void GameObject::build_rot(float _rx, float _ry, float _rz) {

	glm::vec3 euler(_rx, _ry, _rz);
	glm::quat quaternion = glm::quat(euler);

	mat_rot = glm::toMat4(quaternion);
}

void GameObject::update_verts(std::vector<glm::vec3> &_v, std::vector<glm::vec3> &v){
	glm::mat4 _mat_transform = mat_translate * mat_scale;
	for(unsigned int i = 0; i < v.size(); i++) {
		_v.at(i) = glm::vec3(_mat_transform * glm::vec4(v.at(i), 1.0f));
	}
}


void GameObject::update(float delta, GLuint programID) {
	build_translate(pos_x, pos_y, pos_z);
	build_rot(pos_pitch, pos_yaw, pos_roll);
	build_scale(scale_x, scale_y, scale_z);
	mat_transform = mat_translate * mat_rot * mat_scale;
	build_bounds();
	update_verts(bb_verts, bbverts);
}

void GameObject::display(float delta, GLuint programID) {
	if(debug) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		GLuint matrixAttributePosition = glGetUniformLocation(programID, "mat_model_view");
		glm::mat4 _mat_transform = mat_translate * mat_scale;
		glUniformMatrix4fv(matrixAttributePosition, 1, GL_FALSE, &_mat_transform[0][0]);

	    glBindBuffer(GL_ARRAY_BUFFER, debug_vboId);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, debug_eboId);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);
	}
}

cube_bound GameObject::get_bounds() {
	cube_bound b;
	bool flag = true;
	for(auto t : bb_verts){
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

