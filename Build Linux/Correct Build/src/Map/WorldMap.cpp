#include "WorldMap.h"
#include "MapTile.h"
#include "../Core/Libraries.h"
#include "MapTileManager.h"


void WorldMap::update(float delta) {
	for(auto &tile : tiles) {
		if(tile->is_drawing()) tile->update(delta);
	}
}

void WorldMap::display(float delta, ShaderManager & shader_manager) {
	for(auto &tile : tiles) {
	    if(tile->is_drawing()) tile->display(delta, shader_manager);
	}
}

void WorldMap::create_tile(float x, float y, float z, int tex_x, int tex_y) {
	tiles.push_back(new MapTile(x, y, z, manager.getTile(tex_x, tex_y)));
}

void WorldMap::destroy_tile(float x, float y, float z) {

}

std::vector<cube_bound> WorldMap::get_world_bounds() {
	std::vector<cube_bound> b;
	for(auto &tile : tiles) {
		if(tile->is_collidable()) b.push_back(tile->get_bounds());
	}
	return b;
}

