#pragma once

#include "WorldObject.h"

class EdibleObject : public WorldObject {
protected:

public:
	EdibleObject(float i_size, float i_x, float i_y, float i_z, float i_yaw, float i_pitch, float i_roll, Model* i_model) : WorldObject(i_size, i_x, i_y, i_z, i_yaw, i_pitch, i_roll, i_model) {

	}

	~EdibleObject() {

	}


};
