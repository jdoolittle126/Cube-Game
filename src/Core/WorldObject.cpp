#include "WorldObject.h"
#include "Libraries.h"

float WorldObject::get_pos_x(){
	return pos_x;
}

float WorldObject::get_pos_y(){
	return pos_y;
}

float WorldObject::get_pos_z(){
	return pos_z;
}

float WorldObject::get_yaw(){
	return pos_yaw;
}

float WorldObject::get_pitch(){
	return pos_pitch;
}

float WorldObject::get_roll(){
	return pos_roll;
}

void WorldObject::set_pos_x(float n){
	pos_x = n;
}

void WorldObject::set_pos_y(float n){
	pos_y = n;
}

void WorldObject::set_pos_z(float n){
	pos_z = n;
}

void WorldObject::set_pos_yaw(float n){
	pos_yaw = n;
}

void WorldObject::set_pos_pitch(float n){
	pos_pitch = n;
}

void WorldObject::set_pos_roll(float n){
	pos_roll = n;
}

void WorldObject::build_translate(float x, float y, float z) {
	//float m[16] = { 1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1 };
	mat_translate = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

}

void WorldObject::build_scale(float sx, float sy, float sz) {
	//float m[16] = { sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1 };
	mat_scale = glm::scale(glm::mat4(1.0f), glm::vec3(sx, sy, sz));
}

void WorldObject::build_rot(float _rx, float _ry, float _rz) {
	/*
	float rx = _rx * (PI / 180.0f);
	float ry = _ry * (PI / 180.0f);
	float rz = _rz * (PI / 180.0f);

	float m[16] = { cos(ry) * cos(rz), -cos(ry) * sin(rz), sin(ry), 0, (cos(rx)
			* sin(rz)) + (sin(rx) * sin(ry) * cos(rz)), (cos(rx) * cos(rz))
			- (sin(rx) * sin(ry) * sin(rz)), -sin(rx) * cos(ry), 0, (sin(rx)
			* sin(rz)) - (cos(rx) * sin(ry) * cos(rz)), (sin(rx) * cos(rz))
			+ (cos(rx) * sin(ry) * sin(rz)), cos(rx) * cos(ry), 0, 0, 0, 0, 1 };
	*/
	glm::vec3 euler(_rx, _ry, _rz);
	glm::quat quaternion = glm::quat(euler);

	mat_rot = glm::toMat4(quaternion);
}

void WorldObject:: update_color(int a) {
	glColor3f(colors[a][0], colors[a][1], colors[a][2]);
}


void WorldObject::draw_face_quad(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d) {
	tri_verts.push_back(a);
	tri_verts.push_back(b);
	tri_verts.push_back(c);
	tri_verts.push_back(c);
	tri_verts.push_back(d);
	tri_verts.push_back(a);
}



void WorldObject::update_verts(std::vector<glm::vec3> &_v, std::vector<glm::vec3> &v){
	glm::mat4 _mat_transform = mat_translate * mat_scale;
	for(unsigned int i = 0; i < v.size(); i++) {
		_v.at(i) = glm::vec3(_mat_transform * glm::vec4(v.at(i), 1.0f));
	}
}

void WorldObject::update(float delta, GLuint programID) {
	build_translate(pos_x, pos_y, pos_z);
	build_rot(pos_pitch, pos_yaw, pos_roll);
	build_scale(scale_x, scale_y, scale_z);
	mat_transform = mat_translate * mat_rot * mat_scale;
	update_verts(bb_verts, bbverts);

}

void WorldObject::display(float delta, GLuint programID) {

		if((use_model && draw_bb) || !use_model) {
			//TOP (a, b, c, d)
			update_color(0);
			draw_face_quad(bbverts.at(0), bbverts.at(1), bbverts.at(2), bbverts.at(3));

			//BOTTOM (e, f, g, h)
			update_color(1);
			draw_face_quad(bbverts.at(4), bbverts.at(5), bbverts.at(6), bbverts.at(7));

			//FRONT (a, d, h, e)
			update_color(2);
			draw_face_quad(bbverts.at(0), bbverts.at(3), bbverts.at(7), bbverts.at(4));

			//BACK (b, c, f, g)
			update_color(3);
			draw_face_quad(bbverts.at(1), bbverts.at(2), bbverts.at(6), bbverts.at(5));

			//LEFT (a, b, e, f)
			update_color(4);
			draw_face_quad(bbverts.at(0), bbverts.at(1), bbverts.at(5), bbverts.at(4));

			//RIGHT (d, c, h, g)
			update_color(5);
			draw_face_quad(bbverts.at(3), bbverts.at(2), bbverts.at(6), bbverts.at(7));

			GLuint matrixAttributePosition = glGetUniformLocation(programID, "mat_model_view");
			glm::mat4 _mat_transform = mat_translate * mat_scale;
			glUniformMatrix4fv(matrixAttributePosition, 1, GL_FALSE, &_mat_transform[0][0]);

		    GLuint vboId;

		    glGenBuffers(1, &vboId);
		    glBindBuffer(GL_ARRAY_BUFFER, vboId);
		    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*tri_verts.size(), &tri_verts[0], GL_STATIC_DRAW);
		    glBindBuffer(GL_ARRAY_BUFFER, 0);

		    glEnableVertexAttribArray(0);
		    glBindBuffer(GL_ARRAY_BUFFER, vboId);
		    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		    glDrawArrays(GL_TRIANGLES, 0, 3*tri_verts.size());
		    glDisableVertexAttribArray(0);

		    tri_verts.clear();

		}
		if(use_model) {
			GLuint matrixAttributePosition = glGetUniformLocation(programID, "mat_model_view");
			glUniformMatrix4fv(matrixAttributePosition, 1, GL_FALSE, &mat_transform[0][0]);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->eboId);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			//glDrawArrays(GL_TRIANGLES, 0, 3*(model->model_verts.size()));
			glDrawElements(GL_TRIANGLES, model->model_indices.size(), GL_UNSIGNED_INT, (void*)0);
			glDisableVertexAttribArray(0);

		}

}

cubeBound WorldObject::get_bounds() {
	cubeBound b;
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

		if(t.x < b.x1) b.x1 = t.x;
		else if(t.x > b.x2) b.x2 = t.x;
		if(t.y < b.y1) b.y1 = t.y;
		else if(t.y > b.y2) b.y2 = t.y;
		if(t.z < b.z1) b.z1 = t.z;
		else if(t.z > b.z2) b.z2 = t.z;
	}
	return b;

}
