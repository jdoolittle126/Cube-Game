#pragma once

#include "../Core/Libraries.h"
#include "MapTile.h"

class WorldMap {
private:
	std::vector<MapTile*> tiles;

public:
	WorldMap() {

	}

	void update(float delta, GLuint programID);
	void display(float delta, GLuint programID);
	void create_tile(float x, float y, float z);
	void destroy_tile(float x, float y, float z);
	std::vector<cube_bound> get_world_bounds();

};
