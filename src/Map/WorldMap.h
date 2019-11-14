#pragma once
#include "../Core/ShaderManager.h"
#include "../Core/Libraries.h"
#include "MapTileManager.h"
#include "MapTile.h"

class WorldMap {
private:
	std::vector<MapTile*> tiles;
	MapTileManager manager;

public:
	WorldMap(GLuint textureId) : manager(textureId){
	}

	void update(float delta);
	void display(float delta, ShaderManager & shader_manager);
	void create_tile(float x, float y, float z, int tex_x, int tex_y);
	void destroy_tile(float x, float y, float z);
	std::vector<cube_bound> get_world_bounds();

};
