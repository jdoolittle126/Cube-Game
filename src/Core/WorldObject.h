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

	std::vector<glm::vec4> bbverts, bb_verts;

	glm::mat4x4 mat_transform,
				_mat_transform,
				mat_translate,
				mat_scale,
				mat_rot;

	std::vector<glm::vec4> testing;

	Model* model;
	bool use_model = false;
	bool test = true;

	void build(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll){

		size = i_size / 2.0f;
		pos_x = i_x;
		pos_y = i_y;
		pos_z = i_z;
		pos_yaw = i_yaw;
		pos_pitch = i_pitch;
		pos_roll = i_roll;

		bbverts.push_back(glm::vec4(-size, size, size, 1.0f));
		bbverts.push_back(glm::vec4(-size, size, -size, 1.0f));
		bbverts.push_back(glm::vec4(size, size, -size, 1.0f));
		bbverts.push_back(glm::vec4(size, size, size, 1.0f));
		bbverts.push_back(glm::vec4(-size, -size, size, 1.0f));
		bbverts.push_back(glm::vec4(-size, -size, -size, 1.0f));
		bbverts.push_back(glm::vec4(size, -size, -size, 1.0f));
		bbverts.push_back(glm::vec4(size, -size, size, 1.0f));

		bb_verts.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		bb_verts.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		bb_verts.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		bb_verts.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		bb_verts.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		bb_verts.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		bb_verts.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		bb_verts.push_back(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	WorldObject(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll){
		build(i_size, i_x, i_y, i_z, i_yaw, i_pitch, i_roll);
		use_model = false;
	}

	WorldObject(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll, Model* i_model){
		build(i_size, i_x, i_y, i_z, i_yaw, i_pitch, i_roll);
		model = i_model;
		use_model = true;
	}

	void update(float delta, GLuint programID);
	void display(float delta, GLuint programID);
	void update_verts(std::vector<glm::vec4> &_v, std::vector<glm::vec4> &v);
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
	void draw_face_quad(glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d, GLuint programID);
	cubeBound get_bounds();
};
