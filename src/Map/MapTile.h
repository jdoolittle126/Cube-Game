#pragma once

#include "../Core/WorldObject.h"
#include "../Core/Libraries.h"

class MapTile: public WorldObject {
private:
	bool collidable, drawable;

public:
	MapTile(float i_x, float i_y, float i_z) :
			WorldObject(1.0f, i_x, i_y, i_z, 0.0f, 0.0f, 0.0f) {
		collidable = true;
		drawable = true;
	}

	MapTile(float i_x, float i_y, float i_z, bool i_collidable, bool i_drawable) :
			WorldObject(1.0f, i_x, i_y, i_z, 0.0f, 0.0f, 0.0f) {
		collidable = i_collidable;
		drawable = i_drawable;
	}

	void set_collidable(bool v) {
		collidable = v;
	}

	void set_drawable(bool v) {
		drawable = v;
	}

	bool is_collidable() {
		return collidable;
	}

	bool is_drawable() {
		return drawable;
	}

};

