#pragma once

#include "../Core/WorldObject.h"
#include "../Core/Libraries.h"


class MapTile: public WorldObject {
	public: MapTile(float i_x, float i_y, float i_z)
		: WorldObject(1.0f, i_x, i_y, i_z, 0.0f, 0.0f, 0.0f)
		{

		}
};

