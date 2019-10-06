#pragma once

#include "../Core/GameObject.h"
#include "../Core/Libraries.h"

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

	std::list<glm::vec4*>
				verts;

	glm::vec4 	vert0,
				vert1,
				vert2,
				vert3,
				vert4,
				vert5,
				vert6,
				vert7,
				_vert0,
				_vert1,
				_vert2,
				_vert3,
				_vert4,
				_vert5,
				_vert6,
				_vert7;

	glm::mat4x4 mat_transform,
				_mat_transform,
				mat_translate,
				mat_scale,
				mat_rot;

	WorldObject(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll){
		size = i_size / 2.0f;
		pos_x = i_x;
		pos_y = i_y;
		pos_z = i_z;
		pos_yaw = i_yaw;
		pos_pitch = i_pitch;
		pos_roll = i_roll;
		vert0 = glm::vec4(-size, size, size, 1.0f);
		vert1 = glm::vec4(-size, size, -size, 1.0f);
		vert2 = glm::vec4(size, size, -size, 1.0f);
		vert3 = glm::vec4(size, size, size, 1.0f);
		vert4 = glm::vec4(-size, -size, size, 1.0f);
		vert5 = glm::vec4(-size, -size, -size, 1.0f);
		vert6 = glm::vec4(size, -size, -size, 1.0f);
		vert7 = glm::vec4(size, -size, size, 1.0f);

		verts.push_back(&_vert0);
		verts.push_back(&_vert1);
		verts.push_back(&_vert2);
		verts.push_back(&_vert3);
		verts.push_back(&_vert4);
		verts.push_back(&_vert5);
		verts.push_back(&_vert6);
		verts.push_back(&_vert7);
	}


	void update(float delta);
	void display(float delta);
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
	void draw_face(glm::vec4 a, glm::vec4 b, glm::vec4 c, glm::vec4 d);
	cubeBound get_bounds();
};
