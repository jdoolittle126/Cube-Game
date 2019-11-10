#include "WorldMap.h"
#include "MapTile.h"
#include "../Core/Libraries.h"

void WorldMap::update(float delta, GLuint programID) {
	for(auto &tile : tiles) {
		if(tile->is_drawing()) tile->update(delta, programID);
	}
}

void WorldMap::display(float delta, GLuint programID) {
	for(auto &tile : tiles) {
	    if(tile->is_drawing()) tile->display(delta, programID);
	}
}

void WorldMap::create_tile(float x, float y, float z, GLuint textureId) {
	tiles.push_back(new MapTile(x, y, z, textureId));
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

