#pragma once

#include "../Core/Libraries.h"
#include "MapTile.h"

class WorldMap {
	private:
		std::vector<MapTile*> tiles;

	public:
		WorldMap() {

		}


	void update(float delta);
	void display(float delta);
	void create_tile(float x, float y, float z);
	void destroy_tile(float x, float y, float z);
	std::vector<cubeBound> get_world_bounds();

};
