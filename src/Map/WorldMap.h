#pragma once
#include "../Managers/GameManager.h"
#include "MapTileManager.h"
#include "MapTile.h"

class WorldMap {
private:
	std::vector<MapTile*> tiles;
	MapTileManager tile_manager;
	GLuint vaoId;

	void build_vao() {
		glGenVertexArrays(1, &vaoId);
		glBindVertexArray(vaoId);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, UniqueMapTile::eboId);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, UniqueMapTile::vboId);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, UniqueMapTile::nboId);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindVertexArray(0);
	}

public:
	WorldMap(GLuint textureId) : tile_manager(textureId){
		build_vao();
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
