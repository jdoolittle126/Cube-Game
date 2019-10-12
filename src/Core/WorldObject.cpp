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
	float m[16] = { 1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1 };
	mat_translate = glm::make_mat4x4(m);

}

void WorldObject::build_scale(float sx, float sy, float sz) {
	float m[16] = { sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1 };
	mat_scale = glm::make_mat4x4(m);
}

void WorldObject::build_rot(float _rx, float _ry, float _rz) {
	float rx = _rx * (PI / 180.0f);
	float ry = _ry * (PI / 180.0f);
	float rz = _rz * (PI / 180.0f);

	float m[16] = { cos(ry) * cos(rz), -cos(ry) * sin(rz), sin(ry), 0, (cos(rx)
			* sin(rz)) + (sin(rx) * sin(ry) * cos(rz)), (cos(rx) * cos(rz))
			- (sin(rx) * sin(ry) * sin(rz)), -sin(rx) * cos(ry), 0, (sin(rx)
			* sin(rz)) - (cos(rx) * sin(ry) * cos(rz)), (sin(rx) * cos(rz))
			+ (cos(rx) * sin(ry) * sin(rz)), cos(rx) * cos(ry), 0, 0, 0, 0, 1 };

	mat_rot = glm::make_mat4x4(m);
}

void WorldObject:: update_color(int a) {
	glColor3f(colors[a][0], colors[a][1], colors[a][2]);
}

void WorldObject::draw_face_quad(glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d) {
	std::vector<glm::vec4> v;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);
	v.push_back(d);

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * v.size(), &v[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableVertexAttribArray(0);
}

void WorldObject::draw_face_tri(glm::vec4 a, glm::vec4 b, glm::vec4 c) {
	std::vector<glm::vec4> v;
	v.push_back(a);
	v.push_back(b);
	v.push_back(c);

	GLuint vertexbuffer, normalbuffer;

	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * v.size(), &v[0], GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_QUADS, 0, 3);
	glDisableVertexAttribArray(0);


}

void WorldObject::update_verts(std::vector<glm::vec4> &_v, std::vector<glm::vec4> &v){
	mat_transform = mat_rot * mat_translate * mat_scale;
	for(unsigned int i = 0; i < v.size(); i++) {
		_v.at(i) = v.at(i) * mat_transform;
	}
}

void WorldObject::update(float delta) {
	build_translate(pos_x, pos_y, pos_z);
	build_rot(pos_pitch, pos_yaw, pos_roll);
	build_scale(scale_x, scale_y, scale_z);
	if(model_verts.size() > 0){
		update_verts(_model_verts, model_verts);
	} else {
		update_verts(bb_verts, bbverts);
	}

}

void WorldObject::display(float delta) {

		if(model_verts.size() == 0) {
			//glBegin(GL_QUADS);
				//TOP (a, b, c, d)
				update_color(0);
				draw_face_quad(bb_verts.at(0), bb_verts.at(1), bb_verts.at(2), bb_verts.at(3));

				//BOTTOM (e, f, g, h)
				update_color(1);
				draw_face_quad(bb_verts.at(4), bb_verts.at(5), bb_verts.at(6), bb_verts.at(7));

				//FRONT (a, d, h, e)
				update_color(2);
				draw_face_quad(bb_verts.at(0), bb_verts.at(3), bb_verts.at(7), bb_verts.at(4));

				//BACK (b, c, f, g)
				update_color(3);
				draw_face_quad(bb_verts.at(1), bb_verts.at(2), bb_verts.at(6), bb_verts.at(5));

				//LEFT (a, b, e, f)
				update_color(4);
				draw_face_quad(bb_verts.at(0), bb_verts.at(1), bb_verts.at(5), bb_verts.at(4));

				//RIGHT (d, c, h, g)
				update_color(5);
				draw_face_quad(bb_verts.at(3), bb_verts.at(2), bb_verts.at(6), bb_verts.at(7));
			//glEnd();

		} else {

		update_color(2);

		GLfloat g_vertex_buffer_data[_model_verts.size() * 3];

		for(unsigned int i = 0; i < _model_verts.size(); i++){
			 g_vertex_buffer_data[i*3] = _model_verts.at(i).x;
			 g_vertex_buffer_data[i*3+1] = _model_verts.at(i).y;
			 g_vertex_buffer_data[i*3+2] = _model_verts.at(i).z;
		}

		//Vertex buffer
		GLuint vertexbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

		    //vertex buffer
		    glVertexAttribPointer(
		        0,          //index
		        3,          //size
		        GL_FLOAT,   //type
		        GL_FALSE,   //normalized?
		        0,          //stride
		        0           //array buffer offset
		    );

		    //draw triangle
		    glDrawArrays(GL_TRIANGLES, 0, model_verts.size() * 3);

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
