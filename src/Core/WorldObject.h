#pragma once

#include "../Core/GameObject.h"
#include "../Core/Libraries.h"
#include "../Utils/OBJ_Loader.h"
#include "Model.h"

class WorldObject : public GameObject {
protected:
	std::vector<Model*> model;
	bool animated = false;
	int current_model = 0;

	float delta_arg = 0;

public:
	WorldObject(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll, Model* i_model) : GameObject(RenderType::RENDER_MODEL, i_size, i_x, i_y, i_z, i_yaw, i_pitch, i_roll) {
		model.push_back(i_model);
		build_bounds();
	}

	WorldObject(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll, std::vector<Model*> i_model) : GameObject(RenderType::RENDER_MODEL, i_size, i_x, i_y, i_z, i_yaw, i_pitch, i_roll) {
		model = i_model;
		animated = true;
		build_bounds();
	}

	void build_bounds();
	void update(float delta);
	void display(float delta, ShaderManager shader_manager);
};
