#pragma once

#include "../Core/WorldObject.h"
#include "../Core/Libraries.h"
#include "../Map/WorldMap.h"

class Entity : public WorldObject {
	public:
		float 		vel_x,
					vel_y,
					vel_z,
					vel_yaw,
					vel_pitch,
					vel_roll,
					accel_x,
					accel_y,
					accel_z,
					accel_yaw,
					accel_pitch,
					accel_roll,
					_vel_x,
					_vel_y,
					_vel_z,
					_vel_yaw,
					_vel_pitch,
					_vel_roll,
					_pos_x,
					_pos_y,
					_pos_z,
					_pos_pitch,
					_pos_yaw,
					_pos_roll;


		WorldMap* map;

		bool 	has_accels = false,
				has_accel_x = false, has_accel_y = false, has_accel_z = false, has_accel_pitch = false, has_accel_yaw = false, has_accel_roll = false;

		void build() {
			vel_x = 0.0f;
			vel_y = 0.0f;
			vel_z = 0.0f;
			vel_yaw = 0.0f;
			vel_pitch = 0.0f;
			vel_roll = 0.0f;
			accel_x = 0.0f;
			accel_y = -9.81f;
			accel_z = 0.0f;
			accel_yaw = 0.0f;
			accel_pitch = 0.0f;
			accel_roll = 0.0f;
		}

		Entity(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll, Model* i_model)
		: WorldObject(i_size, i_x, i_y, i_z, i_yaw, i_pitch, i_roll, i_model)
		{
			build();
		}

		Entity(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll, std::vector<Model*> i_model)
		: WorldObject(i_size, i_x, i_y, i_z, i_yaw, i_pitch, i_roll, i_model)
		{
			build();
		}


		void update(float delta);
		void display(float delta, ShaderManager shader_manager);
		void set_world_map(WorldMap* m){
			map = m;
		}

		void allow_accels(bool a);
		float get_vel_x();
		float get_vel_y();
		float get_vel_z();
		float get_vel_roll();
		float get_vel_yaw();
		float get_vel_pitch();
		void set_vel_x(float n);
		void set_vel_y(float n);
		void set_vel_z(float n);
		void set_vel_roll(float n);
		void set_vel_yaw(float n);
		void set_vel_pitch(float n);
		float get_accel_x();
		float get_accel_y();
		float get_accel_z();
		float get_accel_roll();
		float get_accel_yaw();
		float get_accel_pitch();
		void set_accel_x(float n);
		void set_accel_y(float n);
		void set_accel_z(float n);
		void set_accel_roll(float n);
		void set_accel_yaw(float n);
		void set_accel_pitch(float n);
		void pos_update(float delta);
		bool does_collide();
		void check_collide();
};
