#pragma once

#include "UniqueMapTile.h"

#include "../Managers/GameManager.h"
#include "../Object/GameObject.h"

class MapTile: public GameObject {
private:
	bool collidable, drawing;
	UniqueMapTile* ref_tile;

public:
	MapTile(float i_x, float i_y, float i_z, UniqueMapTile* i_ref_tile) :
			GameObject(RenderType::RENDER_CUBE, 1.0f, i_x, i_y, i_z, 0.0f, 0.0f, 0.0f) {
		set_static(true);
		collidable = true;
		drawing = true;
		ref_tile = i_ref_tile;
	}
	~MapTile() {
		delete ref_tile;
	}


	void set_collidable(bool v);
	void set_drawing(bool v);
	bool is_collidable();
	bool is_drawing();
	void update(float delta);
	void display(float delta, GameManager & manager);

};

