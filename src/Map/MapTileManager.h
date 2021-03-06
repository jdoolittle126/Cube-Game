#pragma once

#include "UniqueMapTile.h"

//TODO MOVE TO MANAGERS AND CLEAN

#define TEXTURE_PACK_SIZE 12

class MapTileManager {
private:
	UniqueMapTile * tiles[TEXTURE_PACK_SIZE][TEXTURE_PACK_SIZE];

public:
	MapTileManager(GLuint textureId) {
		//TODO rename this function?
		UniqueMapTile::build_static_members(textureId);
		for(int x = 0; x < TEXTURE_PACK_SIZE; x++) {
			for(int y = 0; y < TEXTURE_PACK_SIZE; y++) {
				tiles[x][y] = new UniqueMapTile(x, y);
			}
		}
	}

	~MapTileManager() {
		delete [] tiles;
		UniqueMapTile::destroy_static_members();
	}

	UniqueMapTile * getTile(int tex_x, int tex_y) {
		return tiles[tex_x][tex_y];
	}

};


