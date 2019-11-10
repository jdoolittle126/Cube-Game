#pragma once

#include "../Core/WorldObject.h"
#include "../Core/Libraries.h"

class MapTile: public GameObject {
private:
	bool collidable, drawing;
	GLuint textureId;

public:
	MapTile(float i_x, float i_y, float i_z, GLuint i_textureId) :
			GameObject(RenderType::RENDER_CUBE, 1.0f, i_x, i_y, i_z, 0.0f, 0.0f, 0.0f) {
		collidable = true;
		drawing = true;
		textureId = i_textureId;
	}

	void set_collidable(bool v);
	void set_drawing(bool v);
	bool is_collidable();
	bool is_drawing();
	void update(float delta, GLuint programID);
	void display(float delta, GLuint programID);

};

