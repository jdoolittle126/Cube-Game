#pragma once
#include "Libraries.h"
#include "ShaderManager.h"

class GameObject {
protected:
	bool debug = false;
	RenderType render_type;
	std::vector<glm::vec3> bbverts, bb_verts;
	GLuint debug_vboId, debug_eboId;

	float 		scale_x,
				scale_y,
				scale_z,
				pos_x,
				pos_y,
				pos_z,
				pos_pitch,
				pos_yaw,
				pos_roll;

	glm::mat4x4 mat_transform,
				_mat_transform,
				mat_translate,
				mat_scale,
				mat_rot;


	public:

		GameObject(RenderType i_render_type, float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll) {
			render_type = i_render_type;
			scale_x = i_size;
			scale_y = i_size;
			scale_z = i_size;
			build(i_x, i_y, i_z, i_yaw, i_pitch, i_roll);
		}

		~GameObject() {
			glDeleteBuffers(1, &debug_vboId);
			glDeleteBuffers(1, &debug_eboId);
		}

		void build_debug(){
			if(debug) {
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
		}

		void build(float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll){
			pos_x = i_x;
			pos_y = i_y;
			pos_z = i_z;
			pos_yaw = i_yaw;
			pos_pitch = i_pitch;
			pos_roll = i_roll;
			build_bounds();
		}

		void build_bounds() {
			if(render_type != RenderType::RENDER_MODEL) {
				bbverts.clear();
				float s_x, s_y, s_z;
				cube_bound b;
				b.x1 = -0.5f;
				b.x2 = 0.5f;
				b.y1 = -0.5f;
				b.y2 = 0.5f;
				b.z1 = -0.5f;
				b.z2 = 0.5f;
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
				build_debug();
			}
		}

		virtual void update(float delta);
		virtual void display(float delta, ShaderManager shader_manager);
		float get_scale_x();
		float get_scale_y();
		float get_scale_z();
		float get_pos_x();
		float get_pos_y();
		float get_pos_z();
		float get_roll();
		float get_yaw();
		float get_pitch();
		void set_scale_x(float n);
		void set_scale_y(float n);
		void set_scale_z(float n);
		void set_pos_x(float n);
		void set_pos_y(float n);
		void set_pos_z(float n);
		void set_pos_roll(float n);
		void set_pos_yaw(float n);
		void set_pos_pitch(float n);
		void build_translate(float x, float y, float z);
		void build_scale(float sx, float sy, float sz);
		void build_rot(float _rx, float _ry, float _rz);
		void update_verts(std::vector<glm::vec3> &_v, std::vector<glm::vec3> &v);
		cube_bound get_bounds();
};
