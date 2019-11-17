#pragma once
#include "../Managers/GameManager.h"
#include "MapTileManager.h"
#include "MapTile.h"

class WorldMap {
private:
	std::vector<MapTile*> tiles;
	MapTileManager tile_manager;

public:
	WorldMap(GLuint textureId) : tile_manager(textureId){
	}
	~WorldMap() {
		while(!tiles.empty()) delete tiles.back(), tiles.pop_back();
	}

	void update(float delta);
	void display(float delta, GameManager & manager);
	void create_tile(float x, float y, float z, int tex_x, int tex_y);
	void destroy_tile(float x, float y, float z);
	std::vector<cube_bound> get_world_bounds();

};
