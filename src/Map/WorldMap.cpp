#include "WorldMap.h"
#include "MapTile.h"
#include "../Core/Libraries.h"

void WorldMap::update(float delta) {
	for(auto &tile : tiles) {
	    tile->update(delta);
	}
}

void WorldMap::display(float delta) {
	for(auto &tile : tiles) {
	    tile->display(delta);
	}
}

void WorldMap::create_tile(float x, float y, float z) {
	tiles.push_back(new MapTile(x, y, z));
}

void WorldMap::destroy_tile(float x, float y, float z) {

}

std::vector<cubeBound> WorldMap::get_world_bounds() {
	std::vector<cubeBound> b;
	for(auto &tile : tiles) {
	    b.push_back(tile->get_bounds());
	}
	return b;
}

