#pragma once

#include "../Core/GameObject.h"
#include "../Core/Libraries.h"
#include "../Utils/OBJ_Loader.h"
#include "Model.h"

struct cubeBound {
	float 	x1, x2,
			y1, y2,
			z1, z2;
};

class WorldObject : public GameObject {
public:
	float 		size,
				scale_x = 1.0f,
				scale_y = 1.0f,
				scale_z = 1.0f,
				pos_x,
				pos_y,
				pos_z,
				pos_pitch,
				pos_yaw,
				pos_roll;

	std::vector<glm::vec3> bbverts, bb_verts;

	GLuint debug_vboId, debug_eboId;

	glm::mat4x4 mat_transform,
				_mat_transform,
				mat_translate,
				mat_scale,
				mat_rot;

	Model* model;
	bool use_model = false, draw_bb = false;
	bool test = true;

	void build(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll){

		size = i_size / 2.0f;
		pos_x = i_x;
		pos_y = i_y;
		pos_z = i_z;
		pos_yaw = i_yaw;
		pos_pitch = i_pitch;
		pos_roll = i_roll;

		bbverts.push_back(glm::vec3(-size, size, size));
		bbverts.push_back(glm::vec3(-size, size, -size));
		bbverts.push_back(glm::vec3(size, size, -size));
		bbverts.push_back(glm::vec3(size, size, size));
		bbverts.push_back(glm::vec3(-size, -size, size));
		bbverts.push_back(glm::vec3(-size, -size, -size));
		bbverts.push_back(glm::vec3(size, -size, -size));
		bbverts.push_back(glm::vec3(size, -size, size));

		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		bb_verts.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	}

	void build_debug(){
		glGenBuffers(1, &debug_vboId);
	    glBindBuffer(GL_ARRAY_BUFFER, debug_vboId);
	    glBufferData(GL_ARRAY_BUFFER, bbverts.size() * sizeof(glm::vec3), &bbverts[0], GL_STATIC_DRAW);
	    glBindBuffer(GL_ARRAY_BUFFER, 0);

	    GLuint debug_indices[] = {
	    		0,1,2,2,3,0,
	    		4,5,6,6,7,4,
	    		0,3,7,7,4,0,
	    		1,2,6,6,5,1,
	    		0,1,5,5,4,0,
	    		3,2,6,6,7,3

	    };

	    glGenBuffers(1, &debug_eboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, debug_eboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(unsigned int), &debug_indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	WorldObject(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll){
		build(i_size, i_x, i_y, i_z, i_yaw, i_pitch, i_roll);
		build_debug();
		use_model = false;
	}

	WorldObject(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll, Model* i_model){
		build(i_size, i_x, i_y, i_z, i_yaw, i_pitch, i_roll);
		model = i_model;
		use_model = true;
	}

	void update(float delta, GLuint programID);
	void display(float delta, GLuint programID);
	void update_verts(std::vector<glm::vec3> &_v, std::vector<glm::vec3> &v);
	float get_pos_x();
	float get_pos_y();
	float get_pos_z();
	float get_roll();
	float get_yaw();
	float get_pitch();
	void set_pos_x(float n);
	void set_pos_y(float n);
	void set_pos_z(float n);
	void set_pos_roll(float n);
	void set_pos_yaw(float n);
	void set_pos_pitch(float n);
	void build_translate(float x, float y, float z);
	void build_scale(float sx, float sy, float sz);
	void build_rot(float _rx, float _ry, float _rz);
	void update_color(int a);
	void draw_face_quad(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
	cubeBound get_bounds();
};
